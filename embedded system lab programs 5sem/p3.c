#include<stdio.h>
#include<pthread.h>

#define N 5

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
int mails = 0;

void *task() {
    int k;
    for (k = 0; k < 10; k++) {
        pthread_mutex_lock(&m1);
        mails++;
        pthread_mutex_unlock(&m1);
    }
}

int main() {
    pthread_t th[N];
    int i, j;

    for (i = 0; i < N; i++) {
        pthread_create(&th[i], NULL, &task, NULL);
    }

    for (j = 0; j < N; j++) {
        pthread_join(th[j], NULL);
    }

    printf("\nThe final value of mails: %d\n", mails);

    return 0;
}

