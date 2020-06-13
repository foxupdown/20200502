#include "head.h"
#include "pthread.h"

struct msg{
	struct msg *next;
};
struct msg *work = NULL;
struct msg *mp = NULL;
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;
void *process_work(void *arg)
{
	struct msg *mp;
	while(1)
	{
		pthread_mutex_lock(&qlock);
		while(work == NULL)
			pthread_cond_wait(&qready , &qlock);
		mp = work;
		work = mp -> next;
		pthread_mutex_unlock(&qlock);

	}
}
void *product_work(void *arg)
{
	pthread_mutex_lock(&qlock);
	mp -> next = work;
	work = mp;
	pthread_mutex_unlock(&qlock);
	pthread_cond_signal(&qready);
}
void main()
{
	pthread_t ptid, ctid;
 	mp =(struct msg *) malloc(sizeof(struct msg));
    pthread_create(&ptid, NULL, product_work, NULL);
	pthread_create(&ctid, NULL, process_work, NULL);
    //主线程回收两个子线程
	pthread_join(ptid, NULL);
    pthread_join(ctid, NULL);
}
