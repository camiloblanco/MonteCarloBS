

/****************************************************************************************
*								#INCLUDES AND #CONSTANTS								*
****************************************************************************************/
#pragma once
#include "GenericOptionBS.h"

/****************************************************************************************
*									CLASS DECLARATION									*
****************************************************************************************/

class EurCallMC :	public GenericOptionBS
{
public:

    //constructors
    EurCallMC();
    EurCallMC(double T, double K, int m);

    // Public Member functions
    double payOff(vector <double> path);
};

