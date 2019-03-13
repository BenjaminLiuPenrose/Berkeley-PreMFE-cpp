//
// Created by Benjamin on 3/12/2019.
//
#include <vector>
#include <math.h>
using namespace std;

#ifndef ASSIGNMENT5_AGENTS_H
#define ASSIGNMENT5_AGENTS_H
class Dealer;

class Agent{
public:
    double tradeProb;
    double tradeScale;

    // starting values;
    double startingCash;
    double startingShares;

    // current values
    double cash;
    double shares;

    Agent(
            double tradeProb,
            double tradeScale,
            double cash,
            double shares
            )
    {
        this->tradeProb = tradeProb;
        this->tradeScale = tradeScale;
        this->cash = cash;
        this->shares = shares;
        // starting value
        this->startingCash = cash;
        this->startingShares = shares;
    }

    virtual ~Agent() {}
    virtual void tick(double net, Dealer* dealer) = 0;
    double getNAV(double price)
    {
        return this.cash + price * this->shares;
    }
    virtual void reset()
    {
        this->cash = this->startingCash;
        this->shares = this->startingShares;
    }
    void adjustHoldings(double cash, double shares)
    {
        this->cash += cash;
        this->shares += shares;
    }
};


class ValueAgent : public Agent {
public:
    ValueAgent(double tradeProb, double tradeScale, double cash, double shares) : Agent(tradeProb, tradeScale, cash, shares) {}
    void tick(double net, Dealer* dealer);

    virtual ~ValueAgent() {}
};

class MomentAgent: public Agent {
public:
    double prevNet;
    MomentAgent(double tradeProb, double tradeScale, double cash, double shares) : Agent(tradeProb, tradeScale, cash, shares), prevNet(0) {}
    void tick(double net, Dealer* dealer);

    void reset()
    {
        this->cash = this->startingCash;
        this->shares = this->startingShares;
        this->prevNet = 0;
    }

    virtual ~MomentAgent() {}
};

class NoiseAgent : public Agent {
public:
    NoiseAgent(double tradeScale) : Agent(1., tradeScale, .0, .0) {}
    void tick(double net, Dealer* dealer);

    virtual ~NoiseAgent() {}
};

class Dealer {
public:
    vector<Agent*> agents;
    double net;
    double priceScale;

private:
    double periodNet;

public:
    Dealer(double priceScale)
    {
        this->priceScale = priceScale;
        this->net = .0;
    }
    virtual ~Dealer()
    {
        for (size_t i = 0; i < agents.size(); i++)
        {
            delete agents[i];
        }
    }
    void addAgent(
            const string& agentType,
            double tradeProb,
            double tradeScale,
            double cash,
            double shares
    )
    {
        Agent* agent;
        if (agentType == "value") {
            agent = new ValueAgent(tradeProb, tradeScale, cash, shares);
        } else if (agentType == "momentum") {
            agent = new MomentAgent(tradeProb, tradeScale, cash, shares);
        } else {
            agent = new NoiseAgent(tradeScale);
        }
        this->agents.push_back(agent);
    }

    void runSimulation(
            int numSimulations,
            int numPeriods,
            vector< vector<double> >& simResults

    )
    {
        double currentPirce = .0;
        // clear the simResults vector
        for (size_t i = 0; i<simResults.size(); i++)
        {
            simResults.clear();
        }

        for (int i = 1; i<=numSimulations; i++)
        {
            // reset all agents
            for( size_t ag = 0; ag < agents.size(); ag++)
            {
                agents[ag]->reset();
            }
            this->net = 0;
            vector<double> priceHist;

            for (int n = 1; i<=numPeriods; n++)
            {
                periodNet = 0;
                for (size_t ag = 0; ag <agents.size(); ag++)
                {
                    double u = uniformRandom();
                    if( u < agents[ag]->tradeProb)
                    {
                        agents[ag]->tick(this.net, this);
                    }
                }
                net = net + periodNet;
                currentPirce = exp(priceScale * net);
                priceHist[n-1] = currentPirce;
            }
            simResults[i-1] = priceHist;
        }
    }

    double buyShares(double dollars)
    {
        double price = getPrice();
        periodNet += dollars;
        return dollars / price;
    }
    double sellShares(double shares)
    {
        double price = getPrice();
        periodNet -= shares * price;
        return shares * price;
    }
    double getPrice()
    {
        return exp(priceScale * net);
    }

private:
    double uniformRandom()
    {
        return .0;
    }
};

void ValueAgent::tick(double net, Dealer* dealer)
{
    double percentageToTrade = -.5 + 1 / (1 + exp(tradeScale * net));
    if( percentageToTrade > 0)
    {
        double shares = dealer->buyShares(percentageToTrade * cash);
        adjustHoldings(-percentageToTrade*cash, shares);
    } else {
        double dollars = dealer->sellShares(-percentageToTrade * shares);
        adjustHoldings(dollars, percentageToTrade*shares);
    }
}



void MomentAgent::tick(double net, Dealer* dealer)
{
    double netDelta = net - prevNet;

    // update previously observed net
    prevNet = net;
    double percentageToTrade = -.5 + 1 / (1 + exp(-tradeScale * netDelta) );

    if (percentageToTrade > 0)
    {
        double shares = dealer->buyShares(percentageToTrade * cash);
        adjustHoldings(-percentageToTrade * cash, shares);
    } else {
        double dollars = dealer->sellShares(-percentageToTrade * shares);
        adjustHoldings(dollars, percentageToTrade * shares);
    }
}

void NoiseAgent::tick(double net, Dealer* dealer)
{
    double dollars = normalRandom() * tradeScale;
    if ( dollars > 0) {
        dealer->buyShares(dollars);
    } else {
        dealer->sellShares(-dollars / dealer->getPrice());
    }
}

vector< vector<double> > transpose(vector< vector<double> > matrix);
double percentile(const vector<double>& vect, double pct);
void reportOnPrices(const vector< vector<double> >& simResults, ostream& out)
{
    vector< vector<double> > simResultsT = transpose(simResults);
    double percentile5, percentile25, percentile50, percentile75, percentile95;
    out << "Period" << "," << "5th" << "," << "25th" << "," << "Median" << "," << "75th" << "," << "95th" << endl;
    for ( size_t  i = 0; i < simResultsT.size(); i++)
    {
        percentile5 = percentile(simResultsT[i], 5);
        percentile25 = percentile(simResultsT[i], 25);
        percentile50 = percentile(simResultsT[i], 50);
        percentile75 = percentile(simResultsT[i], 75);
        percentile95 = percentile(simResultsT[i], 95);
        out << i << "," << percentile5 << "," << percentile25 << "," << percentile50 << "," << percentile75 << "," << percentile95 << endl;
    }
}

vector< vector<double> > transpose(vector< vector<double> > matrix)
{
    vector< vector<double> > results;
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            results[i][j] = matrix[j][i];
        }
    }
    return results;
}

double percentile(const vector<double>& vect, int pct)
{
    int offset = pct * vect.size() / 100;
    return vect[offset];
}
#endif //ASSIGNMENT5_AGENTS_H
