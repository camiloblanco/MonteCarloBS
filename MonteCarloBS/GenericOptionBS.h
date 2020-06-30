

/****************************************************************************************
*								#INCLUDES AND #CONSTANTS								*
****************************************************************************************/
#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <numeric>
#include <functional> 
#include "McMarketBS.h"

using namespace std;

/****************************************************************************************
*									CLASS DECLARATION									*
****************************************************************************************/
class GenericOptionBS
{
public:   
    //constructors
    GenericOptionBS();
    GenericOptionBS(double T, double K);
    GenericOptionBS(double T, double K, double m);

    //accessors
    void setT(double T);
    void setK(double K);
    double getT();
    double getK();
    string getType();

    // Public Member functions
    double  priceByMC(McMarketBS market, int N, double eps, double & price, double& error, double& delta, double& gamma);

    //destructors
    ~GenericOptionBS();

protected:
    // protected Member functions
    virtual double payOff(vector <double> path)=0;

    // protected Member variables
    double m_T;         // Time to maturity in years (T)
    double m_K;         // Strike (Exercise) Price (K)
    string m_type; // String for option type
    int m_m;         // Sampling dates (m)
};

