#include <stdio.h>
#include <stdlib.h>

unsigned long ulInversions = 0;

void merge(unsigned long * prgulNumbers, unsigned long * prgulAux, long lBeg, long lMid, long lEnd) {

    long lIdx = lBeg;
    long l1 = lBeg;
    long l2 = lMid + 1;

    while (l1 <= lMid && l2 <= lEnd) {

        if (prgulNumbers[l1] <= prgulNumbers[l2]) {
            prgulAux[lIdx] = prgulNumbers[l1++];
        } else {

            ulInversions += l2 - lIdx;

            prgulAux[lIdx] = prgulNumbers[l2++];
        }

        lIdx++;
    }

    while (l1 <= lMid) {
        prgulAux[lIdx++] = prgulNumbers[l1++];
    }

    while (l2 <= lEnd) {
        prgulAux[lIdx++] = prgulNumbers[l2++];
    }

    for (lIdx = lBeg; lIdx <= lEnd; lIdx++) {
        prgulNumbers[lIdx] = prgulAux[lIdx];
    }
}

void mergeSort(unsigned long * prgulNumbers, unsigned long * prgulAux, long lBeg, long lEnd) {

    if (lBeg >= lEnd) {
        return;
    }

    long lMid = (lBeg + lEnd) / 2;

    mergeSort(prgulNumbers, prgulAux, lBeg, lMid);
    mergeSort(prgulNumbers, prgulAux, lMid + 1, lEnd);

    merge(prgulNumbers, prgulAux, lBeg, lMid, lEnd);
}

void getArrInput(unsigned long * prgulTarget, unsigned long ulLen) {

    unsigned long ulIdx;

    for (ulIdx = 0; ulIdx < ulLen; ulIdx++) {
        scanf("%lu", &prgulTarget[ulIdx]);
    }
}

int main(int argc, char const * argv[]) {

    unsigned long ulLen;
    scanf("%lu", &ulLen);

    unsigned long * prgulNumbers = (unsigned long *) malloc(ulLen * sizeof (unsigned long));
    unsigned long * prgulAux = (unsigned long *) malloc(ulLen * sizeof (unsigned long));
    getArrInput(prgulNumbers, ulLen);

    mergeSort(prgulNumbers, prgulAux, 0, ulLen - 1);
    printf("%lu", ulInversions);

    free(prgulNumbers);
    free(prgulAux);
    return 0;
}
