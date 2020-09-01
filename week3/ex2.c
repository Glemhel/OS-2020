#include <stdio.h>

#define SIZE 7

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void bubble_sort(int array[]){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE - i - 1; j++){
            if (array[j] > array[j + 1]){
                swap(&array[j], &array[j + 1]);
            }
        }
    }
}

int main(){
    int myArray[SIZE] = {4, 2 ,6 ,3, 5, 1, 3};
    bubble_sort(myArray);
    printf("Here is your array sorted in non-descending order:\n");
    for (int i = 0; i < SIZE; i++){
        printf("%d ", myArray[i]);
    }
    printf("\n");
    return 0;
}