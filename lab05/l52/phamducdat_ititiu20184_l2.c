#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // Include this for sleep function

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t *empty, *full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    while (1) {
        // Produce an item
        int item = rand(); // Generate integer as an example

        sem_wait(empty);
        pthread_mutex_lock(&mutex);

        // Add item to buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(full);

        // Sleep for some time to simulate work
        sleep(1);
    }
}

void *consumer(void *arg) {
    while (1) {
        sem_wait(full);
        pthread_mutex_lock(&mutex);

        // Remove item from buffer
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(empty);

        // Consume the item
        printf("Consumed: %d\n", item);

        // Sleep for some time to simulate work
        sleep(1);
    }
}

int main() {
    pthread_t prod_tid1, prod_tid2, cons_tid;

    // Initialize semaphores and mutex
    empty = sem_open("/empty", O_CREAT, 0644, BUFFER_SIZE);
    full = sem_open("/full", O_CREAT, 0644, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod_tid1, NULL, producer, NULL);
    pthread_create(&prod_tid2, NULL, producer, NULL);
    pthread_create(&cons_tid, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod_tid1, NULL);
    pthread_join(prod_tid2, NULL);
    pthread_join(cons_tid, NULL);

    // Destroy semaphores and mutex
    sem_close(empty);
    sem_close(full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
