#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

//哲学家数目及dii个哲学家左右的哲学家编号
#define N 5
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N

//哲学家的三种状态
#define THINKING 0
#define HUNGRY 1
#define EATING 2

//定义哲学家状态 + 临界区的互斥 + 每一个哲学家的信号量
int state[N];
sem_t mutex; //pthread_mutex_t mutex;
sem_t s[N]; //pthread_mutex_t s[N];

//哲学家的编号
int philosophers[N];

void think(int i);//哲学家i开始思考
void eat(int i);//哲学家i开始进餐
void test(int i);//检测哲学家i是否可以进餐
void take_forks(int i);//哲学家i尝试拿起筷子
void put_forks(int i);//哲学家i尝试放下筷子
void *philosopher(void *num);//哲学家

int main(int argc, char **argv)
{
    int i;
    
    //声明哲学家进程
    pthread_t philosopher_id[N];
    
    //初始化哲学家id
    for(i = 0; i < N; i++) philosophers[i] = i;
    
    //初始化信号量
    sem_init(&mutex, 0, 1);
    for(i = 0; i < N; i++) sem_init(&s[i], 0, 0);
    
    //创建哲学家线程
    for(i = 0; i < N; i++)
        pthread_create(&philosopher_id[i], 0, philosopher, &philosophers[i]);
    
    //让主线程等待
    for(i = 0; i < N; i++)
        pthread_join(philosopher_id[i], 0);
    
    return 0;
}


void think(int i)
{
    printf("Philosopher %d: THINKING\n", i);
    sleep(1);
}

void eat(int i)
{
    printf("Philosopher %d: EATING\n", i);
    sleep(1);
}

void test(int i)
{
    //哲学家只有在饥饿状态 + 左右哲学家都不在进餐状态才可以进餐
    if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[i] = EATING;
        eat(i);
        
        //可以进餐则提升其信号量
        sem_post(&s[i]);
        //pthread_mutex_unlock(&s[i]);
    }
}

void take_forks(int i)
{
    sem_wait(&mutex); //pthread_mutex_lock(&mutex);
    
    state[i] = HUNGRY;
    test(i);
    
    sem_post(&mutex); //pthread_mutex_unlock(&mutex);
    
    //若未能进餐则阻塞
    sem_wait(&s[i]); //pthread_mutex_lock(&s[i]);
}

void put_forks(int i)
{
    sem_wait(&mutex); //pthread_mutex_lock(&mutex);
    
    state[i] = THINKING;
    think(i);
    
    //方向筷子后，可能左右哲学家是处于HUNGRY状态，并且是在阻塞中
    //所以检测左右哲学家是否可以进餐，如果可以这提高其信号量
    test(LEFT);
    test(RIGHT);
    
    sem_post(&mutex);//pthread_mutex_unlock(&mutex); 
}

void *philosopher(void *num)
{
    int i = *(int *)num;
    while(1)
    {
        take_forks(i);
        
        //重要！！！
        //需要哲学家在进餐后先放弃自己的时间片
        //让其他哲学家运行
        //以防止一个哲学家线程占用
        sleep(0);
        
        put_forks(i);
    }
}