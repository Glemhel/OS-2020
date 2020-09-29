#include <stdio.h>

int main(){
    char **s = (char **) malloc(sizeof(char*));
    char foo[] = "Hello World";
    *s = foo;
    printf("s is %p\n", s);
    s[0] = foo;
    printf("s[0] is %s\n", s[0]);
    return(0);
}
/*
    No segfaults are thrown, output is
    ---
    s is 0x55ca82cba2a0
    s[0] is Hello World
    ---
    Which is fine: first line is address of first element of array of strings,
                   second line is first element itself(which is string indeed).
*/