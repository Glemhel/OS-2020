#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

// size of the entry table
#define N 1000


int main(){
    DIR* mydir = opendir("/home/mikhail/OS2020/week10/tmp");
    struct dirent* entry;
    struct dirent* files[N];
    int checked[N];
    int sz = 0;
    int i = 0;
    // read next entry in directory while exists
    while ((entry = readdir(mydir)) != NULL){
        files[i] = entry;
        i++;
    }
    sz = i;
    for (int i = 0; i < sz; i++){
        //check given inode if needed
        struct stat buff;
        stat(files[i]->d_name, &buff);
        // given entry should be unchecked yet, have >=2 hard links and not be "." or ".."
        if (checked[i] == 0 && buff.st_nlink >= 2 && strcmp(".", files[i]->d_name) 
            && strcmp("..", files[i]->d_name)){
            printf("Files with inode number = %d in this directory are:\n", files[i]->d_ino);
            for (int j = 0; j < sz; j++){
                if (files[j]->d_ino == files[i]->d_ino){
                    printf("\t%s\n", files[j]->d_name);
                    checked[j] = 1;
                }
            }
            printf("--done--\n");  
        }
    }
    (void)closedir(mydir);
    return 0;
}