

/****************************************************************************************
*								#INCLUDES AND #CONSTANTS								*
****************************************************************************************/

#include "EurPutMC.h"

/****************************************************************************************
*									MEMBER FUNCTIONS									*
****************************************************************************************/

//constructors
EurPutMC::EurPutMC() : GenericOptionBS () { m_type = "put"; }
EurPutMC::EurPutMC(double T, double K, int m) : GenericOptionBS (T, K ,m) { m_type = "put"; }

// Option specific path-dependat Pay Off function
double EurPutMC::payOff(vector <double> path) {

    // Read the last share price from the path values
    double S = path[path.size()-1];
    
    // Return the payoff by comparing the share pric and the strike
    return (m_K > S) ? (m_K - S) : 0;
}