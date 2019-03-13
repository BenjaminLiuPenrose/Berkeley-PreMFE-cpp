#include <iostream>
#include "utils.h"

using namespace std;

int main() {
    // Efficient Frontier
    // create a Market Object
    double corrEquityBond = 0.1;
    double equityReturn = 0.08;
    double equityVol = 0.16;
    double bondReturn = 0.04;
    double bondVol = 0.04;
    double riskFreeRate = 0.02;
    int numSimulations = 100000;
    Market market = Market(corrEquityBond, equityReturn, equityVol, bondReturn, bondVol, riskFreeRate, numSimulations);

    // loop percentEquity, percentBond
    double percentEquity = 0.;
    double percentBond = 1. - percentEquity;

    for(int i = 0; i < 100; i++)
    {
        Portfolio portfolio = market.analyzePortfolio(percentEquity, percentBond);
        cout << portfolio.percentEquity << portfolio.percentBond << portfolio.ret << portfolio.vol;
        percentEquity += 0.01;
        percentBond = 1. - percentEquity;
    }

    // Tangency Portfolio
    // Create a market object
    corrEquityBond = -.1;
    equityReturn = 0.09;
    equityVol = 0.20;
    bondReturn = 0.03;
    bondVol = 0.02;
    riskFreeRate = 0.02;
    numSimulations = 100000;
    Market market2 = Market(corrEquityBond, equityReturn, equityVol, bondReturn, bondVol, riskFreeRate, numSimulations);
    Portfolio portfolio_maxVol = market.analyzePortfolio(1., .0);
    double maxSimulatedVol = portfolio_maxVol.vol;
    double increVol = 0.;
    while( increVol <= maxSimulatedVol)
    {
        Portfolio portfolio = market2.findPortfolioForVol(increVol);
        cout << portfolio.percentEquity << portfolio.percentBond << portfolio.percentCash << portfolio.ret << portfolio.vol;
        increVol += 0.0025;
    }

    return 0;
}