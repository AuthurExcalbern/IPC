#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<fcntl.h>

#include<sys/wait.h>

#include<sys/ipc.h>
#include<sys/shm.h>

#define PATHNAME "."
const int PROJ_ID = 65;

sem_t mutex;
sem_t db;

void read_data_base();
void write_data_base();
void readers();
void writers(pid_t, pid_t);

static int comm_shm(int size, int flags);
int create_shm(int size);
int get_shm(int size);

int main(int argc, char *argv[])
{
    pid_t first_child, second_child;
    
    //第二个参数非0, 代表要在多个进程中使用信号量
    //第三参数为信号量的初始值
    sem_init(&mutex, 1, 1);
    sem_init(&db, 1, 1);
    
    //buf[0] record reader numbers
    //buf[1] record data
    int shmid = create_shm(sizeof(int) * 2);
    int* buf;
    buf = shmat(shmid, NULL, 0);
    buf[0] = 0;
    buf[1] = 0;
    
    if((first_child = fork()) < 0)
    {
        printf("fork error");
        exit(0);
    }
    else if(first_child == 0) //first child as reader1
        readers();
    else
    {
        second_child = fork();
        if(second_child == 0) //second child as reader2
            readers();
        else
            writers(first_child, second_child); //parent as writer
    }
    
    /*
    pthread_t reader1, reader2;
    pthread_t writer;
    
    pthread_create(&reader1, 0, readers, NULL);
    pthread_create(&reader2, 0, readers, NULL);
    pthread_create(&writer, 0, writers, NULL);
    
    pthread_join(reader1, 0);
    pthread_join(reader2, 0);
    pthread_join(writer, 0);
    */
    return 0;
}

//读取数据
void read_data_base(int* buf, int counter)
{
    printf("No %d: The Reader_num %d (pid=%ld), Get data %d\n", counter, buf[0], (long)getpid(), buf[1]);
}

//更改数据
void write_data_base(int* buf, int counter)
{
    buf[1]++;
    printf("No %d: Reader_num %d, The Writer(pid=%ld): update data %d\n", counter, buf[0], (long)getpid(), buf[1]);
}

//用来执行有关 shm 的命令
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

//创建共享存储区
//PC_CREAT||IPC_EXCL|0666 保证返回一个新的共享内存标识符，并且指定该共享内存的劝降为0666. 
int create_shm(int size) { return comm_shm(size, IPC_CREAT|IPC_EXCL|0666); }

//得到共享存储区
//PC_CREAT 如果共享内存不存在，则创建并返回，如果存在，则打开并返回其标识符。
int get_shm(int size) { return comm_shm(size, IPC_CREAT); }

//删除共享存储区
int destory_shm(int shmid)
{
    if(shmctl(shmid, IPC_RMID, NULL) < 0)
    {
        perror("destory_shm error.");
        return -1;
    }
    return 0;
}

//读者
void readers()
{
    int counter;
    
    //关联共享存储区
    int shmid = get_shm(0);
    int* buf;
    buf = shmat(shmid, NULL, 0);
    
    for(counter = 0; counter < 150; counter++)
    {
        //互斥更改读者人数
        sem_wait(&mutex);
        buf[0] = buf[0] + 1;
        if(buf[0] == 1) sem_wait(&db); //当有一个读者就要锁住数据区
        sem_post(&mutex);
        
        read_data_base(buf, counter);
        
        sem_wait(&mutex);
        buf[0] = buf[0] - 1;
        if(buf[0] == 0) sem_post(&db);
        sem_post(&mutex);
    }
    
    //去关联
    shmdt(buf);
    
    exit(0);
}

void writers(pid_t first_child, pid_t second_child)
{
    int counter;
    
    int shmid = get_shm(0);
    int* buf;
    buf = shmat(shmid, NULL, 0);

    for(counter = 0; counter < 200; counter++)
    {
        sem_wait(&db);
        write_data_base(buf, counter);
        sem_post(&db);
    }
    
    //等待子进程结束
    waitpid(first_child, NULL, 0);
    waitpid(second_child, NULL, 0);
    
    //输出结束时的读者人数和数据内容
    printf("Reader: %d  Data: %d\n", buf[0], buf[1]);
    
    //去关联
    shmdt(buf);
    
    //删除共享存储区
    destory_shm(shmid);
    
    exit(0);
}