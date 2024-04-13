#ifndef MamdaniFuzzy_H
#define MamdaniFuzzy_H

#include "Set.h"

class MamdaniFuzzy {
public:
    Set set[2][5];
    uint8_t nSets[2];
    float weight[2][5];

    Set outputSet[5];
    uint8_t nOutputSets;
    float crispOutput[5];

    int rulesTable[3][3];

    void computeMembership(float, float);
    float defuzzify();

};

void MamdaniFuzzy::computeMembership(float point1, float point2){
    for (int i = 0; i < nSets[0]; i++){
        weight[0][i] = set[0][i].getMembership(point1);
    }
    for (int i = 0; i < nSets[1]; i++){
        weight[1][i] = set[1][i].getMembership(point2);
    }
}

float MamdaniFuzzy::defuzzify(){
    float weightSum = 0;
    float numerator = 0;

    for (int i = 0; i < nSets[0]; i++){
        for (int j = 0; j < nSets[1]; j++){
            int numOutSet = rulesTable[i][j];
            crispOutput[numOutSet] = outputSet[numOutSet].getCrispOutput();
            float outputWeight = min(weight[0][i], weight[1][j]);
            numerator += crispOutput[numOutSet] * outputWeight;
            weightSum += outputWeight;
        }
    }
    return numerator/weightSum;
}

#endif