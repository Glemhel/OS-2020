#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define N 20

int main(){
    // open and read from /dev/random
    int randomData = open("/dev/random", O_RDONLY);
    char myRandomData[20];
    read(randomData, myRandomData, sizeof myRandomData);

    // open the file ex1.txt for writing, get size
    int fd2 = open("ex1.txt", O_RDWR, 0);
    struct stat st2;
    fstat(fd2, &st2);
    size_t fsize2 = (size_t)st2.st_size;
    ftruncate(fd2, N);
    // map file ex1.txt to the f2DataPtr to be able to write to it
    unsigned char* f2DataPtr= (unsigned char*)mmap(NULL, fsize2, PROT_WRITE, MAP_SHARED, fd2, 0);
    // copy random data to the file
    memcpy(f2DataPtr, myRandomData, N);
    // close mappings and files
    munmap(f2DataPtr, N);
    close(fd2);
    return 0;
}