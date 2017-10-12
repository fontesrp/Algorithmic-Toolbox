#include <stdio.h>

void swap(unsigned long long * pullA, unsigned long long * pullB) {
    *pullA ^= *pullB;
    *pullB = *pullA ^ *pullB;
    *pullA ^= *pullB;
}

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

// Returns the last digit of the partial sum of Fibonacci numbers m to n
unsigned int uiPartialSumLastDigit(unsigned long long ullM, unsigned long long ullN) {

    // If S(m, n) is the partial sum of Fibonacci numbers F(m) + F(m + 1) + ... + F(n), then
    // S(m, n) = S(n) - S(m - 1) = (F(n + 2) - 1) - (F(m - 1 + 2) - 1) = F(n + 2) - F(m + 1)

    unsigned int uiUpperLastDigit = uiFibLastDigit(ullN + 2u);
    unsigned int uiLowerLastDigit = uiFibLastDigit(ullM + 1u);

    int iPartialSumLastDigit = uiUpperLastDigit - uiLowerLastDigit;

    if (iPartialSumLastDigit < 0) {
        iPartialSumLastDigit += 10;
    }

    return iPartialSumLastDigit;
}

int main(int argc, const char * argv[]) {

    // Start of Fib sequence
    unsigned long long ullM;

    // End of Fib sequence
    unsigned long long ullN;

    scanf("%llu", &ullM);
    scanf("%llu", &ullN);

    if (ullM > ullN) {
        swap(&ullM, &ullN);
    }

    printf("%u", uiPartialSumLastDigit(ullM, ullN));

    return 0;
}
