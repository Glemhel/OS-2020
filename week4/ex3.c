// Mikhail Rudakov, BS19-02
#include <stdio.h>
#include <sys/types.h>

// In this task, simplistic shell is implemented. It invites user to type some commands, executes them, and ends
// when user types a command which start with 'end'

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