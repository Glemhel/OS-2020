// Mikhail Rudakov, BS19-02
#include <stdio.h>
#include<sys/types.h>

int main(){
    int pid = getpid();
    printf("%d\n", pid);
    for (int i = 0; i < 5; i++){
        fork();
    }
    sleep(5);
    return 0;
}

/**
 * Result of execution with 5 fork calls (part that is important for us):
    ex2─┬─ex2─┬─ex2─┬─ex2─┬─ex2───ex2
    │     │     │     └─ex2
    │     │     ├─ex2───ex2
    │     │     └─ex2
    │     ├─ex2─┬─ex2───ex2
    │     │     └─ex2
    │     ├─ex2───ex2
    │     └─ex2
    ├─ex2─┬─ex2─┬─ex2───ex2
    │     │     └─ex2
    │     ├─ex2───ex2
    │     └─ex2
    ├─ex2─┬─ex2───ex2
    │     └─ex2
    ├─ex2───ex2
    └─ex2
 * 
 * As we see, 32 processes are created and executed. This makes sense as 2 ** 5 = 32 processes are created by 5 forks.
 * Tree of forks is printed with pstree command. This is a binary tree as in each time when we call fork(), 
 * process branches into 2 processes.
 **/