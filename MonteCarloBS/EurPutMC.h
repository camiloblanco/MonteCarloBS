

/****************************************************************************************
*								#INCLUDES AND #CONSTANTS								*
****************************************************************************************/
#pragma once
#include "GenericOptionBS.h"

/****************************************************************************************
*									CLASS DECLARATION									*
****************************************************************************************/

class EurPutMC :	public GenericOptionBS
{
public:

    //constructors
    EurPutMC();
    EurPutMC(double T, double K, int m);

    // Public Member functions
    double payOff(vector <double> path);
};

