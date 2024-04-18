#include <stdio.h>
#include <stdlib.h>

// Function to check if a number is a growing number
int isGrowingNumber(int num) {
    int lastDigit = 10; // Last digit is set to 10, which is greater than any possible digit
    while (num > 0) {
        int currentDigit = num % 10; // Extract the last digit
        if (currentDigit >= lastDigit) return 0; // Not a growing number
        lastDigit = currentDigit;
        num /= 10; // Remove the last digit
    }
    return 1; // Is a growing number
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <positive integers>\n", argv[0]);
        return 1; // Error: No numbers provided
    }

    for (int i = 1; i < argc; i++) {
        char *endptr;
        long num = strtol(argv[i], &endptr, 10);

        // Check for non-integer inputs and non-positive numbers
        if (*endptr != '\0' || num <= 0) {
            printf("'%s' is not a positive integer.\n", argv[i]);
            continue;
        }

        // Check and print if the number is a growing number
        if (isGrowingNumber(num)) {
            printf("%ld is a growing number\n", num);
        } else {
            // A single-digit number is not considered a growing number based on the example provided
            printf("%ld is not a growing number\n", num);
        }
    }

    return 0; // Successful execution
}
