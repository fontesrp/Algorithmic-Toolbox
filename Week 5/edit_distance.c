#include <stdio.h>
#include <stdlib.h>

#define MAX_STR_LEN 100

unsigned int uiMin(unsigned int uiA, unsigned int uib, unsigned int uiC) {

    if (uiA < uib && uiA < uiC) {
        return uiA;
    }

    if (uib < uiA && uib < uiC)  {
        return uib;
    }

    return uiC;
}

void editDistance(char * szA, unsigned int uiLenA, char * szB, unsigned int uiLenB, unsigned int ** prgpuiDistance) {

    unsigned int uiI;

    for (uiI = 0; uiI <= uiLenA; uiI++) {
        prgpuiDistance[uiI][0] = uiI;
    }

    unsigned int uiJ;

    for (uiJ = 0; uiJ <= uiLenB; uiJ++) {
        prgpuiDistance[0][uiJ] = uiJ;
    }

    unsigned int uiInsertion;
    unsigned int uiDeletion;
    unsigned int uiMatch;
    unsigned int uiMismatch;

    for (uiJ = 1; uiJ <= uiLenB; uiJ++) {

        for (uiI = 1; uiI <= uiLenA; uiI++) {

            uiInsertion = prgpuiDistance[uiI][uiJ - 1] + 1;
            uiDeletion = prgpuiDistance[uiI - 1][uiJ] + 1;
            uiMatch = prgpuiDistance[uiI - 1][uiJ - 1];
            uiMismatch = prgpuiDistance[uiI - 1][uiJ - 1] + 1;

            prgpuiDistance[uiI][uiJ] = (szA[uiI] == szB[uiJ]) ? uiMin(uiInsertion, uiDeletion, uiMatch) : uiMin(uiInsertion, uiDeletion, uiMismatch);
        }
    }

    printf("%u", prgpuiDistance[uiLenA][uiLenB]);
}

void strShift(char * sz, unsigned int uiLen) {

    unsigned int uiIdx;
    char c0 = 0;
    char c1 = 0;

    for (uiIdx = 0; uiIdx <= uiLen + 1 && uiIdx <= MAX_STR_LEN; uiIdx++) {
        c0 = sz[uiIdx];
        sz[uiIdx] = c1;
        c1 = c0;
    }
}

unsigned int uiStrLen(char * sz) {

    unsigned int uiIdx;

    for (uiIdx = 0; uiIdx <= MAX_STR_LEN && sz[uiIdx] != '\0'; uiIdx++) {
        ;
    }

    return uiIdx;
}

int main(int argc, char const * argv[]) {

    char szA[MAX_STR_LEN + 2];
    scanf("%s", szA);

    char szB[MAX_STR_LEN + 2];
    scanf("%s", szB);

    unsigned int uiLenA = uiStrLen(szA);

    unsigned int uiLenB = uiStrLen(szB);

    strShift(szA, uiLenA);
    strShift(szB, uiLenB);

    unsigned int ** prgpuiDistance = (unsigned int **) malloc((uiLenA + 1) * sizeof (unsigned int *));

    unsigned int uiIdx;

    for (uiIdx = 0; uiIdx <= uiLenA; uiIdx++) {
        prgpuiDistance[uiIdx] = (unsigned int *) malloc((uiLenB + 1) * sizeof (unsigned int));
    }

    editDistance(szA, uiLenA, szB, uiLenB, prgpuiDistance);

    for (uiIdx = 0; uiIdx <= uiLenA; uiIdx++) {
        free(prgpuiDistance[uiIdx]);
    }

    free(prgpuiDistance);

    return 0;
}
