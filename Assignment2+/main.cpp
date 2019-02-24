#include <iostream>
#include <math.h>
#include <random>
#include <fstream>

using namespace std;


class StrategyAnalyzer{
public:
    int numSimulations;
    double mu, sigma, r, K_call, P_call, K_put, P_put;
    double* buyAndHoldArr;
    double* buyWriteArr;
    double* putWriteArr;
    double* stockPArr;
    double* buyAndHoldPnlArr;
    double* buyWritePnlArr;
    double* putWritePnlArr;

    // problem ii
    StrategyAnalyzer(int numSimulations,
                    double mu,
                    double sigma,
                    double r,
                    double K_call,
                    double P_call,
                    double K_put,
                    double P_put)
    {
        this->numSimulations = numSimulations;
        this->mu = mu;
        this->sigma = sigma;
        this->r = r;
        this->K_call = K_call;
        this->P_call = P_call;
        this->K_put = K_put;
        this->P_put = P_put;

        this->stockPArr = new double[numSimulations];
        this->buyAndHoldArr = new double[numSimulations];
        this->buyWriteArr = new double[numSimulations];
        this->putWriteArr = new double[numSimulations];
        this->buyAndHoldPnlArr = new double[numSimulations];
        this->buyWritePnlArr = new double[numSimulations];
        this->putWritePnlArr = new double[numSimulations];

        this->run_simulation_single();
        this->compute_buyAndHold_pnl();
        this->compute_buyWrite_pnl();
        this->compute_putWrite_pnl();
    }

    // problem iv
    void writeResults(const string& fileName)
    {
        double buyAndHoldPnl(.0), buyWritePnl(.0), putWritePnl(.0);
        ofstream file;
        file.open(fileName);
        file << "BuyAndHold,Buy-Write,Put-Write" << endl;
        for(unsigned int i = 0; i < this->numSimulations; i++)
        {
            buyAndHoldPnl = this->buyAndHoldPnlArr[i];
            buyWritePnl = this->buyWritePnlArr[i];
            putWritePnl = this->putWritePnlArr[i];
            file << buyAndHoldPnl << "," << buyWritePnl << "," << putWritePnl << endl;
        }
        file.close();
    }

    // problem v
    double calcStdDev(double* arr, int arrLen)
    {
        double rtn(0);
        double mean(0);

        mean = this->calcMean(arr, arrLen);

        for(unsigned int i = 0; i < arrLen; i++)
        {
            rtn += (arr[i] - mean) * (arr[i] - mean);
        }
        rtn = rtn / (arrLen - 1);
        rtn = sqrt(rtn);

        return rtn;
    }

    double calcMean(double* arr, int arrLen)
    {
        double mean(0);

        for(unsigned int i = 0; i < arrLen; i++)
        {
            mean += arr[i];
        }
        mean = mean / arrLen;

        return mean;
    }

    // problem vi
    void analyzeReturns()
    {
        double mean(.0);
        double vol(.0);
        double sharpeRatio(.0);
        double r(this->r);

        // buy and hold strategy
        mean = calcMean(this->buyAndHoldPnlArr, this->numSimulations);
        vol = calcStdDev(this->buyAndHoldPnlArr, this->numSimulations);
        sharpeRatio = (mean - r) / vol;

        cout << "For strategy buy and hold: "<< endl;
        cout << "the expected return is " << mean << endl;
        cout << "the volatility is " << vol << endl;
        cout << "the sharpe ratio is " << sharpeRatio << endl;
        cout << endl;

        // buy write strategy
        mean = calcMean(this->buyWritePnlArr, this->numSimulations);
        vol = calcStdDev(this->buyWritePnlArr, this->numSimulations);
        sharpeRatio = (mean - r) / vol;

        cout << "For strategy buy write: "<< endl;
        cout << "the expected return is " << mean << endl;
        cout << "the volatility is " << vol << endl;
        cout << "the sharpe ratio is " << sharpeRatio << endl;
        cout << endl;

        // put write strategy
        mean = calcMean(this->putWritePnlArr, this->numSimulations);
        vol = calcStdDev(this->putWritePnlArr, this->numSimulations);
        sharpeRatio = (mean - r) / vol;

        cout << "For strategy put write: "<< endl;
        cout << "the expected return is " << mean << endl;
        cout << "the volatility is " << vol << endl;
        cout << "the sharpe ratio is " << sharpeRatio << endl;
        cout << endl;
    }

    // problem iii
    virtual ~StrategyAnalyzer()
    {
        delete buyAndHoldArr;
        delete buyWriteArr;
        delete putWriteArr;
        delete stockPArr;
        delete buyWritePnlArr;
        delete buyAndHoldPnlArr;
        delete putWritePnlArr;
    }

private:
    double* run_simulation_single(double spot = 100.0)
    {
        double mult(.0), Z(.0);
        random_device rd{};
        mt19937 gen{rd()};
        normal_distribution<> norm{0, 1};
        double mu, sigma, sigma2, spot1;
        mu = this->mu;
        sigma2 = (this->sigma * this->sigma);
        sigma = sqrt(sigma2);
        for(unsigned int i = 0; i < this->numSimulations; i++)
        {
            Z = norm(gen);
            mult = (mu - 0.5 * sigma2) + sigma * Z;
            mult = exp(mult);
            spot1 = spot * mult;
            this->stockPArr[i] = spot1;
        }

        return this->stockPArr;
    }

    double* compute_buyAndHold_pnl(double spot0 = 100.0)
    {
        double spot(0);
        for(unsigned int i = 0; i < this->numSimulations; i++)
        {
            spot = this->stockPArr[i];
            this->buyAndHoldPnlArr[i] = spot - spot0;
//            this->buyAndHoldArr[i] = spot;
//            if (i == 0)
//            {
//                this->buyAndHoldPnlArr[i] = 0;
//            }else{
//                this->buyAndHoldPnlArr[i] = this->buyAndHoldArr[i] - this->buyAndHoldArr[i-1];
//            }

        }

        return this->buyAndHoldPnlArr;
    }

    double* compute_buyWrite_pnl(double spot0 = 100.0)
    {
        double spot(.0);
        double value(.0);
        for(unsigned int i =0; i < this->numSimulations; i++)
        {
            spot = this->stockPArr[i];
            value = (1 + this->r) * this->P_call + spot - fmax(spot - this->K_call, .0);
            this->buyWritePnlArr[i] = value - spot0;
//            this->buyWriteArr[i] = value;
//            if (i == 0)
//            {
//                this->buyWritePnlArr[i] = 0;
//            }else{
//                this->buyWritePnlArr[i] = this->buyWriteArr[i] - this->buyWriteArr[i-1];
//            }
        }

        return this->buyWritePnlArr;
    }

    double* compute_putWrite_pnl(double spot0 = 100.0)
    {
        double spot(.0);
        double value(.0);
        for(unsigned int i = 0; i < this->numSimulations; i++)
        {
            spot = this->stockPArr[i];
            value = (1 + this->r) * (this->P_put + spot) - fmax(this->K_put - spot, .0);
            this->putWritePnlArr[i] = value - spot0;
//            this->putWriteArr[i] = value;
//            if (i == 0)
//            {
//                this->putWritePnlArr[i] = 0;
//            }else{
//                this->putWritePnlArr[i] = this->putWriteArr[i] - this->putWriteArr[i-1];
//            }
        }

        return this->putWritePnlArr;
    }

};


int main() {
    StrategyAnalyzer sa1(1000000,
                         0.076961,
                         0.14842,
                         0.025,
                         105,
                         5.32,
                         105,
                         7.728
    );

    sa1.analyzeReturns();

    StrategyAnalyzer sa2(10000,
                         0.076961,
                         0.14842,
                         0.025,
                         105,
                         5.32,
                         105,
                         7.728
    );

    sa2.writeResults("strategy.csv");

    return 0;
}