#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to check if a number is a Fibonacci number
int is_fibonacci(int n) {
    if (n <= 0) return 0;
    int a = 0, b = 1;
    while (b < n) {
        int temp = b;
        b = a + b;
        a = temp;
    }
    return b == n || n == 0 || n == 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number1> <number2> ... <numberN>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            // Error handling for fork failure
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            int num = atoi(argv[i]);
            if (num < 0) {
                fprintf(stderr, "%s is not a valid positive integer\n", argv[i]);
                exit(EXIT_FAILURE);
            }
            printf("%d is %sa Fibonacci member\n", num, is_fibonacci(num) ? "" : "not ");
            exit(EXIT_SUCCESS);
        }
        // Parent process does nothing here
    }

    // Parent waits for all children to finish
    for (int i = 1; i < argc; i++) {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
