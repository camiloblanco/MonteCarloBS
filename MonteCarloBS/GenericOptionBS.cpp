

/****************************************************************************************
*								#INCLUDES AND #CONSTANTS								*
****************************************************************************************/
#include "GenericOptionBS.h"

/****************************************************************************************
*									MEMBER FUNCTIONS									*
****************************************************************************************/


//constructors
GenericOptionBS::GenericOptionBS() :m_T(0), m_K(0), m_m(1), m_type("") { }
GenericOptionBS::GenericOptionBS(double T, double K) : m_T(T), m_K(K), m_m(1), m_type("") { }
GenericOptionBS::GenericOptionBS(double T, double K, double m):m_T(T),m_K(K),m_m(m), m_type("") { }

//accessors
void GenericOptionBS::setT(double T) { m_T = T; }
void GenericOptionBS::setK(double K) { m_K = K; }
double GenericOptionBS::getT() { return m_T; }
double GenericOptionBS::getK() { return m_K; }
string GenericOptionBS::getType() { return m_type; }


// Pricing function using Monte Carlo Method
double  GenericOptionBS::priceByMC(McMarketBS market, int N, double eps, double& price, double& error, double& delta, double& gamma){

    vector<double> payOffs(N);
    vector<double> shiftPayOffsPlus; //For (1.0+eps)
    vector<double> shiftPayOffsMinus; //For (1.0-eps)

    // Simulate N paths, and store the resulting Payoffs in the samples vector's elements
    for (auto& sample : payOffs)
    {   
        //Simulate a path and modify the coresponding payOffs vector element
        vector<double> path = market.simulatePath(m_T, m_m);
        sample = payOff(path);

        //For Delta: Rescale the path by 1+eps, calculate the payOff and store the result in shiftPayOffsPlus vector
        transform(path.begin(), path.end(), path.begin(), bind(multiplies<double>(), placeholders::_1, (1.0 + eps)));
        shiftPayOffsPlus.insert(shiftPayOffsPlus.end(), payOff(path));

        //For Gamma: Rescale the path by 1-eps, calculate the payOff and store the result in shiftPayOffsMinus vector
        transform(path.begin(), path.end(), path.begin(), bind(multiplies<double>(), placeholders::_1, (1.0 - eps)/(1.0 + eps)));
        shiftPayOffsMinus.insert(shiftPayOffsMinus.end(), payOff(path));
    }

    // Estimate the price as the discounted mean of all simulated Payoffs
    double mean = accumulate(payOffs.begin(), payOffs.end(), 0.0) / payOffs.size();
    price = exp(-market.get_r() * m_T) * mean;

    // Estimate the standard error
    double sq_sum = inner_product(payOffs.begin(), payOffs.end(), payOffs.begin(), 0.0);
    double stdev = sqrt(sq_sum / payOffs.size() - mean * mean);
    error = (exp(-market.get_r() * m_T) * stdev)/sqrt(N-1);

    // Estimate the Delta
    double shiftMeanPlus = accumulate(shiftPayOffsPlus.begin(), shiftPayOffsPlus.end(), 0.0) / shiftPayOffsPlus.size();
    double shiftPricePlus = exp(-market.get_r() * m_T) * shiftMeanPlus;
    delta = (shiftPricePlus - price) / (eps* market.get_S0());

    // Estimate the Gamma
    double shiftMeanMinus = accumulate(shiftPayOffsMinus.begin(), shiftPayOffsMinus.end(), 0.0) / shiftPayOffsMinus.size();
    double shiftPriceMinus = exp(-market.get_r() * m_T) * shiftMeanMinus;
    gamma = (shiftPricePlus - 2*price + shiftPriceMinus) / ((eps * market.get_S0())* (eps * market.get_S0()));

    return price;
}

 //destructors
GenericOptionBS::~GenericOptionBS(){}