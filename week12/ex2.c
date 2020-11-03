#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    // read from stdin
    FILE* input = fopen(stdin, "r");
    char output;
    int a = 0;
    // set append flag
    if(argc > 1 && strcmp(argv[1], "-a") == 0)
        a = 1;
    // arrays of files to write in
    FILE* fs[argc - 1 - a];
    char* append_policy  = (a == 1 ? "a" : "w");
    for (int i = a + 1; i < argc; i++){
        // open each file accoding to the append policy
        fs[i - a - 1] = fopen(argv[i], append_policy);
    }
    // read byte-at-a-time and write to the files
    while(read(input, &output, 1) != 0){
        printf("%c", output); // print to the stdout
        // write to the stdout
        for (int i = a + 1; i < argc; i++){
            fprintf(fs[i - a - 1], "%c", output);
        }
    }
    // close all files
    for (int i = a + 1; i < argc; i++){
        fclose(fs[i - a - 1]);
    }
    return 0;
}