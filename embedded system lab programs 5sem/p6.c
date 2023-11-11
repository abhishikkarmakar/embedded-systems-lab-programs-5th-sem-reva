#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<time.h>

#define N 2

int y;
int flag = 0;
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

void *check_prime_num() {
    int i, j;
    int count = 0;

    pthread_mutex_lock(&m1);

    y = (rand() % 50);
    printf("\nRandom y is %d\n", y);

    for (i = 0; i <= y; i++) {
        flag = 0;
        for (j = 2; j <= i / 2; j++) {
            if (i % j == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0 && i >= 2) {
            count++;
            printf("Prime number: %d\n", i);
        }
    }

    printf("\nPrime count = %d\n", count);

    pthread_mutex_unlock(&m1);
}

int main() {
    pthread_t th[N];
    int i, j;

    srand(time(NULL));

    for (i = 0; i < N; i++) {
        pthread_create(&th[i], NULL, &check_prime_num, NULL);
    }

    for (j = 0; j < N; j++) {
        if (pthread_join(th[j], NULL) != 0) {
            perror("Failed to join thread\n");
        }
    }

    return 0;
}

