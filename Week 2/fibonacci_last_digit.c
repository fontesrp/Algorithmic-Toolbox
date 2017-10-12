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

// Returns the last digit of the nth fibonaacci number
unsigned int uiFibLastDigit(unsigned long ulN) {

    // The sequence of final digits in Fibonacci numbers repeats in cycles of 60
    return ullFibonacciNumber(ulN % 60) % 10;
}

int main(int argc, const char * argv[]) {

    unsigned long ulN;

    scanf("%lu", &ulN);

    printf("%u", uiFibLastDigit(ulN));

    return 0;
}
