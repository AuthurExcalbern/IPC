#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<fcntl.h>

#include<sys/ipc.h>
#include<sys/shm.h>

#define PATHNAME "."
const int PROJ_ID = 65;

static int comm_shm(int size, int flags)
{
    key_t _key = ftok(PATHNAME, PROJ_ID);
    if(_key < 0)
    {
        perror("ftok error");
        return -1;
    }
    
    int shmid = shmget(_key, size, flags);
    if(shmid < 0)
    {
        perror("shmid");
        return -2;
    }
    
    return shmid;
}

int create_shm(int size) { return comm_shm(size, IPC_CREAT|IPC_EXCL|0666); }

int get_shm(int size) { return comm_shm(size, IPC_CREAT); }

int destory_shm(int shmid)
{
    if(shmctl(shmid, IPC_RMID, NULL) < 0)
    {
        perror("destory_shm error.");
        return -1;
    }
    return 0;
}

int main(void)
{
    int shmid = get_shm(0);
    int* buf;
    buf = shmat(shmid, NULL, 0);
    
    destory_shm(shmid);
    printf("OK\n");
    return 0;
}
    
    