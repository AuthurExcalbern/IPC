#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<sched.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

int reader_num = 0;
int data_base;

void read_data_base();
void write_data_base();
void * readers();
void * writers();


int main(int argc, char *argv[])
{
    int err;
    
    pthread_t reader1, reader2, reader3, reader4;
    pthread_t writer;
    void *r_tret1, *r_tret2, *w_tret;
    
    err = pthread_rwlock_init(&rwlock, NULL);
    if(err != 0)
        return (err);
    
    pthread_create(&reader1, NULL, readers, NULL);
    pthread_create(&reader2, NULL, readers, NULL);
    pthread_create(&reader3, NULL, readers, NULL);
    pthread_create(&reader4, NULL, readers, NULL);
    pthread_create(&writer, NULL, writers, NULL);
    
    pthread_join(reader1, &r_tret1);
    pthread_join(reader2, &r_tret2);
    pthread_join(reader3, NULL);
    pthread_join(reader4, NULL);
    pthread_join(writer, &w_tret);
    /*
    printf("Reader1 exit code %ld\n", (long)r_tret1);
    printf("Reader2 exit code %ld\n", (long)r_tret2);
    printf("Writer exit code %ld\n", (long)w_tret);
    */
    return 0;
}

void read_data_base(int reader_num)
{
    printf("The Reader_num %d, Get data %d\n", reader_num, data_base);
    sleep(1);
}

void write_data_base()
{
    data_base++;
    printf("The Writer: update data %d\n", data_base);
    sleep(1);
}


void *readers()
{
    while(1)
    {
        sleep(0);//sched_yield();
        
        pthread_mutex_lock(&mutex);
        reader_num = reader_num + 1;
        pthread_mutex_unlock(&mutex);
        
        //因为不需要对读者数目进行修改，所以不用互斥锁
        pthread_rwlock_rdlock(&rwlock);
        read_data_base(reader_num);
        pthread_rwlock_unlock(&rwlock);
        
        pthread_mutex_lock(&mutex);
        reader_num = reader_num - 1;
        pthread_mutex_unlock(&mutex);
    }
}

void *writers()
{
    while(1)
    {
        sleep(3);//pthread_yield();
        
        pthread_rwlock_wrlock(&rwlock);
        write_data_base();
        pthread_rwlock_unlock(&rwlock);
    }
}