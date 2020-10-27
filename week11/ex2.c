#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(){

    // set line buffer mode to the stdout (printing)
    setvbuf(stdout, NULL, _IOLBF, NULL);
    char* str = "Hello";
    for (int i = 0; i < strlen(str); i++){
        printf("%c", str[i]);
        sleep(1);
    }

    return 0;
}

/*
Explanation:
Output was as expecteed - 5 seconds of sleep, then Hello altogether. 
It happens this way even without line 11
This happened as in line buffer mode, OS waits till it's full, and only then prints(or when program terminates).
If buffer mode is unbuffered, it prints charachetrs one by one. However, default mode of stdout is not unbuffered,
as we have seen.
*/