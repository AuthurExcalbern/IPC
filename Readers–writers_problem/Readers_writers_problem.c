#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t mutex;
sem_t db;

int rc = 0;
int data_base;

void read_data_base();
void write_data_base();
void * readers();
void * writers();


int main(int argc, char *argv[])
{
    sem_init(&mutex, 0, 1);
    sem_init(&db, 0, 1);
    
    pthread_t reader1, reader2;
    pthread_t writer;
    
    pthread_create(&reader1, 0, readers, NULL);
    pthread_create(&reader2, 0, readers, NULL);
    pthread_create(&writer, 0, writers, NULL);
    
    pthread_join(reader1, 0);
    pthread_join(reader2, 0);
    pthread_join(writer, 0);
    
    return 0;
}

void read_data_base()
{
    printf("The Reader: Get data %d\n", data_base);
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
        sleep(0);//pthread_yield();
        
        sem_wait(&mutex);
        
        rc = rc + 1;
        if(rc == 1) sem_wait(&db);
        
        sem_post(&mutex);
        
        read_data_base();
        
        sem_wait(&mutex);
        
        rc = rc - 1;
        if(rc == 0) sem_post(&db);
        
        sem_post(&mutex);
        
        //use_data_read();
    }
}

void *writers()
{
    while(1)
    {
        sleep(0);//pthread_yield();
        //think_up_data();
        
        sem_wait(&db);
        
        write_data_base();
        
        sem_post(&db);
    }
}