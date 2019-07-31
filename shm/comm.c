#include"comm.h"

static int CommShm(int size,int flags)
{
	key_t key = ftok(PATHNAME,PROJ_ID);
	if(key < 0)
	{
		printf("ftok");
		return -1;
	}

	int shmid = 0;
	// 有就返回，没有就直接创建，暂忽略生产消费问题
	if((shmid = shmget(key,size,flags)) < 0)
	{
		printf("shmget");
		return -2;
	}
	return shmid;
}

int DestroyShm(int shmid)
{
	if(shmctl(shmid,IPC_RMID,NULL) < 0)
	{
		printf("shmctl");
		return -1;
	}
	return 0;
}

int CreateShm(int size)
{
	return CommShm(size,IPC_CREAT);
}

int GetShm(int size)
{
	return CommShm(size,IPC_CREAT);
}

