#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

/**
 * 实现linux who 命令的功能
*/

void showtime(long timeval){
    char *time = ctime(&timeval);
    printf("%12.12s\t",time);
}


void print_record(struct utmp *record){
    //显示登陆的用户名
    printf("%s\t",record->ut_user);
    //显示登陆的设备
    printf("%s\t",record->ut_line);
    
    showtime(record->ut_tv.tv_sec);

    //显示登陆的ip地址
    printf("(%s)\t",record->ut_host);
    printf("\n");
}

int main(){

    struct utmp record;
    int size = sizeof(record);
    int fd;

    /**
     * 判断文件是否成功打开
    */
    if((fd = open(UTMP_FILE,O_RDONLY)) == -1){
        printf("open file error\n");
        return 0;
    }

    /**
     * 循环读取文件中的记录
    */
    while(read(fd,&record,size) == size){
        if(record.ut_type == USER_PROCESS){
            print_record(&record);
        }

    }

    /**
     * 释放文件描述符
    */
    close(fd);


    return 0;
}