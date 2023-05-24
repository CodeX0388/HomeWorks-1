#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/sem.h>

void sem_wait(int semid, int sem_num) // не понял в чем проблема тут
{
    struct sembuf op = {sem_num, -1, 0};
    semop(semid, &op, 1);
}

void sem_signal(int semid, int sem_num) 
{
    struct sembuf op = {sem_num, 1, 0};
    semop(semid, &op, 1);
}

int main(int argc, char *argv[])
{
    if (argc != 2) 
    {
        printf("Inappropriate argument count!");
        return 0;
    }
    int N = atoi(argv[1]);
    int sem_id = semget(IPC_PRIVATE, N, IPC_CREAT | 0666);
    if (sem_id == -1) 
    {
        perror("Couldnt create a semaphore!");
        return 0;
    }
    for (int i = 0; i < N; i++)
    {
        if (semctl(sem_id, i, SETVAL, 0) == -1)
        {
            perror("semctl SETVAL");
            return 0;
        }
    }
    for (int i = 0; i < N; i++) 
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("couldnt fork!");
            return 0;
        }
        else if (pid == 0)
        {
            sem_wait(sem_id, i);
            printf("%d\n", i + 1);
            sem_signal(sem_id, (i + 1) % N);
            return 0;
        }
    }
    sem_signal(sem_id, 0);

    for (int i = 0; i < N; i++) 
    {
        wait(NULL);
    }

    if (semctl(sem_id, 0, IPC_RMID) == -1) 
    {
        perror("semctl IPC_RMID");
        return 1;
    }
}
