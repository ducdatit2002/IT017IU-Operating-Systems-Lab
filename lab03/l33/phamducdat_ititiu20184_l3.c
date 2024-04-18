#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to check if a number is growing
int is_growing(int number) {
    int prev_digit = 10; // Digits are 0-9, so start higher
    while (number > 0) {
        int digit = number % 10;
        if (digit >= prev_digit) {
            return 0; // Not growing
        }
        prev_digit = digit;
        number /= 10;
    }
    return 1; // Is growing
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number1> <number2> ... <numberN>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child process
            int num = atoi(argv[i]);
            if (num < 0) {
                fprintf(stderr, "%s is not a valid positive integer\n", argv[i]);
                exit(EXIT_FAILURE);
            }
            printf("%d is %sa growing number on process %d\n", num, is_growing(num) ? "" : "not ", getpid());
            exit(EXIT_SUCCESS);
        }
        // Parent does nothing in the loop
    }

    // Parent waits for all child processes to finish
    while (wait(NULL) > 0);

    return EXIT_SUCCESS;
}
