#include<stdio.h>
#include<sys/stat.h>

/**
 * 获得文件的大小
*/

int main(){

    struct stat infobuf;

    if(stat("/etc/passwd",&infobuf) == -1){
        perror("/etc/passwd");
    }else{
        printf("The size of /etc/passwd is %ld\n",
        infobuf.st_size);
    }

    return 0;
}