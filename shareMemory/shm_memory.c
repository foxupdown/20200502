#include "head.h"
struct sendMsg{
	char send[64];
	int flag;
};
void main()
{
	struct sendMsg msg;
	strcpy(msg.send , "hello world");
	msg.flag = 1;
	int shmid = shmget(1234 , sizeof(struct sendMsg) , IPC_CREAT | 0666);
	if(-1 == shmid){
		printf("fail to shmget msg\n");
		return ;
	}
	struct sendMsg *pMsg = shmat(shmid , NULL , 0);
	if((void *)(-1) == pMsg)
	{
		printf("fail to shmat\n");
		return ;
	}
	memcpy(pMsg , &msg , sizeof(struct sendMsg));
	shmdt(pMsg);
	while(1);
}
