#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

// Function to check if x is a perfect square
int is_perfect_square(int x) {
    int s = (int)sqrt(x);
    return s * s == x;
}

// Function to check if n is a Fibonacci number
int is_fibonacci(int n) {
    // Checking the condition for Fibonacci number
    return is_perfect_square(5 * n * n + 4) || is_perfect_square(5 * n * n - 4);
}

// Thread function to process each number
void* process(void* arg) {
    int n = *(int*)arg;
    if (is_fibonacci(n)) {
        printf("%d is a Fibonacci member\n", n);
    } else {
        printf("%d is not a Fibonacci member\n", n);
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
        if (*num < 1) {
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
