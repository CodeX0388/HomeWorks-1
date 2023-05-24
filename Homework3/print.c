#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>

int main()
{
    key_t key = ftok("file.txt", 5);
    if (key == -1) 
    {
        perror("Failed generating a key");
        exit(EXIT_FAILURE);
    }
    int shm_id = shmget(key, 1024, 0);
    if (shm_id == -1) {
        perror("Failed getting a shared memory segment");
        exit(EXIT_FAILURE);
    }
    char *d = (char*)shmat(shm_id, NULL, 0);
    if (d == (char*)(-1)) {
        perror("Failed attaching a shared memory segment");
        exit(EXIT_FAILURE);
    }
    while (true) {
        printf("%s\n", d);
        sleep(5);
    }
    if (shmdt(d) == -1) {
        perror("Failed detaching a shared memory segment");
        exit(EXIT_FAILURE);
    }
}
