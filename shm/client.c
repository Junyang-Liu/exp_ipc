#include"comm.h"

int main()
{
    int shmid = GetShm(4096);
    if(shmid<0)
    {
        printf("shmid not find\n");
        return -1;
    }
    sleep(1);
    char *addr = shmat(shmid,NULL,0);
    sleep(2);
    int i = 0;
    while(i++ < 6)
    {
        printf("client# %s\n",addr);
        sleep(1);
    }
    shmdt(addr);
    sleep(2);
    return 0;
}
