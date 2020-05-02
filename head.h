#ifndef __HEAD__H
#define __HEAD__H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "semaphore.h"
union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
																				(Linux-specific) */
};
typedef struct shmhead{
	unsigned int blksize;
	unsigned int blocks;
	unsigned int rd_index;
	unsigned int wr_index;
}shmhead_s;
typedef struct shmfifo{
	shmhead_s *p_shmhead;
	char *p_payload;
	int shmid;
	int shm_mutex;
	int shm_full;
	int shm_empty;
}shmfifo_s;
#endif
