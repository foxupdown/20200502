#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
int main()
{
	pid_t pid ;
	int fd[2];
	int ret = pipe(fd);
	char buff[512] = {0};
	bzero(buff , 512);
	if(-1 == ret)
	{
		printf("fail to pipe\n");
		return -1;
	}
	pid = fork();
	if(-1 == pid)
	{
		printf("fail to fork\n");
		return -1;
	}
	if(0 == pid)
	{
		printf("hello world pid 0\n");
		strcpy(buff , "hello world");
		write(fd[1] , buff , strlen(buff));
		strcpy(buff , "hello world1");
		write(fd[1] , buff , strlen(buff));
		strcpy(buff , "hello world2");
		write(fd[1] , buff , strlen(buff));
		strcpy(buff , "hello world3");
		write(fd[1] , buff , strlen(buff));
		printf("__ccs__ strlen\n");
		sleep(3);
	}
	else if(pid > 0)
	{
		read(fd[0] , buff , sizeof(buff));
		printf("buff is %s\n",buff);
		read(fd[0] , buff , sizeof(buff));
		printf("buff is %s\n",buff);
		read(fd[0] , buff , sizeof(buff));
		printf("buff is %s\n",buff);
		read(fd[0] , buff , sizeof(buff));
		printf("buff is %s\n",buff);
	}

	return 0;
}
