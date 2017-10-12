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

// Returns the last digit of the sum of the first n Fibonacci numbers
unsigned int uiSumLastDigit(unsigned long long ullN) {

    // Let S(n) be the sum of the first n Fibonacci numbers and F(n) be the nth Fibonacci number
    // S(n) = F(n + 2) - 1

    int iSumLastDigit = uiFibLastDigit(ullN + 2) - 1;

    if (iSumLastDigit < 0) {
        iSumLastDigit += 10;
    }

    return iSumLastDigit;
}

int main(int argc, const char * argv[]) {

    unsigned long long ullN;

    scanf("%llu", &ullN);

    printf("%u", uiSumLastDigit(ullN));

    return 0;
}
