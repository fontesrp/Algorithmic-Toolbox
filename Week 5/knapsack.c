#include <stdio.h>
#include <stdlib.h>

void maxLootWeight(unsigned long ** prgpulKnapsacks, unsigned long * prgulBarWeights, unsigned int uiBarQtt, unsigned long ulWeightLmt) {

    unsigned long ulW;

    for (ulW = 0; ulW <= ulWeightLmt; ulW++) {
        prgpulKnapsacks[ulW][0] = 0;
    }

    unsigned int ulIdx;

    for (ulIdx = 0; ulIdx <= uiBarQtt; ulIdx++) {
        prgpulKnapsacks[0][ulIdx] = 0;
    }

    unsigned long ulLootWeight;

    for (ulIdx = 1; ulIdx <= uiBarQtt; ulIdx++) {

        for (ulW = 1; ulW <= ulWeightLmt; ulW++) {

            prgpulKnapsacks[ulW][ulIdx] = prgpulKnapsacks[ulW][ulIdx - 1];

            if (prgulBarWeights[ulIdx] <= ulW) {

                ulLootWeight = prgpulKnapsacks[ulW - prgulBarWeights[ulIdx]][ulIdx - 1] + prgulBarWeights[ulIdx];

                if (prgpulKnapsacks[ulW][ulIdx] < ulLootWeight) {
                    prgpulKnapsacks[ulW][ulIdx] = ulLootWeight;
                }
            }
        }
    }

    printf("%lu", prgpulKnapsacks[ulWeightLmt][uiBarQtt]);
}

void getArrInput(unsigned long * prgulTarget, unsigned int uiLen) {

    unsigned int uiIdx;

    prgulTarget[0] = 0;

    for (uiIdx = 1; uiIdx < uiLen; uiIdx++) {
        scanf("%lu", &prgulTarget[uiIdx]);
    }
}

int main(int argc, char const * argv[]) {

    unsigned long ulWeightLmt;
    scanf("%lu", &ulWeightLmt);

    unsigned int uiBarQtt;
    scanf("%u", &uiBarQtt);

    unsigned long * prgulBarWeights = (unsigned long *) malloc((uiBarQtt + 1) * sizeof (unsigned long));
    unsigned long ** prgpulKnapsacks = (unsigned long **) malloc((ulWeightLmt + 1) * sizeof (unsigned long *));

    unsigned long ulIdx;

    for (ulIdx = 0; ulIdx < ulWeightLmt + 1; ulIdx++) {
        prgpulKnapsacks[ulIdx] = (unsigned long *) malloc((uiBarQtt + 1) * sizeof (unsigned long));
    }

    getArrInput(prgulBarWeights, uiBarQtt);
    maxLootWeight(prgpulKnapsacks, prgulBarWeights, uiBarQtt, ulWeightLmt);

    for (ulIdx = 0; ulIdx < ulWeightLmt + 1; ulIdx++) {
        free(prgpulKnapsacks[ulIdx]);
    }

    free(prgpulKnapsacks);
    free(prgulBarWeights);

    return 0;
}
