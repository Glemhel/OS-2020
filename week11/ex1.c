#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

// string in ex1.txt was created truly randomly, with the use of this command:
// tr -dc A-Za-z0-9 </dev/urandom | head -c 40 > ex1.txt
int main(){
    // open the file, get size
    int fd = open("ex1.txt", O_RDWR, 0);
    struct stat st;
    fstat(fd, &st);
    size_t fsize = (size_t)st.st_size;

    // string to put into file
    char* str = "This is a nice day";

    // truncate file to the size of the string so that it perfectly fits
    ftruncate(fd, strlen(str));

    // map file to the dataPtr to be able to write
    unsigned char* dataPtr = (unsigned char*)mmap(NULL, fsize, PROT_WRITE, MAP_SHARED, fd, 0);

    // copy from str to dataPtr - rewrite ex1.txt, in fact
    memcpy(dataPtr, str, strlen(str));

    // close mapping and file
    munmap(dataPtr, strlen(str));
    close(fd);
    return 0;
}