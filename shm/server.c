#include"comm.h"

int main()
{
  int shmid = CreateShm(4096);

  char *addr = shmat(shmid,NULL,0);
  sleep(2);
  int i = 0;
  while(i < 6)
  {
      addr[i] = 'A' + i;
      i++;
      addr[i] = 0;
      sleep(1);
  }
  shmdt(addr);
  sleep(2);
  DestroyShm(shmid);
  printf("server stop...");
  return 0;
}
