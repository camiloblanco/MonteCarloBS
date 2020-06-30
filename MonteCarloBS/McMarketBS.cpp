

/****************************************************************************************
*								#INCLUDES AND #CONSTANTS								*
****************************************************************************************/
#include "McMarketBS.h"

/****************************************************************************************
*									MEMBER FUNCTIONS									*
****************************************************************************************/


//Default constructor
McMarketBS::McMarketBS() : m_S0(0), m_sigma(0), m_r(0) {
}

//Parametrized constructor
McMarketBS::McMarketBS(double S0, double sigma, double r) : m_S0(S0), m_sigma(sigma), m_r(r) {
}

//accessors
double McMarketBS::get_S0() { return m_S0; }
double McMarketBS::get_sigma() { return m_sigma; }
double McMarketBS::get_r() { return m_r; }

//Simulate an Stock Price Path 
vector <double>  McMarketBS::simulatePath(double T, int m) {

    if (T > 0 && m > 0) {
        //Initialize variables
        double prevSt = m_S0;
        double delta = T / m;
        vector<double> path(m);

        //Mersenne twister MT19937 random and normal distribution object with mean 0 and dev 1
        //random_device device; //Uses system respurces pool
        //mt19937 generator(device());
        auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
        mt19937 generator(seed);
        normal_distribution<double> distribution(0.0, 1.0);

        //Generate the path
        for (auto& step : path)
        {
            double Zk = distribution(generator);
            step = prevSt * exp((m_r - m_sigma * m_sigma * 0.5) * delta + m_sigma * sqrt(delta) * Zk);
            prevSt = step;
        }
        return path;
    }
    cout << "Error in McMarketBS::simulatePath, Partameters T and m should be psotive and greater than 0." << endl;
    exit(0);
}

//Default destructor
McMarketBS::~McMarketBS() {}