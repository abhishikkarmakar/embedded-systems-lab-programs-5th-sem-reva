#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define N 10
int Buffer[N];
int index1=0,i,j;

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void *consumer(){
    for(i=0;i<N;i++){
        
        pthread_mutex_lock(&m1);
        if(index1==-1){
            pthread_cond_wait(&empty,&m1);
        }
        printf("Consumer : %d\n",index1--);
        pthread_mutex_unlock(&m1);
        pthread_cond_signal(&full);
    }
}
void *producer(){
    for(j=0;j<N;j++){
        pthread_mutex_lock(&m1);
        if(index1==N){
            pthread_cond_wait(&full,&m1);
        }
        Buffer[index1++]=rand()%50;
        printf("producer : %d\n",index1);
        pthread_mutex_unlock(&m1);
        pthread_cond_signal(&empty);
    }
}

int main(){
    pthread_t th1,th2;
    pthread_create(&th1,NULL,&producer,NULL);
    pthread_create(&th2,NULL,&consumer,NULL);
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
  
}
