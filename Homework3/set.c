#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main()
{
    key_t key = ftok("file.txt", 5);
    if (key == -1) {
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
        perror("Failed attaching shared memory segment");
        exit(EXIT_FAILURE);
    }
    char input[1024];
    while (fgets(input,1024, stdin)) {
        strncpy(d, input, 1024-1);
        d[1024-1] = '\0';
    }
   if (shmdt(d) == -1) {
        perror("Failed detaching a shared memory segment");
        exit(EXIT_FAILURE);
    }
}
