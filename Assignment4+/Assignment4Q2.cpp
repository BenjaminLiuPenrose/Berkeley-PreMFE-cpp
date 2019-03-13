#include <iostream>
#include <fstream>
#include "option.h"

using namespace std;

int main()
{
   ofstream myfile;
   myfile.open ("Assignment4Q2.txt");
   myfile << "option,type,strike,spot,bs_value,value,binomialValue" << endl;

   {

        double spot = 100;
        double strike = 90;
        double riskFreeRate = 0.15;
        double sigma = 0.275;
        double T = 1;
        int N = 100;

        EuropeanCall option(strike, T, sigma, riskFreeRate);
        double V = option.getValue(spot);
        double bs_V = option.getBlackScholesValue(spot);
        double binomial = option.getBinomialTreeValue(spot, N);

        myfile << "1,EC," << strike << "," << spot << "," << bs_V << "," << V << "," << binomial << endl;
   }
    
  {

        double spot = 100;
        double strike = 95;
        double riskFreeRate = 0.05;
        double sigma = 0.1;
        double T = 0.5;
        int N = 10000;
    
        AmericanCall option(strike, T, sigma, riskFreeRate);
        double V = option.getValue(spot);
        double bs_V = option.getBlackScholesValue(spot);
        double binomial = option.getBinomialTreeValue(spot, N);

		myfile << "2,AC," << strike << "," << spot << "," << bs_V << "," << V << "," << binomial << endl;
   }
   
  {

        double spot = 100;
        double strike = 105;
        double riskFreeRate = 0.01;
        double sigma = 0.25;
        double T = 0.25;
        int N = 250;
    
        AmericanPut option(strike, T, sigma, riskFreeRate);
        double V = option.getValue(spot);
        double bs_V = option.getBlackScholesValue(spot);
        double binomial = option.getBinomialTreeValue(spot, N);

		myfile << "3,AP," << strike << "," << spot << "," << bs_V << "," << V << "," << binomial << endl;
  }
   
  {

        double spot = 100;
        double strike = 95;
        double riskFreeRate = 0.1;
        double sigma = 0.175;
        double T = 0.25;
        int N = 2500;
    
        EuropeanPut option(strike, T, sigma, riskFreeRate);
        double V = option.getValue(spot);
        double bs_V = option.getBlackScholesValue(spot);
        double binomial = option.getBinomialTreeValue(spot, N);

		myfile << "4,EP," << strike << "," << spot << "," << bs_V << "," << V << "," << binomial  << endl;
  }
   
    myfile.close();        
    
    return 0;
}
