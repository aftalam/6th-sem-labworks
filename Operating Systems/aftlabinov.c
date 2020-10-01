//program to implement Dining Philosophers Problem

#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define PHILOSOPERS_NUM 5
//philosophers are THINKING, then become HUNGRY so they start EATING
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT_PHILOSOPHER (philosopher_number + 4) % PHILOSOPERS_NUM
#define RIGHT_PHILOSOPHER (philosopher_number + 1) % PHILOSOPERS_NUM
pthread_mutex_t mutex;
pthread_cond_t cond_var[PHILOSOPERS_NUM];
pthread_t threadID[PHILOSOPERS_NUM];
//declare the functions
void *philospher(void *num);
void pickup_forks(int);
void return_forks(int);
void philosopher_can_eat(int);
int state[PHILOSOPERS_NUM];
int philosophers[PHILOSOPERS_NUM] = {0, 1, 2, 3, 4};
void *philospher(void *num)
{
    while (1)
    {
        int x = rand() % 3;
        int *i = num;
        sleep(x + 1);
        printf("%d seconds waited...\n", x + 1);
        pickup_forks(*i);
        return_forks(*i);
    }
}
void pickup_forks(int philosopher_number)
{
    //lock first
    pthread_mutex_lock(&mutex);
    //make philosopher HUNGRY
    state[philosopher_number] = HUNGRY;
    printf("Philosopher %d is Hungry now \n", philosopher_number + 1);
    //get what the philosopher is doing
    philosopher_can_eat(philosopher_number);
    //wait if he is EATING
    if (state[philosopher_number] != EATING)
    {
        pthread_cond_wait(&cond_var[philosopher_number], &mutex);
    }
    //else, unlock and sleep for 5 seconds
    pthread_mutex_unlock(&mutex);
}
void return_forks(int philosopher_number)
{
    //lock first
    pthread_mutex_lock(&mutex);
    //make philosopher THINKING
    state[philosopher_number] = THINKING;
    printf("Philosopher %d is PuttingForks %d & %d down.He is Thinking now \n", philosopher_number + 1, LEFT_PHILOSOPHER + 1, philosopher_number + 1);
    philosopher_can_eat(LEFT_PHILOSOPHER);
    philosopher_can_eat(RIGHT_PHILOSOPHER);
    pthread_mutex_unlock(&mutex);
}
void philosopher_can_eat(int philosopher_number)
{
    //check the state of the philosophers
    //if a philosopher is HUNGRY and his LEFT_PHILOSOPHER and RIGHT_PHILOSOPHER are not EATING then he can eat
    if (state[philosopher_number] == HUNGRY && state[LEFT_PHILOSOPHER] != EATING && state[RIGHT_PHILOSOPHER] != EATING)
    {
        state[philosopher_number] = EATING;
        printf("Philosopher %d is PickingUpFork %d & %d.He is Eating now \n", philosopher_number + 1, LEFT_PHILOSOPHER + 1, philosopher_number + 1);
        pthread_cond_signal(&cond_var[philosopher_number]);
    }
}
int main()
{
    int i;
    time_t t;
    srand((unsigned)time(&t));
    pthread_t threadID[PHILOSOPERS_NUM];
    //set them all to THINKING initially
    for (i = 0; i < PHILOSOPERS_NUM; i++)
    {
        state[i] = THINKING;
        pthread_cond_init(&cond_var[i], NULL);
    }
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < PHILOSOPERS_NUM; i++)
    {
        //create a pthread
        pthread_create(&threadID[i], NULL, philospher, &philosophers[i]);
        printf("Philosopher %d is Thinking now \n", i + 1);
    }
    for (i = 0; i < PHILOSOPERS_NUM; i++)
    {
        pthread_join(threadID[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
}
