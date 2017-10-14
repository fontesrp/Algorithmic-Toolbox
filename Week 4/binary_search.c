#include <stdio.h>
#include <stdlib.h>

long lBinarySearch(unsigned long ulSearchVal, unsigned long * prgulSequence, unsigned long ulSqcLen) {

    unsigned long ulBeg = 0;
    unsigned long ulEnd = ulSqcLen - 1;
    unsigned long ulMid;

    while (ulBeg <= ulEnd) {

        ulMid = (ulEnd + ulBeg) / 2;

        if (prgulSequence[ulMid] == ulSearchVal) {
            return ulMid;
        }

        if (prgulSequence[ulMid] < ulSearchVal) {
            ulBeg = ulMid + 1;
        } else {

            if (ulMid == 0) {
                break;
            }

            ulEnd = ulMid - 1;
        }
    }

    return -1;
}

void searchValues(unsigned long * prgulSearch, unsigned long ulSrchLen, unsigned long * prgulSequence, unsigned long ulSqcLen) {

    unsigned long ulIdx;

    for (ulIdx = 0; ulIdx < ulSrchLen; ulIdx++) {

        printf("%ld", lBinarySearch(prgulSearch[ulIdx], prgulSequence, ulSqcLen));

        if (ulIdx != ulSrchLen - 1) {
            printf(" ");
        }
    }
}

void getArrInput(unsigned long * prgulTarget, unsigned long ulLen) {

    unsigned long ulIdx;

    for (ulIdx = 0; ulIdx < ulLen; ulIdx++) {
        scanf("%lu", &prgulTarget[ulIdx]);
    }
}

int main(int argc, char const * argv[]) {

    unsigned long ulSqcLen;
    scanf("%lu", &ulSqcLen);

    unsigned long * prgulSequence = (unsigned long *) malloc(ulSqcLen * sizeof (unsigned long));
    getArrInput(prgulSequence, ulSqcLen);

    unsigned long ulSrchLen;
    scanf("%lu", &ulSrchLen);

    unsigned long * prgulSearch = (unsigned long *) malloc(ulSrchLen * sizeof (unsigned long));
    getArrInput(prgulSearch, ulSrchLen);

    searchValues(prgulSearch, ulSrchLen, prgulSequence, ulSqcLen);

    free(prgulSequence);
    free(prgulSearch);

    return 0;
}
