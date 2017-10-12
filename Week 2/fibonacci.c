#include <stdio.h>

// Returns the nth Fibonacci number
unsigned long long ullFibonacciNumber(unsigned int uiN) {

    unsigned long long ullFib;
    unsigned long long ullPrev = 1;
    unsigned long long ullBefLast = 0;

    if (uiN == 0) {
        return ullBefLast;
    }

    while (uiN > 1) {

        ullFib = ullBefLast + ullPrev;

        ullBefLast = ullPrev;
        ullPrev = ullFib;

        uiN--;
    }

    return ullFib;
}

int main(int argc, const char * argv[]) {

    unsigned int uiN;

    scanf("%u", &uiN);

    printf("%llu", ullFibonacciNumber(uiN));

    return 0;
}
