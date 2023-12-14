#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define count_done 10
#define halt1 3
#define halt2 6

int count=0;

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c1 = PTHREAD_COND_INITIALIZER;
void *functioncount1(){
    while(1){
        pthread_mutex_lock(&m1);
        pthread_cond_wait(&c1,&m1);
        count++;
        printf("Thread 1 count : %d \n",count);
        pthread_mutex_unlock(&m1);
        
    
        if(count>count_done){
            break;
        }
    }
}
void *functioncount2(){
    while(1){
        pthread_mutex_lock(&m1);
        if(count<halt1 || count>=halt2){
            pthread_cond_signal(&c1);
        }
        else{
        count++;
        printf("Thread 2 count : %d \n",count);
       
        }
        pthread_mutex_unlock(&m1);
        if(count>count_done){
            break;
        }
    }
}

int main(){
    pthread_t th1,th2;
    pthread_create(&th1,NULL,&functioncount1,NULL);
    pthread_create(&th2,NULL,&functioncount2,NULL);
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
  
}
