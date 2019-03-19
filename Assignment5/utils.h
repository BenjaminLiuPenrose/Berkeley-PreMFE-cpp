//
// Created by Benjamin on 3/4/2019.
//
#include <vector>
#include <math.h>
#include <random>
#include <chrono>

using namespace std;
#ifndef ASSIGNMENT5_UTILS_H
#define ASSIGNMENT5_UTILS_H

class Portfolio{
public:
    double percentEquity;
    double percentBond;
    double percentCash;
    double ret;
    double vol;
    Portfolio() = default;
    Portfolio(
            double percentEquity,
            double percentBond,
            double ret,
            double vol
    )
    {
        this->percentEquity = percentEquity;
        this->percentBond = percentBond;
        this->percentCash = 1. - percentEquity - percentBond;
        this->ret = ret;
        this->vol = vol;
    }
};

class Market{
public:
    double corrEquityBond;
    double equityReturn;
    double equityVol;
    double bondReturn;
    double bondVol;
    double riskFreeRate;
    vector<double> equityReturns;
    vector<double> bondReturns;
    Portfolio tangencyPortfolio;
    const double MIN_FLOAT = 1e-8;
    int numSimulations;
    Market(
            double corrEquityBond,
            double equityReturn,
            double equityVol,
            double bondReturn,
            double bondVol,
            double riskFreeRate,
            int numSimulations
            )
    {
        this->corrEquityBond = corrEquityBond;
        this->equityReturn = equityReturn;
        this->bondReturn = bondReturn;
        this->equityVol = equityVol;
        this->bondVol = bondVol;
        this->riskFreeRate = riskFreeRate;
        runSimulations();
        findTangencyPortfolio();
    }

    Portfolio analyzePortfolio(
            double percentEquity,
            double percentBond
            )
    {
        double ret, vol;
        vector<double> portfolioReturns;
        for (size_t i = 0; i < equityReturns.size(); i++)
        {
            portfolioReturns[i] = -1. + percentEquity * equityReturns[i] + percentBond * bondReturns[i] + (1. - percentEquity - percentBond) * riskFreeRate;
        }
        ret = mean(portfolioReturns);
        vol = std(portfolioReturns);
        Portfolio port = Portfolio(percentEquity, percentBond, ret, vol);
        return port;
    }

    Portfolio findTangencyPortfolio ()
    {
        double percentEquity(.0), percentEquity1(.0);
        percentEquity1 = 1.;
        while( calculateTangent(percentEquity1) <= 0 )
        {
        	percentEquity1 -= 0.02;
        }
        percentEquity = .05;
        while( f(percentEquity) >= 0 )
        {
        	percentEquity += 0.02;
        }
        percentEquity = findRoot(percentEquity, percentEquity1);
        this->tangencyPortfolio = analyzePortfolio(percentEquity, 1.-percentEquity);
        return this->tangencyPortfolio;
    }

    Portfolio findPortfolioForVol(double vol)
    {
        tangencyPortfolio = findTangencyPortfolio();
        double tangencyPortfolioVol = tangencyPortfolio.vol;
        double percentCash, percentEquity, percentBond, percentEquity1;
        if( tangencyPortfolioVol >= vol)
        {
            percentCash = 1. - vol / tangencyPortfolioVol;
            percentEquity = (1. - percentCash) * tangencyPortfolio.percentEquity;
            percentBond = (1. - percentCash) * tangencyPortfolio.percentBond;
        } else {
            percentCash = .0;
            percentEquity = tangencyPortfolio.percentEquity;
            percentEquity1 = 1.;
            percentEquity = findRoot2(percentEquity, percentEquity1);
            percentBond = 1.-percentEquity;
        }
        Portfolio port = analyzePortfolio(percentEquity, percentBond);
        return port;
    }

protected:
    double calculateTangent(double percentEquity)
    {
        double tangent;
        double returnUp, returnDown, volUp, volDown;
        double equityUp, equityDown;
        equityUp = percentEquity + 0.01;
        equityDown = percentEquity - 0.01;
        Portfolio portUp = analyzePortfolio(equityUp, 1. - equityUp);
        Portfolio portDown = analyzePortfolio(equityDown, 1. - equityDown);
        returnUp = portUp.ret; returnDown = portDown.ret;
        volUp = portUp.vol; volDown = portDown.vol;
        tangent = (returnUp - returnDown) / (volUp - volDown);
        return tangent;
    }

    double f(double percentEquity)
    {
        Portfolio port = analyzePortfolio(percentEquity, 1.-percentEquity);
        return calculateTangent(percentEquity) - (port.ret - riskFreeRate) / port.vol;
    }

    double findRoot(double x0, double x1, double precision = 1e-8) // TODO
    {
        double err, xPrev, xRtn, fA(.0), fB(.0), fMid(.0), tmp(.0);
        int cnt(0);
        xPrev = x0;
        xRtn = x1;
        err = f(xRtn);
        while ( fabs(err) >= precision )
        {
            tmp = (xPrev + xRtn) * 0.5;
            fA = f(xPrev); fB = f(xRtn); fMid = f(tmp);
            if ( fabs(fMid) <= precision )
            {
                xRtn = tmp;
                err = f(xRtn);
            }else{
                if ( fA * fMid < 0 )
                {
                    xRtn = tmp;
                    err = f(xRtn);
                }else if ( fMid * fB < 0 ){
                    xPrev = tmp;
                    err = f(xRtn);
                }else{
                    return 0; // this case shouldn't happen and will always return 0
                }
            }
            cnt += 1;
        }
        return xRtn;
    }

    double f2(double percentEquity, double vol)
    {
        Portfolio port = analyzePortfolio(percentEquity, 1. - percentEquity);
        return port.vol - vol;
    }

    double findRoot2(double x0, double x1, double precision = 1e-8)
    {
        double err, xPrev, xRtn, fA(.0), fB(.0), fMid(.0), tmp(.0);
        int cnt(0);
        xPrev = x0;
        xRtn = x1;
        err = f(xRtn);
        while ( fabs(err) >= precision )
        {
            tmp = (xPrev + xRtn) * 0.5;
            fA = f(xPrev); fB = f(xRtn); fMid = f(tmp);
            if ( fabs(fMid) <= precision )
            {
                xRtn = tmp;
                err = f(xRtn);
            }else{
                if ( fA * fMid < 0 )
                {
                    xRtn = tmp;
                    err = f(xRtn);
                }else if ( fMid * fB < 0 ){
                    xPrev = tmp;
                    err = f(xRtn);
                }else{
                    return 0; // this case shouldn't happen and will always return 0
                }
            }
            cnt += 1;
        }
        return xRtn;
    }

private:
    void runSimulations()
    {
    	double corr = this->corrEquityBond;
    	for (int i = 0; i < this->numSimulations; i++)
    	{
    		this->equityReturns[i] = normalRandom(equityReturn, equityVol);
    		this->bondReturns[i] = corr * this->equityReturns[i] + sqrt(1 - corr*corr) * normalRandom(bondReturn, bondVol);
    	}
    }
    double normalRandom(double mu = .0, double sigma = 1.)
    {
//        random_device rd{};
//        mt19937 gen{rd()};
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine gen(seed);
        normal_distribution<double> norm{mu, sigma};
        return norm(gen);
    }
    double mean(const vector<double> returns)
    {
        double mean = .0;
        for (size_t i = 0; i < returns.size(); i++)
        {
            mean += returns[i];
        }
        mean = mean / returns.size();
        return mean;
    }
    double std(const vector<double> returns)
    {
        double meant;
        meant = mean(returns);
        double std = .0;
        for (size_t i = 0; i < returns.size(); i++)
        {
            std += pow(returns[i] - meant, 2);
        }
        std = std / returns.size();
        std = sqrt(std);
        return std;
    }
};




#endif //ASSIGNMENT5_UTILS_H
