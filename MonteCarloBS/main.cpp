/****************************************************************************************
* Project		:	Machine Learning and modern numerical techniques for high-dimensional
*					option pricing - Financial Computing MSc. Dissertation QMUL 2019/2020
* License		:	MIT License, https://opensource.org/licenses/MIT
* Copyright (c) :	2020 Camilo Blanco
* Mail - Web	:	mail@camiloblanco.com - www.camiloblanco.com
* Lenguaje / Env:	C++ / Microsoft Visual Studio Community 2019
* Git Control	:	https://github.com/camiloblanco/BlackScholesDL
* Description	:	main CPP file for the program MonteCarloBS, entry point.
*
*
****************************************************************************************/

/****************************************************************************************
*								#INCLUDES AND #CONSTANTS								*
****************************************************************************************/
#include <iostream>
#include <iomanip>
#include "McMarketBS.h"
#include "EurCallMC.h"
#include "EurPutMC.h"

using namespace std;


/****************************************************************************************
*										FUNCTIONS				        				*
****************************************************************************************/

// Clear the console in any plataform
void clearConsole() {
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
#elif defined (__APPLE__)
	system("clear");
#endif
}

// Pause execution waiting for a key
void menuPause() {
	cout << endl << "Press any key to continue..." << endl;
	cin.ignore();
	cin.get();
}

void EuropeanMC() {
	double T = 0, K = 100, S0 = 0, sigma = 0, r = 0;
	int m = 0;
	clearConsole();

	cout << "****************************************************************************" << endl;
	cout << " Price an European option using Monte Carlo on the BS framewrok" << endl << endl;
	cout << "Please enter the Time to maturity in years (T): " << endl;
	cin >> T;
	cout << "Please enter the Strike (Exercise) Price (K): " << endl;
	cin >> K;
	cout << "Please enter the Initial Stock Price (S0): " << endl;
	cin >> S0;
	cout << "Please enter the Annualized volatility (sigma): " << endl;
	cin >> sigma;
	cout << "Please enter the Annual risk-free interest rate (r): " << endl;
	cin >> r;

	// Sampling dates from https://en.wikipedia.org/wiki/Trading_day
	m=int(T*253);
	int N = 10000;
	double eps = 0.001;

	if (T > 0 && K >= 0 && m > 0 && S0 >= 0 && sigma >= 0 && r >= 0) {

		// Declare qn optionsPTRvec pointers vector, an EurCallBS, and an EurPutBS Objects
		vector<GenericOptionBS*> optionsPTRvec;
		GenericOptionBS* eurCallPTR = new EurCallMC(T, K, m);
		GenericOptionBS* eurPutPRT = new EurPutMC(T, K, m);
		optionsPTRvec.push_back(eurCallPTR);
		optionsPTRvec.push_back(eurPutPRT);
		McMarketBS market(S0, sigma, r);

		//
		double price, error, delta, gamma;

		//Loop over the vector of options types
		for (auto& option : optionsPTRvec) {
			option->setK(K);
			option->setT(T);
			// Price the options, calculate the greeks and display
			cout << endl << "The Monte Carlo results for this " << option->getType() << " option are:" << endl;
			//priceByMC(McMarketBS market, int N, double eps, double& price, double& error, double& delta, double& gamma)
			cout << "The option price is: " << option->priceByMC(market, N, eps, price, error, delta, gamma) << endl;
			cout << "The option Delta is: " << delta << endl;
			cout << "The option Gamma is: " << gamma << endl;
			cout << "The estimated standar error is : " << error << endl;
			cout << "As a % of the estimated price this is : " << fixed << setprecision(3) << (error / price) * 100.0 << " %." << endl;
		}

		//Delete EurOptionBS Objects
		for (auto pointer : optionsPTRvec)
		{
			delete pointer;
		}
		optionsPTRvec.clear();
	}
	else {
		cout << "All parameters must be positive. " << endl;
	}
	menuPause(); 
}



/****************************************************************************************
*							        MAIN FUNCTION				        				*
****************************************************************************************/

int main()
{
	EuropeanMC();
}
