// Mikhail Rudakov, BS19-02
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define NUM_THREADS 5 // number of threads to test on

pthread_t thread_id[NUM_THREADS]; // array with threads id's

void* Boo(int* i) {
    printf("    Boo! I'm thread %d - I was born in iteration %d !\n",
        (int) pthread_self(), *i);
    return (*i + 10); // pthread_exit(NULL) is not needed in this case
}

int main() { 
    int rc, i;
    printf("I am main thread %d. I will do something now.\n", (int) pthread_self());
    for (i = 0; i < NUM_THREADS; i++) {
        //Create a new thread that will execute 'Boo'
        int a;
        rc = pthread_create(&thread_id[i], NULL, Boo, &i);
        pthread_join(thread_id[i], &a); // wait for thread thread_id[i] to finish execution
        printf("Created new thread (%d) in iteration %d and it returned %d\n",
            (int) thread_id[i], i, a);
        if (rc) {         
            printf("\nERROR: return code from pthread_create is %d \n", rc);         
            exit(1);      
        }
    }
    sleep(1);
    pthread_exit(NULL); // exit the main thread
}

// Results
/**
 * This is typical output of this program:
 * 
 *  I am main thread 1584957248. I will do something now.
        Boo! I'm thread 1584953088 - I was born in iteration 0 !
    Created new thread (1584953088) in iteration 0 and it returned 10
        Boo! I'm thread 1584953088 - I was born in iteration 1 !
    Created new thread (1584953088) in iteration 1 and it returned 11
        Boo! I'm thread 1584953088 - I was born in iteration 2 !
    Created new thread (1584953088) in iteration 2 and it returned 12
        Boo! I'm thread 1584953088 - I was born in iteration 3 !
    Created new thread (1584953088) in iteration 3 and it returned 13
        Boo! I'm thread 1584953088 - I was born in iteration 4 !
    Created new thread (1584953088) in iteration 4 and it returned 14
 * 
 * We see that thread's id's are equal, although we definitely create several threads. However, as we use pthread_join,
 * thread has finished it's execution and when the new thread is created, it takes the same id as the previous, already exited one.
 * This is not an error, but just an observation.
 * Due to pthread_join,the output is not mixed: coroutine by created thread is run, and then message with the results is printed
 * in them main thread
 **/