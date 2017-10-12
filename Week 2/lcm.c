#include <stdio.h>

void swap(unsigned long * pulA, unsigned long * pulB) {
    *pulA ^= *pulB;
    *pulB = *pulA ^ *pulB;
    *pulA ^= *pulB;
}

// Greatest common divisor
unsigned long ulGcd(unsigned long ulA, unsigned long ulB) {

    while (ulB != 0u) {

        if (ulA > ulB) {
            swap(&ulA, &ulB);
        }

        ulB %= ulA;
    }

    return ulA;
}

// Least common multiple
unsigned long ulLcm(unsigned long ulA, unsigned long ulB) {

    if (ulA > ulB) {
        swap(&ulA, &ulB);
    }

    return (ulB / ulGcd(ulA, ulB)) * ulA;
}

int main(int argc, const char * argv[]) {

    unsigned long ulA;
    unsigned long ulB;

    scanf("%lu", &ulA);
    scanf("%lu", &ulB);

    printf("%lu", ulLcm(ulA, ulB));

    return 0;
}
