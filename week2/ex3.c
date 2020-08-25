/**
 * 
 * Mikhail Rudakov, BS19-02
 * 
*/

#include <stdio.h>

int main(int argc, char** argv){
    int n = -1;
    if (argc == 2 && sscanf(argv[1], "%d", &n)){
        printf("Congratulations! Here is your triangle:\n");
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n - 1 - i; j++)
                putchar(' ');
            for (int j = n - 1 - i; j < n - 1; j++)
                putchar('*');
            putchar('*');
            for (int j = n - 1 - i; j < n - 1; j++)
                putchar('*');
            for (int j = 0; j < n - 1 - i; j++)
                putchar(' ');
            printf("\n");
        }
    } else {
        printf("Wrong number of parameters");
    }
    return 0;
}