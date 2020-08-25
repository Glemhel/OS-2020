/**
 * 
 * Mikhail Rudakov, BS19-02
 * 
*/

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 105


int main(){
    char str[MAX_LENGTH];
    printf("Input a string of reasonable size (<100):\n");
    fgets(str, MAX_LENGTH, stdin);
    int length = strlen(str);
    printf("Here is your string reversed:\n");
    for (int i = 1; i < length; i++){
        putchar(str[length - i - 1]);
    }
    printf("\n");
    return 0;
}