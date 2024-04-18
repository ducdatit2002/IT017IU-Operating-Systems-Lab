#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isPrime(int num) {
    if (num <= 1) return 0; 
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return 0;
    }
    return 1; 
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <positive integers>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        char *endptr;
        long num = strtol(argv[i], &endptr, 10);

        if (*endptr != '\0' || num <= 0) {
            printf("'%s' is not a positive integer.\n", argv[i]);
            continue;
        }

        if (isPrime(num)) {
            printf("%ld is a prime\n", num);
        } else {
            printf("%ld is not a prime\n", num);
        }
    }

    return 0; 
}
