#include <stdio.h>

void swap(unsigned long * pulA, unsigned long * pulB) {
    *pulA ^= *pulB;
    *pulB = *pulA ^ *pulB;
    *pulA ^= *pulB;
}

unsigned long ulGcd(unsigned long ulA, unsigned long ulB) {

    while (ulB != 0u) {

        if (ulA > ulB) {
            swap(&ulA, &ulB);
        }

        ulB %= ulA;
    }

    return ulA;
}

int main(int argc, const char * argv[]) {

    unsigned long ulA;
    unsigned long ulB;

    scanf("%lu", &ulA);
    scanf("%lu", &ulB);

    printf("%lu", ulGcd(ulA, ulB));

    return 0;
}
