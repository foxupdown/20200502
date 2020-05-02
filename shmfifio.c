#include "head.h"
union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
								(Linux-specific) */
};
int sem_create(key_t key)
{
	int sem_id = semget(key , 1 , IPC_CREAT | IPC_EXCL | 0666 );
	if(sem_id == -1){
		printf("fail to sem_create\n");
		return -1;
	}
	return 0;
}
int sem_open(key_t key)
{
	int sem_id = semget(key , 0 , 0);
	if(-1 == sem_id)
	{
		printf("fail to sem_open\n");
		return -1;
	}
	return 0;
}

int sem_setval(int sem_id , int val_t)
{
	union semun semunion;
	semunion.val = val_t;
	int ret = semctl(semid , 0 , SETVAL , semunion);
	if(-1 == ret)
	{
		printf("fail to sem_setval\n");
		return -1;
	}
	return 0;
}
int sem_p()
{

}
int sem_v()
{
	
}
shmfifo_s* shmfifo_init(int key , int blksize , int blocks)
{
	shmfifo_s *shmfifo =(shmfifo_s*)malloc(sizeof(shmfifo_s));
	if(shmfifo){
		printf("fail to get shmfifo\n");
		return NULL;}
	bzero(shmfifo , sizeof(shmfifo_s));
	int shmid = shmget(key , 0 , 0);
	int size = sizeof(shmhead_s) + blksize * blocks;
	if(-1 == shmid)
	{
		if(-1 == (shmfifo->shmid = shmget(key , size , IPC_CREAT | 0666)))
		{	
			printf("fail to shmget %d\n",__LINE__);
			return NULL;
		}
	}
	else
		shmfifo->shmid = shmid;
	shmfifo->p_shmhead =(shmhead_s *)shmat(shmfifo -> shmid , NULL , 0);
	if((shmhead_s*)-1 == shmfifo->p_shmhead)
	{
		printf("shmat fail %d\n",__LINE__);
		return NULL;
	}
	shmfifo -> p_payload = (char *)(shmfifo -> p_shmhead + 1);
	shmfifo->shm_mutex = sem_create(key);
	shmfifo->shm_full = sem_create(key + 1);
	shmfifo->shm_empty = sem_create(key + 2);

	sem_setval(shmfifo->shm_mutex , 1);
	sem_setval(shmfifo->shm_full , blocks);
	sem_setval(shmfifo->shm_empty , 0);	
	return shmfifo;
}
void shmfifo_put(shmfifo_s *fifo , const void *buf)
{
	sem_wait(fifo -> shm_full);
	sem_wait(fifo -> shm_mutex);
 
	sem_post(fifo -> shm_full);
	sem_post(fifo -> shm_mutex);
}
void shmfifo_get(shmfifo_s *fifo , char *buf)
{

}
void shmfifo_destory(shmfifo_s *fifo)
{
	
}
int main()
{
	printf("__ccs__ \n");
	return 0;
}


