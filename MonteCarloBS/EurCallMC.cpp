

/****************************************************************************************
*								#INCLUDES AND #CONSTANTS								*
****************************************************************************************/

#include "EurCallMC.h"

/****************************************************************************************
*									MEMBER FUNCTIONS									*
****************************************************************************************/

//constructors
EurCallMC::EurCallMC() : GenericOptionBS () { m_type = "call"; }
EurCallMC::EurCallMC(double T, double K, int m) : GenericOptionBS (T, K ,m) { m_type = "call"; }

// Option specific path-dependat Pay Off function
double EurCallMC::payOff(vector <double> path) {

    // Read the last share price from the path values
    double S = path[path.size()-1];
    
    // Return the payoff by comparing the share price and the strike
    return (S > m_K) ? (S - m_K) : 0;
}