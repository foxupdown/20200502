// client:写入共享内存图像数据
#include "head.h"
 
static int SHMID = 0;
static unsigned char *ADDR = NULL;
 
int main()
{
	// 获取共享内存
	int iLoop = 5;
	SHMID = GetShm(4096+1); // 获取IPC键值：申请4096+1个字节的内存
	ADDR = shmat(SHMID, NULL, 0);	// 共享内存映射到进程页表
	printf("client init share memory succeed, SHMID = %d\n", SHMID);
	
	// 准备传送的数据
	FILE *img;
	char path[100] = { 0 };
	snprintf(path, 100, "%s", "/home/fxhui/IPC/ipc_pv_img/LF.jpg");
	while((img = fopen(path, "rb")) == NULL && iLoop)
	{
		printf("open file failed!, [%d]\n", iLoop);
		iLoop--;
		sleep(1);
	}
	
	fseek(img, 0, SEEK_END);
	int len = ftell(img);
	int m = len / 4096;
	int n = len % 4096;	
	fseek(img, 0, SEEK_SET);
	
	printf("%d %d \n", m ,n);
 
	// 信号同步
	int semid;
	if((semid=initsem(0x200)) < 0)
	{
		printf("server init sem error!\n");
		exit(1);
	}
	unsigned char *buffer;
	int freadSize = 0;
	buffer = (unsigned char *)malloc(sizeof(unsigned char)*4096);
	ADDR[4096] = 'a';
	while(1)
	{
		if(ADDR[4096] == 'a' && m--)
		{
			freadSize = fread(ADDR, 1, 4096, img);
			ADDR[4096] = 'b';
			printf("m = %d, freadSize = %d\n", m, freadSize);
		}
		if(m == 0)
		{
			sleep(1);
			ADDR[4096] = 'c';
			freadSize = fread(ADDR, 1, n, img);
			printf("m = %d, freadSize = %d\n", m, freadSize);
			printf("图像读取完毕!\n");
			break;
		}
	}
/*	int c = 0;
	ADDR[4095] = 'a';
	while(1)
	{
		if(ADDR[4095] == 'a')
		{
			if((c=fgetc(img))!= EOF)
			{
				printf("read date : [%d]\n",c);
				sprintf(ADDR,"%d",c);
				ADDR[4095] = 'b';
			}
			else
			{	
				ADDR[4095] = 'c';
				printf("图像读取完毕!\n");
				break;
			}
		}
	}
*/	
	free(buffer);
	sleep(1);
	fclose(img);
	shmdt(ADDR);
	
	return 0;
}
