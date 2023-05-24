#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <unistd.h>

int main() 
{
  int fd = open("file.txt", O_CREAT | O_TRUNC, S_IRWXU);
  if(fd == -1)
  {
    perror("Failed creating a file");
    exit(EXIT_FAILURE);
  }
  key_t key = ftok("file.txt", 5);
  if (key == -1) 
  {
        perror("Failed generating a key");
        exit(EXIT_FAILURE);
    }
  int shm_id = shmget(key, 1024, IPC_CREAT | IPC_EXCL);
  if (shm_id == -1) 
  {
        perror("Failed creating a shared memory segment");
        exit(EXIT_FAILURE);
  }
  return 0;
}
