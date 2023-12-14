#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
int i,j;
int flag=0;

void *check_prime(){
    int count=0;
    int y;
    pthread_mutex_lock(&m1);
    y=rand()%50;
    printf("Range : %d \n",y);
    for(i=2;i<y;i++){
        flag=0;
        for(j=2; j*j <= i ; j++){
            if(i%j==0){
                flag=1;
                break;
            }
        }if(i>=2 && flag==0){
            count++;
            printf("Prime number is \t: %d\n",i);
        }
    }printf("total prime number in the range is %d \n",count);
    pthread_mutex_unlock(&m1);
}

int main(){
    pthread_t th1,th2;
    srand(time(NULL));
    pthread_create(&th1,NULL,&check_prime,NULL);
    pthread_create(&th2,NULL,&check_prime,NULL);
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    
}
