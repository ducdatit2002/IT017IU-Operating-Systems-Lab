#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 10

pthread_mutex_t forks[MAX_PHILOSOPHERS];

void *philosopher(void *num);
void take_forks(int);
void put_forks(int);
int N;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Number of philosophers>\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);
    if (N < 4 || N > MAX_PHILOSOPHERS) {
        fprintf(stderr, "Number of philosophers must be between 4 and %d.\n", MAX_PHILOSOPHERS);
        return 1;
    }

    pthread_t phil[N];
    int i;

    // Initialize mutexes
    for (i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (i = 0; i < N; i++) {
        pthread_create(&phil[i], NULL, philosopher, (void *)(long)i);
    }

    // Join threads
    for (i = 0; i < N; i++) {
        pthread_join(phil[i], NULL);
    }

    // Destroy mutexes
    for (i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

void *philosopher(void *num) {
    int id = (int)(long)num;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        take_forks(id);

        printf("Philosopher %d is eating.\n", id);
        sleep(1);

        put_forks(id);
    }
}

void take_forks(int id) {
    int left = id;
    int right = (id + 1) % N;

    if (id % 2 == 0) { // Even ID: left first, then right
        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);
    } else { // Odd ID: right first, then left
        pthread_mutex_lock(&forks[right]);
        pthread_mutex_lock(&forks[left]);
    }
}

void put_forks(int id) {
    int left = id;
    int right = (id + 1) % N;

    pthread_mutex_unlock(&forks[left]);
    pthread_mutex_unlock(&forks[right]);
}
