#include <stdio.h>
#include <stdlib.h>

enum opTypes {
    NOP,
    ADD_1,
    MUL_2,
    MUL_3
};

struct SOperation {
    unsigned int m_uiOpQtt;
    unsigned int m_uiLastOpType;
};

void printInvertedArr(unsigned long * prgulArr, unsigned long ulLen) {

    while (ulLen > 0) {

        printf("%lu", prgulArr[ulLen - 1]);

        if (ulLen - 1 != 0) {
            printf(" ");
        }

        ulLen--;
    }
}

void retraceSteps(unsigned long ulGoal, struct SOperation * prgopMins) {

    unsigned long ulStepQtt = prgopMins[ulGoal].m_uiOpQtt;

    unsigned long * prgulSteps = (unsigned long *) malloc(ulStepQtt * sizeof (unsigned long));

    unsigned long ulIdx;

    for (ulIdx = 0; ulIdx <= ulStepQtt; ulIdx++) {

        prgulSteps[ulIdx] = ulGoal;

        switch (prgopMins[ulGoal].m_uiLastOpType) {
        case ADD_1:
            ulGoal--;
            break;
        case MUL_2:
            ulGoal /= 2;
            break;
        case MUL_3:
            ulGoal /= 3;
            break;
        case NOP:
            break;
        }
    }

    printInvertedArr(prgulSteps, ulStepQtt);

    free(prgulSteps);
}

struct SOperation opFindMin(unsigned long ulIdx, struct SOperation * prgopMins) {

    struct SOperation op;

    // Get to the current number by adding one to the previous
    op.m_uiOpQtt = prgopMins[ulIdx - 1].m_uiOpQtt + 1;
    op.m_uiLastOpType = ADD_1;

    // If it's possible to do it by doubling a previous number, prefer that
    if (ulIdx % 2 == 0 && prgopMins[ulIdx / 2].m_uiOpQtt + 1 < op.m_uiOpQtt) {
        op.m_uiOpQtt = prgopMins[ulIdx / 2].m_uiOpQtt + 1;
        op.m_uiLastOpType = MUL_2;
    }

    // The best way is by multiplying a previous number by three
    if (ulIdx % 3 == 0 && prgopMins[ulIdx / 3].m_uiOpQtt + 1 < op.m_uiOpQtt) {
        op.m_uiOpQtt = prgopMins[ulIdx / 3].m_uiOpQtt + 1;
        op.m_uiLastOpType = MUL_3;
    }

    return op;
}

void minOpToGoal(unsigned long ulGoal, struct SOperation * prgopMins) {

    prgopMins[0].m_uiOpQtt = 0;
    prgopMins[0].m_uiLastOpType = NOP;
    prgopMins[1].m_uiOpQtt = 0;
    prgopMins[1].m_uiLastOpType = NOP;

    unsigned long ulIdx;

    for (ulIdx = 2; ulIdx <= ulGoal; ulIdx++) {
        prgopMins[ulIdx] = opFindMin(ulIdx, prgopMins);
    }

    printf("%u", prgopMins[ulGoal].m_uiOpQtt);
}

int main(int argc, char const * argv[]) {

    unsigned long ulGoal;
    scanf("%lu", &ulGoal);

    // Each number 1 <= n <= "goal" will have its operations stored on index n
    struct SOperation * prgopMins = (struct SOperation *) malloc((ulGoal + 1) * sizeof (struct SOperation));

    minOpToGoal(ulGoal, prgopMins);
    printf("\n");
    retraceSteps(ulGoal, prgopMins);

    free(prgopMins);

    return 0;
}
