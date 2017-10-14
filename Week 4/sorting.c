#include <stdio.h>
#include <stdlib.h>

void printArray(unsigned long * prgulNumbers, unsigned long ulLen) {

    unsigned long ulI;

    for (ulI = 0; ulI < ulLen; ulI++) {

        printf("%lu", prgulNumbers[ulI]);

        if (ulI != ulLen - 1) {
            printf(" ");
        }
    }
}

void swap(unsigned long * pulA, unsigned long * pulB) {

    if (pulA == pulB) {
        // The method bellow fails if both arguments point to the same address
        return;
    }

    *pulA ^= *pulB;
    *pulB = *pulA ^ *pulB;
    *pulA ^= *pulB;
}

void partition3(unsigned long * prgulNumbers, long * rglPostn, long lBeg, long lEnd) {

    long lFirst = prgulNumbers[lBeg];
    long lI;
    long lJ;

    rglPostn[0] = rglPostn[1] = lBeg;

    for (lI = lBeg + 1; lI <= lEnd; lI++) {

        if (prgulNumbers[lI] <= lFirst) {

            rglPostn[1]++;
            swap(&prgulNumbers[lI], &prgulNumbers[rglPostn[1]]);

            if (prgulNumbers[rglPostn[1]] == lFirst) {
                rglPostn[0]++;
                swap(&prgulNumbers[rglPostn[1]], &prgulNumbers[rglPostn[0]]);
            }
        }
    }

    for (lI = lBeg, lJ = 0; lI <= rglPostn[0]; lI++, lJ++) {
        swap(&prgulNumbers[lI], &prgulNumbers[rglPostn[1] - lJ]);
    }

    rglPostn[0] = rglPostn[1] - (lJ - 1);
}

void quickSort(unsigned long * prgulNumbers, long lBeg, long lEnd) {

    long lRandIdx;
    long rglPostn[2];

    if (lBeg >= lEnd) {
        return;
    }

    lRandIdx = lBeg + rand() % (lEnd - lBeg + 1);
    swap(&prgulNumbers[lBeg], &prgulNumbers[lRandIdx]);

    partition3(prgulNumbers, rglPostn, lBeg, lEnd);
    quickSort(prgulNumbers, lBeg, rglPostn[0] - 1);
    quickSort(prgulNumbers, rglPostn[1] + 1, lEnd);
}

void getArrInput(unsigned long * prgulNumbers, unsigned long ulLen) {

    unsigned long ulIdx;

    for (ulIdx = 0; ulIdx < ulLen; ulIdx++) {
        scanf("%lu", &prgulNumbers[ulIdx]);
    }
}

int main(int argc, char const * argv[]) {

    unsigned long ulLen;
    scanf("%lu", &ulLen);

    unsigned long * prgulNumbers = (unsigned long *) malloc(ulLen * sizeof (unsigned long));
    getArrInput(prgulNumbers, ulLen);

    quickSort(prgulNumbers, 0, ulLen - 1);

    printArray(prgulNumbers, ulLen);
    free(prgulNumbers);

    return 0;
}
