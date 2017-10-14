#include <stdio.h>

#define AVALIABLE_COINS_QTT 3

// Returns the biggest coin value that is less or equal to the change
// if none is found, returns -1
int iBiggestCoin(int * arriCoins, int iTarget) {

    for (int i = AVALIABLE_COINS_QTT - 1; i >= 0; i--) {
        if (arriCoins[i] <= iTarget) {
            return arriCoins[i];
        }
    }

    return -1;
}

// Returns the minimum number of coins needed to change the input value
int iMinCoinQtt(int * arriCoins, int iTarget) {

    int iCoinQtt = 0;
    int iBiggest;

    while (iTarget > 0) {

        iBiggest = iBiggestCoin(arriCoins, iTarget);

        if (iBiggest == -1) {
            return -1;
        }

        iTarget -= iBiggest;
        iCoinQtt++;
    }

    return iCoinQtt;
}

int main(int argc, char const *argv[]) {

    // coin values must be crescently ordered
    int arriCoins[AVALIABLE_COINS_QTT] = {1, 5, 10};

    int iTarget;

    scanf("%d", &iTarget);

    int iMinQtt = iMinCoinQtt(arriCoins, iTarget);

    if (iMinQtt == -1) {
        printf("not possible");
    } else {
        printf("%d", iMinQtt);
    }

    return 0;
}
