#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(){
    for (int i = 0; i < 10; i++){
        void* meme = malloc(1024 * 1024 * 100); // allocate 100 mb
        memset(meme, 0, 1024 * 1024 * 100);// fill
        int who = RUSAGE_SELF;
        struct rusage usage;
        int ret;
        ret = getrusage(who, &usage);// print memory usage
        printf("%ld\n", usage.ru_maxrss);
        sleep(1); // sleep
    }

    return 0;
}

/*
Ouput of the program:
103420
206324
308756
410924
513356
615788
718220
820652
923084
1025516

The memory is used and we now can measure usage :)
*/