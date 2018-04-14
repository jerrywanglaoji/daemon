
#include <unistd.h>
#include <fcntl.h>
#include <syslog.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <string.h>

//令该进程变成守护进程
void init_daemon()
{
    int pid;
    int i;

    //创建子进程，并结束父进程
    //保证进程不是进程组组长进程
    if ((pid = fork()) < 0){
        printf("fork error\n");
        exit(1);
    }
    else if (pid > 0)
        exit(0);

    printf("fork success\n");

    //创建一个会话，会话只包含子进程，其子进程是会话首进程
    setsid();

    //改变当前工作目录为根目录
    chdir("/");

    //设置文件权限掩码
    umask(0);

    printf("set success\n");

    for(i = 0; i < getdtablesize(); ++i)
    {
        //关闭文件权限描述符
        close(i);
    }

    printf("close success\n");

}

void func_do()
{
    char buf[] = "This is a daemon\n";
    int fd;

    while(1)
    {
        if (fd = open("/home/jerry/git/daemon/daemon.log", O_CREAT|O_WRONLY|O_APPEND, 0600) < 0)
        {
            printf("open file error\n");
            exit(1);
        }
        write(fd, buf, strlen(buf) +1);
        close(fd);
        sleep(3);
    }
}

int main()
{
    init_daemon();
    func_do();
    return 0;
}

