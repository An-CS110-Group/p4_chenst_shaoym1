<<<<<<< HEAD
#include "generateMap.h"
#include <stdlib.h>

char probability[50] = {4,  7,  11, 11, 15, 15, 19, 19, 23, 23, 23, 26, 26, 26, 30, 30, 30, 34, 34, 34, 38, 38, 38, 38, 42,
                        42, 46, 46, 46, 46, 50, 50, 50, 53, 53, 57, 57, 61, 61, 61, 65, 65, 69, 73, 73, 76, 80, 84, 92, 100};

int getNextObs(int prev, float difficulty) { return prev + (int) (difficulty * (float) (1000 + 21 * probability[rand() % 99])); }

int displayRandGnd();
=======
#ifndef GENERATE_MAP_C
#define GENERATE_MAP_C

#include <stdlib.h>

char probability[50] = {4, 7, 11, 11, 15, 15, 19, 19, 23, 23, 23, 26, 26, 26, 30, 30, 30, 34, 34, 34, 38, 38, 38, 38, 42, 42, 46, 46, 46, 46, 50, 50, 50, 53, 53, 57, 57, 61, 61, 61, 65, 65, 69, 73, 73, 76, 80, 84, 92, 100};

int getNextObs(int prev, float difficulty) {
    return prev + (int) (difficulty * (float) (1000 + 21 * probability[rand() % 99]));
}

#endif//GENERATE_MAP_C
>>>>>>> 688555eea9b5e137ef481ea81a4362f733d5faaa
