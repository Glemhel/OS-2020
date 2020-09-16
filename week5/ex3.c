// Mikhail Rudakov, BS19-02
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define N 10 // size of the buffer

char buf[N];
int in=0, out=0; // indicies of the buffer to read and to write
int chars=0, space=N;
pthread_t consumer_id, producer_id;

void send(char c){
    while (space == 0){
        // wait as no space for writing, sleep
    }
    buf[in] = c;
    in = (in + 1) % N;
    chars += 1; // wakeup signal that another char is written
}

char recieve(){
    char c;
    while (chars == 0){
        // wait as nothing to read yet, sleep
    }
    c = buf[out];
    out = (out + 1) % N;
    space += 1; // wakeup signal that one more place is available now
    return c;
}

void* producer(void* args){
    // produces a lot of chars
    char c = 'a';
    int shift = 0;
    int counter = 0;
    while (1 == 1){
        char to_send = c + shift;
        send(to_send);
        shift = (shift + 1) % 26;
        if (counter % 1000000000 == 0){
            printf("We producer %c\n", to_send);
        }
        counter++;
    }
}

void* consumer(void* args){
    // consumes a lot of chars and prints some of them
    int counter = 0;
    while (1 == 1){
        char got = recieve();
        if (counter % 1000000000 == 0){
            printf("We consumed %c\n", got);
        }
        counter++;
    }
}

int main() {
    pthread_create(&producer_id, NULL, producer, NULL);
    pthread_create(&consumer_id, NULL, consumer, NULL);
    pthread_join(consumer_id, NULL); // wait till consumer is done, only after it we terminate
    return 0;
}