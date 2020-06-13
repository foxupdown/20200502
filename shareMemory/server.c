
// server:读取共享内存图像数据
#include "head.h"
 
static int SHMID = 0;
static unsigned char *ADDR = NULL;
 
void main()
{
	int iLoop = 5;
	int date = 0;
	FILE *img = NULL;
 
	// 初始化共享内存
	SHMID = CreateShm(4096+1);
	if(SHMID==-1)
	{
		printf("create share memory failed!\n");
		exit(1);
	}
	
	ADDR = shmat(SHMID, NULL, 0);
	
	printf("init server share memory succeed, shmid = %d\n", SHMID);
	
	while((img = fopen("/home/fxhui/IPC/ipc_pv_img/new.jpg", "wb")) == NULL && iLoop)
	{
		printf("open file failed!, [%d]\n", iLoop);
		iLoop--;
		sleep(1);
	}
	
	// 信号同步
	int semid;
	int b = 0;
	
	if((semid = initsem(0x200)) < 0)
	{
		printf("server init sem error!\n");
		exit(1);
	}
	int fwriteSize = 0;
	while(1)
	{
		if(ADDR[4096] == 'b')
		{
			fwriteSize = fwrite(ADDR, 1, 4096, img);
			ADDR[4096] = 'a';
			printf("fwriteSize = %d\n", fwriteSize);
		}
		if(ADDR[4096] == 'c')
		{
			fwriteSize = fwrite(ADDR, 1, 731, img);
			printf("fwriteSize = %d\n", fwriteSize);
			break;
		}
	}
	
/* 方式二
	while(1)
	{
		if(ADDR[4096] == 'b')
		{
			b = atoi(ADDR);
			printf("recv data = [%d]\n", b);
			fputc(b, img);
			ADDR[4095] = 'a';
		}
		if(ADDR[4096] == 'c')
			break;
	}
*/	
	fclose(img);	
	
	shmdt(ADDR);
	DestroyShm(SHMID);	  // 销毁IPC
}