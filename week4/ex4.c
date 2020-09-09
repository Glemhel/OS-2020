// Mikhail Rudakov, BS19-02
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// In this task, simplistic shell from ex3 is further improved. It is now able to handle commands with parameters 
// and to run processes in background. By the way, it is the same as the third task.

int main(){
    printf("Hello! This is Mikhail's simplistic shell! Type some commands!\nType \"end\" to exit this shell\n");
    while (2){
        printf("Your next command:\n");
        char input[100];
        fgets(input, 100, stdin);
        if (input[0] == 'e' && input[1] == 'n' && input[2] == 'd'){
            printf("See you next time!\n");
            return 0;
        } else {
            int ret = system(input);
        }
    }
    return 0;
}