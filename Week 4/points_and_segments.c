#include <stdio.h>
#include <stdlib.h>

// STILL NOT WORKING

enum sweepLinePointsTypes {
    SEGMENT_BEG,
    SEGMENT_END,
    POINT
};

struct sweepLinePoint {
    long location;
    unsigned char type;
    unsigned long pointIdx; // For type = POINT, stores its position on the input array
};

struct segment {
    long start;
    long end;
};

void printArr_l(long * arr, unsigned long arrLen) {
    unsigned long i;
    printf("pointsArr = [\n\t");
    for (i = 0; i < arrLen; i++) {
        printf("%ld", arr[i]);
        if (i != arrLen - 1) {
            printf(",\n\t");
        }
    }
    printf("\n];");
}

void printArr_seg(struct segment * arr, unsigned long arrLen) {
    unsigned long i;
    printf("segArr = [\n\t");
    for (i = 0; i < arrLen; i++) {
        printf("{\n\t\tstart: %ld,\n\t\tend: %ld\n\t}", arr[i].start, arr[i].end);
        if (i != arrLen - 1) {
            printf(", ");
        }
    }
    printf("\n];");
}

void slow_scorePoints(struct segment * segArr, unsigned long segmentsQtt, long * pointsArr, unsigned long pointsQtt, unsigned long * scoreArr) {

    unsigned long i;
    unsigned long j;

    for (i = 0; i < pointsQtt; i++) {
        scoreArr[i] = 0;
        for (j = 0; j < segmentsQtt; j++) {
            if (segArr[j].start <= pointsArr[i] && pointsArr[i] <= segArr[j].end) {
                scoreArr[i] += 1;
            }
        }
    }
}

void printSweepLine(struct sweepLinePoint * sweepLine, unsigned long sweepLineLen) {
    unsigned long i;
    printf("sweepLine = [\n\t");
    for (i = 0; i < sweepLineLen; i++) {
        printf("{\n\t\tlocation: %ld,\n\t\ttype: %u,\n\t\tpointIdx: %lu\n\t}", sweepLine[i].location, sweepLine[i].type, sweepLine[i].pointIdx);
        if (i != sweepLineLen - 1) {
            printf(", ");
        }
    }
    printf("\n];");
}

void printArr(unsigned long * arr, unsigned long arrLen) {
    unsigned long i;
    for (i = 0; i < arrLen; i++) {
        printf("%lu", arr[i]);
        if (i != arrLen - 1) {
            printf(" ");
        }
    }
}

int compareSweepLinePoints(const void * a, const void * b) {

    struct sweepLinePoint * ptA = (struct sweepLinePoint *) a;
    struct sweepLinePoint * ptB = (struct sweepLinePoint *) b;

    return (ptA->location < ptB->location) ? -1 : ((ptA->location == ptB->location) ? 0 : 1);
}

void scorePoints(struct sweepLinePoint * sweepLine, unsigned long sweepLineLen, unsigned long * pointsScoreArr, unsigned long pointsQtt) {

    unsigned long position;
    long counter = 0u;
    unsigned long ptIdx;

    qsort(sweepLine, sweepLineLen, sizeof (struct sweepLinePoint), compareSweepLinePoints);

    for (position = 0u; position < sweepLineLen; position++) {
        switch (sweepLine[position].type) {
        case SEGMENT_BEG:
            counter++;
            break;
        case SEGMENT_END:
            counter--;
            break;
        case POINT:
            ptIdx = sweepLine[position].pointIdx;
            if (ptIdx < pointsQtt) {
                pointsScoreArr[ptIdx] = counter;
            }
            break;
        }
    }
}

void getArrInputs(struct sweepLinePoint * sweepLine, unsigned long sweepLineLen, unsigned long * pointsScoreArr, unsigned long pointsQtt) {

    unsigned long i;
    unsigned long j;

    // Get all segments extremities
    for (i = 0u; i < sweepLineLen - pointsQtt; i++) {
        // scanf("%lu", &sweepLine[i].location);
        sweepLine[i].location = (i % 2) ? rand() : rand() * (-1);
        sweepLine[i].type = (i % 2) ? SEGMENT_END : SEGMENT_BEG;
        sweepLine[i].pointIdx = 0u;
    }

    // Get all points
    for (j = 0; j < pointsQtt; j++, i++) {
        // scanf("%lu", &sweepLine[i].location);
        sweepLine[i].location = rand();
        sweepLine[i].type = POINT;
        sweepLine[i].pointIdx = j;
        pointsScoreArr[j] = 0u;
    }
}

int main(int argc, char const * argv[]) {

    unsigned long segmentsQtt;
    unsigned long pointsQtt;
    unsigned long sweepLineLen;
    struct sweepLinePoint * sweepLine;
    unsigned long * pointsScoreArr;

    // scanf("%lu", &segmentsQtt);
    // scanf("%lu", &pointsQtt);
    segmentsQtt = rand() % 10 + 1;
    pointsQtt = rand() % 10 + 1;

    sweepLineLen = 2 * segmentsQtt + pointsQtt; // Each segment has a start and an end, each point only has one location
    sweepLine = (struct sweepLinePoint *) malloc(sweepLineLen * sizeof (struct sweepLinePoint));
    pointsScoreArr = (unsigned long *) malloc(pointsQtt * sizeof (unsigned long));

    // getArrInputs(sweepLine, sweepLineLen, pointsScoreArr, pointsQtt);

    // scorePoints(sweepLine, sweepLineLen, pointsScoreArr, pointsQtt);
    // printArr(pointsScoreArr, pointsQtt);

    struct segment * segArr;
    long * pointsArr;
    unsigned long * auxPointsScoreArr;
    unsigned long i, j;
    int k = 1;
    segArr = (struct segment *) malloc(segmentsQtt * sizeof (struct segment));
    pointsArr = (long *) malloc(pointsQtt * sizeof (unsigned long));
    auxPointsScoreArr = (unsigned long *) malloc(pointsQtt * sizeof (unsigned long));

    while (k) {

        getArrInputs(sweepLine, sweepLineLen, pointsScoreArr, pointsQtt);

        for (i = 0; i < 2 * segmentsQtt; i++) {
            if (i % 2) {
                segArr[i / 2].end = sweepLine[i].location;
            } else {
                segArr[i / 2].start = sweepLine[i].location;
            }
        }
        for (i = 2 * segmentsQtt, j = 0; i < sweepLineLen; i++, j++) {
            pointsArr[j] = sweepLine[i].location;
        }

        scorePoints(sweepLine, sweepLineLen, pointsScoreArr, pointsQtt);
        slow_scorePoints(segArr, segmentsQtt, pointsArr, pointsQtt, auxPointsScoreArr);

        for (i = 0; i < pointsQtt; i++) {
            if (pointsScoreArr[i] != auxPointsScoreArr[i]) {
                k = 0;
                i = pointsQtt;
            }
        }
    }

    printArr_seg(segArr, segmentsQtt);
    printf("\n");
    printArr_l(pointsArr, pointsQtt);
    printf("\n");
    printf("\n");
    printf("pointsScoreArr = ");
    printArr(pointsScoreArr, pointsQtt);
    printf("\n");
    printf("auxPointsScoreArr = ");
    printArr(auxPointsScoreArr, pointsQtt);
    printf("\n");

    free(segArr);
    free(pointsArr);
    free(auxPointsScoreArr);

    free(sweepLine);
    free(pointsScoreArr);
    return 0;
}
