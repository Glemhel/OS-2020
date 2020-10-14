#include <stdio.h>

#define N 100 // number of page frames
const int MAX_BIT = 1 << 30; // highest bit in age

struct page_frame{
    int page_id; // page identifier - number > 0, -1 by default when page is absent
    char R; // R-bit
    int age; // age of the page
};

struct page_frame page_table[N];

int hits = 0, misses = 0;
double ratio = 0;
int timer = 0;


int main(){
    // input file
    FILE *input = fopen("input4.txt", "r");

    // fill the initial array
    for (int i = 0; i < N; i++){
        struct page_frame tmp;
        tmp.age = 0;
        tmp.page_id = -1;
        tmp.R = 0;
        page_table[i] = tmp;
    }
    int new_page_id;
    // read while file is not over
    while (fscanf(input, "%d", &new_page_id) != EOF){
        // try to find new_page in page_table
        int new_page_index = -1; // -1 if not present, >= 0 if present
        for (int i = 0; i < N; i++){
            if (page_table[i].page_id == new_page_id){
                new_page_index = i;
            }
        }
        if (new_page_index != -1){
            hits++; // hit!
            page_table[new_page_index].R = 1; // referenced during this clock tick
        } else {
            misses++; // missed the page
            // we need to remove the oldest page from page frames table
            // there might also be untaken places in table
            int untaken = 0;
            for (int i = 0; i < N; i++){
                if (page_table[i].page_id == -1 && untaken == 0){
                    // unpresent, fill it
                    page_table[i].R = 1;
                    page_table[i].page_id = new_page_id;
                    page_table[i].age = 0;
                    untaken = 1;
                }
            }
            if (untaken == 0){
                // page table is full, then search for oldest page
                int minn = page_table[0].age;
                int min_index = 0;

                for (int i = 1; i < N; i++){
                    if (minn > page_table[i].age){
                        minn = page_table[i].age;
                        min_index = i;
                    }
                }
                page_table[min_index].page_id = new_page_id;
                page_table[min_index].R = 1;
                page_table[min_index].age = 0;
            }
        }
        // new page inserted, now update ages
        for (int i = 0; i < N; i++){
            page_table[i].age >>= 1;
            page_table[i].age |= page_table[i].R * MAX_BIT;
            page_table[i].R = 0;
        }
        
    }
    printf("Hits: %d\n", hits);
    printf("Misses: %d\n", misses);
    ratio = (double)hits / (double)(hits + misses);
    printf("Ratio: %lf\n",ratio);
    return 0;
}

/*
Results of testing:
N = 10:
    Hits: 10
    Misses: 990
    Ratio: 0.010000
N = 50:
    Hits: 52
    Misses: 948
    Ratio: 0.052000
N = 100:
    Hits: 98
    Misses: 902
    Ratio: 0.098000
*/