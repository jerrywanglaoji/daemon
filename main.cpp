
#include <unistd.h>
#include <fcntl.h>
#include <syslog.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>

void init_daemon()
{
    int pid;
    int i;

    //创建子进程，并结束父进程
    //保证进程不是进程组组长进程
    if ((pid = fork()) < 0){
        exit(1);
    }
    else if (pid != 0)
        exit(0);

    //创建一个会话，会话只包含子进程，企鹅子进程是会话首进程
    setsid();

    //再次创建子进程，并结束父进程
    //保证守护进程不是会话首进程，这样open的时候不会被分配终端
    if((pid = fork()) < 0){
        exit(1);
    }
    else if (pid != 0)
        exit(0);

    if (chdir("/") < 0){
        exit(2);
    }
}

int main()
{
    init_daemon();
    return 0;
}

