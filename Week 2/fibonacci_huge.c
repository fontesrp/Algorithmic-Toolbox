#include <stdio.h>
#include <stdlib.h>

unsigned long long ullGetPisanoPeriod(unsigned long long ullM, unsigned long long * arrullModulosList) {

    unsigned long long i;

    arrullModulosList[0] = 0;
    arrullModulosList[1] = 1;

    for (i = 2; i < 6 * ullM; i++) {

        arrullModulosList[i] = (arrullModulosList[i - 1] + arrullModulosList[i - 2]) % ullM;

        if (arrullModulosList[i - 1] == 0 && arrullModulosList[i] == 1) {
            return i - 1;
        }
    }

    return 0;
}

// Returns the nth Fibonacci number
unsigned long long ullFibonacciNumber(unsigned long long ullN) {

    unsigned long long ullFib;
    unsigned long long ullPrev = 1;
    unsigned long long ullBefLast = 0;

    if (ullN == 0) {
        return ullBefLast;
    }

    while (ullN > 1) {

        ullFib = ullBefLast + ullPrev;

        ullBefLast = ullPrev;
        ullPrev = ullFib;

        ullN--;
    }

    return ullFib;
}

// Returns the rest of the division of the nth Fibonacci number by m
unsigned long long ullGetFibHuge(unsigned long long ullN, unsigned long long ullM) {

    if (ullM == 1) {
        return ullFibonacciNumber(ullN);
    }

    unsigned long long * arrullModulosList = (unsigned long long *) malloc(6 * ullM * sizeof(unsigned long long));

    unsigned long long ullPisanoPeriod = ullGetPisanoPeriod(ullM, arrullModulosList);

    unsigned long long ullFibHuge = arrullModulosList[ullN % ullPisanoPeriod];

    free(arrullModulosList);

    return ullFibHuge;
}

int main(int argc, const char * argv[]) {

    unsigned long long ullN;
    unsigned long long ullM;

    // Index in the Fibonacci sequence
    scanf("%llu", &ullN);

    // Divisor
    scanf("%llu", &ullM);

    printf("%llu", ullGetFibHuge(ullN, ullM));

    return 0;
}
