#include <stdio.h>
#include <pthread.h>

// Thread function
void *print_message_function(void *ptr);

int main() {
    pthread_t thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    int iret1, iret2;

    // Create threads
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void *)message1);
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void *)message2);

    // Wait for threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print return values
    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);

    return 0;
}

// Thread function definition
void *print_message_function(void *ptr) {
    char *message = (char *)ptr;
    printf("%s \n", message);

    // Thread terminates implicitly when the function returns

    // You can also use pthread_exit(NULL) explicitly if needed
    // pthread_exit(NULL);
}

