#include <stdio.h>
#include <pthread.h>

#define Buffer_Limit 10

int Index_Value = 0, i, j;
int Buffer[Buffer_Limit];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t Buffer_Full = PTHREAD_COND_INITIALIZER;
pthread_cond_t Buffer_Empty = PTHREAD_COND_INITIALIZER;

void *Consumer() {
    for (j = 0; j < Buffer_Limit; j++) {
        pthread_mutex_lock(&mutex);
        if (Index_Value == -1) {
            pthread_cond_wait(&Buffer_Empty, &mutex);
        }
        printf("\nConsumer:%d\t", Index_Value--);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&Buffer_Full);
    }
}

void *Producer() {
    for (i = 0; i < Buffer_Limit; i++) {
        pthread_mutex_lock(&mutex);
        if (Index_Value == Buffer_Limit) {
            pthread_cond_wait(&Buffer_Full, &mutex);
        }
        Buffer[Index_Value++] = rand() % 50;
        printf("\nProducer:%d\t", Index_Value);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&Buffer_Empty);
    }
}

int main() {
    pthread_t producer_thread_id, consumer_thread_id;
    pthread_create(&producer_thread_id, NULL, &Producer, NULL);
    pthread_create(&consumer_thread_id, NULL, &Consumer, NULL);
    pthread_join(producer_thread_id, NULL);
    pthread_join(consumer_thread_id, NULL);
    return 0;
}
