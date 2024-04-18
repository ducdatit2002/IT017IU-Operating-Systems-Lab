#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int is_prime(int number) {
    if (number <= 1) return 0;
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number1> <number2> ... <numberN>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            // Error handling
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            int num = atoi(argv[i]);
            if (num <= 0) {
                fprintf(stderr, "%s is not a valid positive integer\n", argv[i]);
                exit(EXIT_FAILURE);
            }
            printf("%d is %sa prime\n", num, is_prime(num) ? "" : "not ");
            exit(EXIT_SUCCESS);
        }
        // Parent process does nothing here, it just forks off another child
    }

    // Parent waits for all children
    for (int i = 1; i < argc; i++) {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
