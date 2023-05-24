#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>


int main() 
{
  key_t key = ftok("file.txt", 5);
  if (key == -1) 
  {
        perror("Failed generating a key");
        exit(EXIT_FAILURE);
  }
  int shmid = shmget(key, 0, 0);
  if (shmid == -1)
  {
        perror("Failed getting a shared memory segment");
        exit(EXIT_FAILURE);
  }
  int res = shmctl(shmid, IPC_RMID, NULL);
  if (res == -1) 
  {
        perror("Failed to mark shared memory segment for removal");
        exit(EXIT_FAILURE);
  }
  if (remove("file.txt") == -1) 
  {
        perror("Failed to remove file");
        exit(EXIT_FAILURE);
  }
  return 0;
}
