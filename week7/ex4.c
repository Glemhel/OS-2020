// Mikhail Rudakov, BS19-02
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void* realloc1(void* ptr, size_t size){
    if (ptr == NULL){
        ptr = malloc(size);
        return ptr;
    }
    if (size == 0){
        free(ptr);
        ptr = NULL;
        return ptr;
    }
    void* ptr1;
    if (size < malloc_usable_size(ptr)){
        ptr1 = malloc(size);
        memcpy(ptr1, ptr, size);
    } else {
        ptr1 = malloc(malloc_usable_size(ptr));
        memcpy(ptr1, ptr, malloc_usable_size(ptr));
    }
    free(ptr);
    return ptr1;
}

int main(){
    // testing my realloc
    printf("Testing my realloc function!\n");
    int *a = NULL;
    int n = 10;
    a = realloc1(a, n * sizeof(int)); // this call is equivalent to  a = (int*) malloc(n * sizeof(int))
    printf("Uninitialized array of %d integers:\n", n);
    for (int i = 0; i < n; i++){
        // check that memory is uninitialized
        printf("%d ", a[i]);
        a[i] = i; // initialize memory for future testing
    }
    printf("\nInitialized array to consecutive numbers from 0.\n");
    //printf("\n");
    int n1 = n + 5;
    a = realloc1(a, n1 * sizeof(int));
    printf("Array of %d integers after realloc:\n", n1);
    for (int i = 0; i < n1; i++){
        // check that memory is uninitialized
        printf("%d ", a[i]);
    }
    printf("\nNow we free the memory!\n");
    realloc1(a, 0);
    printf("Done!\n");
    return 0;
}
/*
With n1 = n - 8, output is:
---
Testing my realloc function!
Uninitialized array of 10 integers:
0 0 0 0 0 0 0 0 0 0 
Initialized array to consecutive numbers from 0.
Array of 2 integers after realloc:
0 1 
Now we free the memory!
Done!
---
Which is reasonable.

With n1 = n + 5, output is:
---
Testing my realloc function!
Uninitialized array of 10 integers:
0 0 0 0 0 0 0 0 0 0 
Initialized array to consecutive numbers from 0.
Array of 15 integers after realloc:
0 1 2 3 4 5 6 7 8 9 133377 0 0 0 0 
Now we free the memory!
Done!
---
Which also makes sense. (133377 is some garbage meaning that this is part of unallocated memory)
*/