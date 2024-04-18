#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isPerfectSquare(int x) {
    int s = sqrt(x);
    return (s * s == x);
}
int isFibonacci(int n) {
    return isPerfectSquare(5*n*n + 4) || isPerfectSquare(5*n*n - 4);
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

        if (isFibonacci(num)) {
            printf("%ld is a Fibonacci member\n", num);
        } else {
            printf("%ld is not a Fibonacci member\n", num);
        }
    }

    return 0;
}
