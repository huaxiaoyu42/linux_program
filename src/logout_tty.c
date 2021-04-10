#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int logout_tty(char *line){
    int fd;
    struct utmp rec;
    int len = sizeof(struct utmp);
    int retval = -1;

    if((fd = open(UTMP_FILE,O_RDONLY)) == -1){
        return -1;
    }

    while(read(fd,&rec,len) == len){
        if(strncmp(rec.ut_line,line,sizeof(rec.ut_line)) == 0){
            rec.ut_type = DEAD_PROCESS;
            if(lseek(fd,-len,SEEK_CUR)!= -1){
                if(write(fd,&rec,len) == len){
                    retval = 0;
                }
            }
            break;
        }
    }

    if(close(fd) == -1){
        retval = -1;
    }
    return retval;
}