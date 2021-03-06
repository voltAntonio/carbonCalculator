#ifndef FERTILISATIONANDSOIL_H
#define FERTILISATIONANDSOIL_H

#include "basicStructures.h"

class FertiliserApplication{

public:
    TfertInput fertInput[8];
    double volatilizationFraction[8];
    double amountFertiliser[8];
    double incrementalParameter[8];
    double drymatter[8];
    double recalcitrantCarbonIndex[8]; // [0-1] ratio of recalcitrant carbon for special amendments biochar,rock dust ...
    double bouwmanParameterNH4ApplicationMethod[8];
    TBouwmanIndex bouwmanParameterNH4;
    TBouwmanIndex bouwmanParameterNO;
    TBouwmanIndex bouwmanParameterN2O;
    TnitrogenInhibitors nitrogenInhibitorNO;
    TnitrogenInhibitors nitrogenInhibitorN2O;
    int inhibitorClass = 1;
    double inhibitorN2O[8];
    double inhibitorNO[8];
    double leachingParameterDueToClimate = 0;

    double emissionDueToFertiliserProduction;
    double emissionDueToFertiliserApplication;
    double emissionDueToSoil;

    double sequestrationDueToFertiliserApplication;


    void computeEmissions();
    void setNitrogenInhibitorsTable();
};



#endif // FERTILISATIONANDSOIL_H
