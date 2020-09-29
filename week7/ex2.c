// Mikhail Rudakov, BS19-02
#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Hello, user! Please enter N - number of elements in array:\n");
    scanf("%d", &n);
    if (n <= 0){
        printf("Nothing to do with it! Bye!\n");
        return 0;
    }
    int* array = (int*) calloc(n, sizeof(int)); // initialize array size
    for (int i = 1; i < n; i++){ // fill array with incremental values
        // array[0] = 0 due to calloc use
        array[i] = i;
    }
    printf("Here is your array of integers:\n");
    // print the array
    for (int i = 0; i < n; i++){
        printf("%d ", array[i]);
    }
    // deallocate the memory
    free(array);
    printf("\nMemory is deallocated! Bye!\n");
    return 0;
}

/*
Output for N=10:
Hello, user! Please enter N - number of elements in array:
>> 10
Here is your array of integers:
0 1 2 3 4 5 6 7 8 9 
Memory is deallocated! Bye!
*/