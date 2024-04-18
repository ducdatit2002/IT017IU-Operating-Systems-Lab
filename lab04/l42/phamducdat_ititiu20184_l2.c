#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

// Function to check if n is a prime number
int is_prime(int n) {
    if (n <= 1) return 0; // 0 and 1 are not prime numbers
    if (n <= 3) return 1; // 2 and 3 are prime numbers
    if (n % 2 == 0 || n % 3 == 0) return 0; // multiples of 2 and 3 are not primes
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

// Thread function to process each number
void* process(void* arg) {
    int n = *(int*)arg;
    if (is_prime(n)) {
        printf("%d is a prime\n", n);
    } else {
        printf("%d is not a prime\n", n);
    }
    free(arg);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s n1 [n2 ...]\n", argv[0]);
        return 1;
    }

    pthread_t threads[argc - 1];

    for (int i = 1; i < argc; i++) {
        int *num = malloc(sizeof(int));
        if (num == NULL) {
            fprintf(stderr, "Failed to allocate memory\n");
            continue;
        }
        *num = atoi(argv[i]);
        if (*num < 0) {
            fprintf(stderr, "Invalid input: %s (Positive integers only)\n", argv[i]);
            free(num);
            continue;
        }
        pthread_create(&threads[i-1], NULL, process, num);
    }

    // Wait for all threads to finish
    for (int i = 1; i < argc; i++) {
        pthread_join(threads[i-1], NULL);
    }

    return 0;
}
