#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(){
    // open the file ex1.txt for reading, get size
    int fd1 = open("ex1.txt", O_RDONLY, 0);
    struct stat st1;
    fstat(fd1, &st1);
    size_t fsize1 = (size_t)st1.st_size;

    // open the file ex1.memcpy.txt for writing, get size
    int fd2 = open("ex1.memcpy.txt", O_RDWR, 0);
    struct stat st2;
    fstat(fd2, &st2);
    size_t fsize2 = (size_t)st2.st_size;

    
    ftruncate(fd2, fsize1);
    // map file ex1.txt to the dataPtr to be able to read from it
    unsigned char* f1DataPtr= (unsigned char*)mmap(NULL, fsize1, PROT_READ, MAP_SHARED, fd1, 0);

    // map file ex1.memcpy.txt to the f2DataPtr to be able to write to it
    unsigned char* f2DataPtr= (unsigned char*)mmap(NULL, fsize2, PROT_WRITE, MAP_SHARED, fd2, 0);

    // copy from f2 to f1 - from ex1.txt to ex1.memcpy.txt
    memcpy(f2DataPtr, f1DataPtr, fsize1);

    // close mappings and files
    munmap(f1DataPtr, fsize1);
    munmap(f2DataPtr, fsize1);
    close(fd1);
    close(fd2);
    return 0;
}