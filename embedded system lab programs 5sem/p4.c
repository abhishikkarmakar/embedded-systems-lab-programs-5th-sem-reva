#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

void* roll_dice() {
    pthread_mutex_lock(&m1);

    int value = rand() % 11 + 2;
    printf("\nThe rolling dice value: %d\n", value);

    pthread_mutex_unlock(&m1);
}

int main() {
    pthread_t t1, t2;
    srand(time(NULL));

    pthread_create(&t1, NULL, &roll_dice, NULL);
    pthread_create(&t2, NULL, &roll_dice, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

