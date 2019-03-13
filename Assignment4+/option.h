//
// Created by Benjamin on 2/23/2019.
//

#ifndef ASSIGNMENT4_OPTION_H
#define ASSIGNMENT4_OPTION_H
#include <math.h>
#include <vector>
using namespace std;

// class Option
class Option{
public:
    Option(double K, double T, double sigma, double r)
    {
        this->K = K;
        this->T = T;
        this->sigma = sigma;
        this->r = r;
    }

    virtual double getExerciseValue(double s, double t) = 0;
    virtual double getBlackScholesValue(double s) = 0;
    double getBinomialTreeValue(double s, int N)
    {
        /*
         T  expiration time
         s  stock price
         K  strike price
         sigma  volatility
         N  height of the binomial tree
         */
        double T(this->T);
        double K(this->K);
        double r(this->r);
        double sigma(this->sigma);
        double deltaT = T / (N * 1.);
        double up = exp(sigma * sqrt(deltaT));
        double down = 1. / up;
        double p0 = (up - exp(-r * deltaT)) / (up*up - 1.);
        double p1 = exp(-r * deltaT) - p0;
        double p = (up - exp(r * deltaT)) / (up - down);
        double q = 1. - p;
        double minfloat = this->minfloat;
        vector<double> priceArr(N+1);
        // initial values at time T, forward pass
        for (int i = 0; i <= N; i++)
        {
            double spot = s * pow(up, 2*i - N);
            priceArr[i] =  fmax(getExerciseValue(spot, T), .0) ;
        }

        double t = T;
        // backward pass or "back-prop"
        for (int j = N - 1; j >= 0; j--)
        {
            t = t - deltaT;
            for (int i = 0; i <= j; i++)
            {
                double spot = s * pow(up, 2*i - j);
                double exercise = getExerciseValue(spot, T);
                priceArr[i] = p0 * priceArr[i + 1] + p1 * priceArr[i];
//                priceArr[i] = (p * priceArr[i + 1] + q * priceArr[i]) * exp(-r * deltaT);
                if (priceArr[i] < exercise - minfloat)
                {
                    priceArr[i] = exercise;
                }
            }
        }

        return priceArr[0];
    }
    virtual double getValue(double s) = 0;


protected:
    double K;
    double T;
    double sigma;
    double r;
    double minfloat = 1e-8; // float point comparision
    double N = 250;
    double cdfGaussian(double x)
    {
        return 0.5 * erfc(-x * M_SQRT1_2);
    }
};

// class European Option
class EuropeanOption : public Option {
public:
    EuropeanOption(double K, double T, double sigma, double r) : Option(K, T, sigma, r)
    {}
    double getValue(double s)
    {
        return getBlackScholesValue(s);
    }
};

// European Call
class EuropeanCall : public EuropeanOption {
public:
    EuropeanCall(double K, double T, double sigma, double r) : EuropeanOption(K, T, sigma, r)
    {}
    double getExerciseValue(double s, double t)
    {
        double minfloat = this->minfloat;
        if (t <= this->T + minfloat && t >= this->T - minfloat) // float number comparision
        {
            return s - this->K;
        } else {
            return .0;
        }
    }
    double getBlackScholesValue(double s)
    {
        double d1(.0), d2(.0), pvk(.0), value(.0);
        d1 = ( log(s / this->K) + (this->r + this->sigma*this->sigma/2.0)*this->T ) / (this->sigma * sqrt(this->T));
        d2 = d1 - this->sigma * sqrt(this->T);
        pvk = this->K * exp(-this->r * this->T);
        value= cdfGaussian(d1) * s - cdfGaussian(d2) * pvk;
        return value;
    }
};

// European Put
class EuropeanPut : public EuropeanOption {
public:
    EuropeanPut(double K, double T, double sigma, double r) : EuropeanOption(K, T, sigma, r)
    {}
    double getExerciseValue(double s, double t)
    {
        double minfloat = this->minfloat;
        if (t <= this->T + minfloat && t >= this->T - minfloat) // float number comparision
        {
            return this->K - s;
        } else {
            return .0;
        }
    }
    double getBlackScholesValue(double s)
    {
        double d1(.0), d2(.0), pvk(.0), value(.0);
        d1 = ( log(s / this->K) + (this->r + this->sigma*this->sigma/2.0)*this->T ) / (this->sigma * sqrt(this->T));
        d2 = d1 - this->sigma * sqrt(this->T);
        pvk = this->K * exp(-this->r * this->T);
        value = cdfGaussian(-d2)  * pvk - cdfGaussian(-d1) * s;
        return value;
    }
};

// American Option
class AmericanOption : public Option {
public:
    AmericanOption(double K, double T, double sigma, double r) : Option(K, T, sigma, r)
    {}
    double getBlackScholesValue(double s)
    {
        return -1.; // -1 stands for NA value for American option BS value
    }
    double getValue(double s)
    {
        int N = this->N;
        return getBinomialTreeValue(s, N);
    }
};

// American Call
class AmericanCall : public AmericanOption {
public:
    AmericanCall(double K, double T, double sigma, double r) : AmericanOption(K, T, sigma, r)
    {}
    double getExerciseValue(double s, double t)
    {
        double minfloat = this->minfloat;
        if (t >= this->T + minfloat)
        {
            return .0;
        } else {
            return s - this->K;
        }
    }
};

// American Put
class AmericanPut : public AmericanOption {
public:
    AmericanPut(double K, double T, double sigma, double r) : AmericanOption(K, T, sigma, r)
    {}
    double getExerciseValue(double s, double t)
    {
        double minfloat = this->minfloat;
        if ( t >= this->T + minfloat)
        {
            return .0;
        } else {
            return this->K - s;
        }
    }
};

#endif //ASSIGNMENT4_OPTION_H
