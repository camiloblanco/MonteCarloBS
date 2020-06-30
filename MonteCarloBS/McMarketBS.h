

/****************************************************************************************
*								#INCLUDES AND #CONSTANTS								*
****************************************************************************************/
#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

/****************************************************************************************
*									CLASS DECLARATION									*
****************************************************************************************/
class McMarketBS
{
public:

    //constructors
    McMarketBS();
    McMarketBS(double S0 , double sigma, double r);

    //accessors
    double get_S0();
    double get_sigma();
    double get_r();


    // Public Member functions
    vector <double>  simulatePath(double T, int m);

    //destructors
    ~McMarketBS();

private:

    // private Member variables
    double m_S0;        // Initial Stock Price (S0)
    double m_sigma;     // Annualized volatility (sigma)
    double m_r;         // Annual risk-free interest rate (r)
};