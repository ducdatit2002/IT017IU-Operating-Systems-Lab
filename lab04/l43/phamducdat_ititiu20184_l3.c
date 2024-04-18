#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function to check if n is a growing number
int is_growing(int n) {
    int last_digit = 10; // start higher than any single digit
    while (n > 0) {
        int current_digit = n % 10;
        if (current_digit >= last_digit) {
            return 0; // found a non-growing sequence
        }
        last_digit = current_digit;
        n /= 10;
    }
    return 1;
}

// Thread function to process each number
void* process(void* arg) {
    int n = *(int*)arg;
    if (is_growing(n)) {
        printf("%d is a growing number\n", n);
    } else {
        printf("%d is not a growing number\n", n);
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
