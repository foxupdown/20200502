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
	int semid = semget(key , 1 ,IPC_CREAT | IPC_EXCL | 0666 );
	if(-1 == semid)
	{
		printf("failt to creat\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;

}
int sem_open_t(key_t key)
{
	int semid = semget(key , 0 , 0);
	if(-1 == semid)
	{
		printf("failt to sem open\n");
		return EXIT_FAILURE;
	}
}
int sem_setval(int semid , int val)
{
	union semun su;
	su.val  = val;
	int ret = semctl(semid , 0 , SETVAL , su);
	if(ret == -1)
	{	
		printf("failt to sem SETVAL\n");
		return EXIT_FAILURE;
	}
}
int sem_d(int semid)
{
	int ret = semctl(semid , 0 , IPC_RMID , 0);
	if(-1 == ret)
	{
		printf("failt to semctl\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int sem_p(int semid)
{
	struct sembuf sb = {0 , -1 , 0};
	int ret = semop(semid , &sb , 0); // IPC_NOWAIT , SEM_UNDO
	if(-1 == ret)
	{
		printf("failt to sem p\n");
		return  EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
int sem_v(int semid)
{
	struct sembuf sb = {0 , 1 , 0};
	int ret = semop(semid , &sb , 0);
	if(-1 == ret)
	{
		printf("failt to sem v\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
void main()
{
	int semid ; 
	semid = sem_create(1234);
	sleep(2);
	//sem_d(semid);
}
