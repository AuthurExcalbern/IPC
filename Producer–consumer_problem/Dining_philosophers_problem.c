#include<stdio.h>
#include<pthread.h>//线程模拟实现
#define MAX 100//需要生产的数量

pthread_mutex_t the_mutex;//互斥量
pthread_cond_t condc, condp;//条件变量

int buffer = 0;//生产者和消费者的缓冲区

//生产者函数
void *producer(void *ptr)
{
    int i;

    for(i = 1; i <= MAX; i++)
    {
        pthread_mutex_lock(&the_mutex);//对互斥量加锁

        //当缓冲区内容不为0
        //就等待一个条件变量，并解锁它的互斥量
        while(buffer != 0) pthread_cond_wait(&condp, &the_mutex);

        printf("Producer time: Add data!\n");
        buffer = i;//将数据放入缓冲区

        pthread_cond_signal(&condc);//唤醒消费者
        pthread_mutex_unlock(&the_mutex); //对互斥量解锁
    }

    pthread_exit(0);
}

//消费者函数
void *consumer(void *ptr)
{
    int i;

    //内容如上
    for(i = 1; i <= MAX; i++)
    {
        pthread_mutex_lock(&the_mutex);

        while(buffer == 0) pthread_cond_wait(&condc, &the_mutex);

        printf("Consumer time: Put data %d\n", buffer);
        buffer = 0;//取出数据

        pthread_cond_signal(&condp);
        pthread_mutex_unlock(&the_mutex); 
    }

    pthread_exit(0);
}

int main(int argc, char **argv)
{
    //声明两个线程
    pthread_t pro, con;
    
    //初始化互斥量和条件变量
    pthread_mutex_init(&the_mutex, 0);
    pthread_cond_init(&condc, 0);
    pthread_cond_init(&condp, 0);
    
    //创建两线程
    pthread_create(&con, 0, consumer, 0);
    pthread_create(&pro, 0, producer, 0);

    //使主线程等待两线程结束
    pthread_join(pro, 0);
    pthread_join(con, 0);

    //删除条件变量和信号量
    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&the_mutex);

    return 0;
}
