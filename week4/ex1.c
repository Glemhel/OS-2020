// Mikhail Rudakov, BS19-02
#include <stdio.h>
#include<sys/types.h>

int main(){
    int n = fork();
    // choose between child and parent processes
    if (n != 0){
        printf("Hello from parent [PID - %d]\n", getpid());
    } else {
        printf("Hello from child [PID - %d]\n",  getpid());
    }
    return 0;
}

// Result: parent's and child's outputs are mixed sometimes.
/**
 * 
Hello from parent [PID - 8111]
Hello from child [PID - 8112]
Hello from parent [PID - 8113]
Hello from child [PID - 8114]
Hello from parent [PID - 8115]
Hello from child [PID - 8116]
Hello from parent [PID - 8117]
Hello from child [PID - 8118]
Hello from parent [PID - 8119]
Hello from child [PID - 8120]
Hello from child [PID - 8122]
Hello from parent [PID - 8121]
Hello from parent [PID - 8123]
Hello from child [PID - 8124]
Hello from parent [PID - 8125]
Hello from child [PID - 8126]
Hello from parent [PID - 8127]
Hello from child [PID - 8128]
Hello from parent [PID - 8129]
Hello from child [PID - 8130]
**/

// This happens due to the reason that operating system runs both processes concurrently, thus we do not know the order
// of the processes internally. Due to that scheme of execution by OS, this uncertainty happens.

