#include <iostream>
#include <fstream>
#include "bond.h"

using namespace std;

int main()
{
	ofstream myfile;
	myfile.open("Assignment4Q1.txt");
	myfile << "bond,principal,coupon,timeToMaturity,price,ytm,modifiedDuration" << endl;

	{

		double principal = 1000;
		double coupon = 60;
		double timeToMaturity = 10;

		Bond b(principal, coupon, timeToMaturity);
		double P = b.getPrice(0.05);
		double YTM = b.getYTM(1007.0);
		double md = b.estimateModifiedDuration(0.06);

		myfile << "1," << principal << "," << coupon << "," << timeToMaturity << "," << P << "," << YTM << "," << md << endl;
	}

	{

		double principal = 100;
		double coupon = 7;
		double timeToMaturity = 5.15;

		Bond b(principal, coupon, timeToMaturity);
		double P = b.getPrice(0.05);
		double YTM = b.getYTM(98.5);
		double md = b.estimateModifiedDuration(0.05);

		myfile << "2," << principal << "," << coupon << "," << timeToMaturity << "," << P << "," << YTM << "," << md << endl;
	}


	{

		double principal = 100;
		double coupon = 10;
		double timeToMaturity = 7.65;

		Bond b(principal, coupon, timeToMaturity);
		double P = b.getPrice(0.08);
		double YTM = b.getYTM(104.0);
		double md = b.estimateModifiedDuration(0.1);

		myfile << "3," << principal << "," << coupon << "," << timeToMaturity << "," << P << "," << YTM << "," << md << endl;
	}

	myfile << endl << endl;


	{
		double principal = 100;
		double coupon = 6.2;
		double timeToMaturity = 15.23;
		double hazardRate = 0.05;
		double riskFreeRate = 0.01;

		Bond b(principal, coupon, timeToMaturity);

		int numSimulations = 100;
		double simulatedPrice = b.estimateSimulatedPrice(hazardRate, riskFreeRate, numSimulations);
		myfile << "simulated price after " << numSimulations << " simulations: " << simulatedPrice << endl;


		numSimulations = 1000;
		simulatedPrice = b.estimateSimulatedPrice(hazardRate, riskFreeRate, numSimulations);
		myfile << "simulated price after " << numSimulations << " simulations: " << simulatedPrice << endl;


		numSimulations = 10000;
		simulatedPrice = b.estimateSimulatedPrice(hazardRate, riskFreeRate, numSimulations);
		myfile << "simulated price after " << numSimulations << " simulations: " << simulatedPrice << endl;

		numSimulations = 100000;
		simulatedPrice = b.estimateSimulatedPrice(hazardRate, riskFreeRate, numSimulations);
		myfile << "simulated price after " << numSimulations << " simulations: " << simulatedPrice << endl;

		numSimulations = 1000000;
		simulatedPrice = b.estimateSimulatedPrice(hazardRate, riskFreeRate, numSimulations);
		myfile << "simulated price after " << numSimulations << " simulations: " << simulatedPrice << endl;
	}

	myfile.close();

	return 0;
}
