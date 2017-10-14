#include <stdio.h>
#include <stdlib.h>

unsigned long ulBoyerMooreMajority(unsigned long * prgulVotes, unsigned long ulLen) {

    unsigned long ulCandidate;
    unsigned long ulLead = 0;
    unsigned long ulIdx;

    for (ulIdx = 0; ulIdx < ulLen; ulIdx++) {
        if (ulLead == 0) {
            ulCandidate = ulIdx;
            ulLead = 1;
        } else if (prgulVotes[ulCandidate] == prgulVotes[ulIdx]) {
            ulLead++;
        } else {
            ulLead--;
        }
    }

    return ulCandidate;
}

unsigned int uiMajorityElement(unsigned long * prgulVotes, unsigned long ulLen) {

    unsigned long ulCandidate = ulBoyerMooreMajority(prgulVotes, ulLen);

    unsigned long ulIdx;
    unsigned long ulOccur = 0;

    for (ulIdx = 0; ulIdx < ulLen; ulIdx++) {
        if (prgulVotes[ulIdx] == prgulVotes[ulCandidate]) {
            ulOccur++;
        }
    }

    return (ulOccur > ulLen / 2) ? 1 : 0;
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

    unsigned long * prgulVotes = (unsigned long *) malloc(ulLen * sizeof (unsigned long));
    getArrInput(prgulVotes, ulLen);

    printf("%u", uiMajorityElement(prgulVotes, ulLen));

    free(prgulVotes);

    return 0;
}
