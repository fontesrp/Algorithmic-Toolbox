#include <stdio.h>
#include <stdlib.h>

#define iCompareBigNumbers(_a, _b) (_a < _b) ? -1 : ((_a == _b) ? 0 : 1)

struct SLootItem {
    unsigned long m_ulValue;
    unsigned long m_ulWeight;
};

struct SFractalLootItem {
    double m_dValue;
    unsigned long m_ulWeight;
};

struct SFractalLootItem fliChooseBestLootItem(struct SLootItem * prgliAvaliableItems, unsigned int uiItemQtt, unsigned long uiRemainingWeight) {

    unsigned int ui;
    struct SFractalLootItem fliBestItem;
    double dDivFactor;

    for (ui = uiItemQtt; ui > 0 && prgliAvaliableItems[ui - 1].m_ulWeight == 0; ui--) {
        // Find the product with the best price/weight ratio still available
        ;
    }

    if (ui == 0) {
        // No product available
        fliBestItem.m_dValue = 0.0;
        fliBestItem.m_ulWeight = 0;
    } else if (prgliAvaliableItems[ui - 1].m_ulWeight <= uiRemainingWeight) {

        fliBestItem.m_dValue = (double) prgliAvaliableItems[ui - 1].m_ulValue;
        fliBestItem.m_ulWeight = prgliAvaliableItems[ui - 1].m_ulWeight;

        // This product was completely taken and is no longer available
        prgliAvaliableItems[ui - 1].m_ulWeight = 0;
    } else {

        dDivFactor = (double) prgliAvaliableItems[ui - 1].m_ulWeight / uiRemainingWeight;

        fliBestItem.m_dValue = (double) prgliAvaliableItems[ui - 1].m_ulValue / dDivFactor;
        fliBestItem.m_ulWeight = uiRemainingWeight;
        // As this will fill the remaining of the sack, there is no need to decrease the product's available weight: the program will terminate after this step
    }

    return fliBestItem;
}

void swap(unsigned long * pulA, unsigned long * pulB) {
    *pulA ^= *pulB;
    *pulB = *pulA ^ *pulB;
    *pulA ^= *pulB;
}

// Greatest common divisor
unsigned long ulGcd(unsigned long ulA, unsigned long ulB) {

    while (ulB != 0) {

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

int iCompareFractions(unsigned long ulNumA, unsigned long ulDenA, unsigned long ulNumB, unsigned long ulDenB) {

    unsigned long ulCommonDen;

    if (ulDenA != ulDenB) {

        ulCommonDen = ulLcm(ulDenA, ulDenB);

        ulNumA *= ulCommonDen / ulDenA;
        ulNumB *= ulCommonDen / ulDenB;
    }

    return iCompareBigNumbers(ulNumA, ulNumB);
}

int iCompareLootItems(const void * a, const void * b) {

    struct SLootItem * pliA = (struct SLootItem *) a;
    struct SLootItem * pliB = (struct SLootItem *) b;

    // Compares the items' value/weight ratio
    return iCompareFractions(pliA->m_ulValue, pliA->m_ulWeight, pliB->m_ulValue, pliB->m_ulWeight);
}

double dBestLootValue(struct SLootItem * prgliAvaliableItems, unsigned int uiItemQtt, unsigned long ulWeightLimit) {

    unsigned long ulLootWeight = 0;
    double dLootValue = 0.0;
    struct SFractalLootItem fliBestItem;

    qsort(prgliAvaliableItems, uiItemQtt, sizeof(struct SLootItem), iCompareLootItems);

    do {

        fliBestItem = fliChooseBestLootItem(prgliAvaliableItems, uiItemQtt, ulWeightLimit - ulLootWeight);

        dLootValue += fliBestItem.m_dValue;
        ulLootWeight += fliBestItem.m_ulWeight;
    } while (ulLootWeight < ulWeightLimit && fliBestItem.m_ulWeight != 0);

    return dLootValue;
}

void getLootItemsInput(struct SLootItem * prgliAvaliableItems, unsigned int uiItemQtt) {

    unsigned int ui;

    for (ui = 0; ui < uiItemQtt; ui++) {
        scanf("%lu", &(prgliAvaliableItems[ui].m_ulValue));
        scanf("%lu", &(prgliAvaliableItems[ui].m_ulWeight));
    }
}

int main(int argc, char const *argv[]) {

    unsigned int uiItemQtt;
    unsigned long ulWeightLimit;
    struct SLootItem * prgliAvaliableItems;

    scanf("%u", &uiItemQtt);
    scanf("%lu", &ulWeightLimit);

    prgliAvaliableItems = (struct SLootItem *) malloc(uiItemQtt * sizeof (struct SLootItem));

    getLootItemsInput(prgliAvaliableItems, uiItemQtt);
    printf("%.4f", dBestLootValue(prgliAvaliableItems, uiItemQtt, ulWeightLimit));

    free(prgliAvaliableItems);

    return 0;
}
