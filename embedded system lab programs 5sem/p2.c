#include <stdio.h>
#include <pthread.h>

#define NTHREADS 5

int mails = 0;
pthread_mutex_t mails_mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex initialization

void *task() {
    int k;
    for (k = 0; k < 10000; k++) {
        // Lock the mutex before accessing the shared variable
        pthread_mutex_lock(&mails_mutex);

        mails++;

        // Unlock the mutex after modifying the shared variable
        pthread_mutex_unlock(&mails_mutex);
    }
}

int main() {
    pthread_t thread_id[NTHREADS];
    int i, j;

    for (i = 0; i < NTHREADS; i++) {
        pthread_create(&thread_id[i], NULL, &task, NULL);
    }

    for (j = 0; j < NTHREADS; j++) {
        pthread_join(thread_id[j], NULL);
    }

    printf("Final mails value: %d\n", mails);

    return 0;
}

