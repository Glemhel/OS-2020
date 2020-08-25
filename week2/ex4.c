/**
 * 
 * Mikhail Rudakov, BS19-02
 * 
*/

#include <stdio.h>

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(){
    printf("Enter two integers separated by a space character:\n");
    int a, b;
    scanf("%d %d", &a, &b);
    swap(&a, &b);
    printf("Here are your numbers swapped:\n%d %d\n", a, b);
    return 0;
}