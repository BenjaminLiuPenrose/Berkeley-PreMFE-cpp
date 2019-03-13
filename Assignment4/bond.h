//
// Created by Benjamin on 2/23/2019.
//

#ifndef ASSIGNMENT4_BOND_H
#define ASSIGNMENT4_BOND_H
#include <math.h>
#include <iostream>
#include <random>
#include <chrono>
using namespace std;

class Bond{
public:
    double principal;
    double coupon;
    double timeToMaturity;

    Bond(double principal, double coupon, double timeToMaturity)
    {
        this->principal = principal;
        this->coupon = coupon;
        this->timeToMaturity = timeToMaturity;
    }

    double getPrice(double YTM)
    {
        double price(.0);
        price = this->principal / pow(1 + YTM, this->timeToMaturity);
        for (int i = 0; i < this->timeToMaturity; i++)
        {
            price += this->coupon * 1. / pow(1 + YTM, this->timeToMaturity - i);
        }
        return price;
    }

    double getYTM(double price)
    {
        return findRootSecant(
                this->coupon / this->principal,
                price,
                1e-8
                );
    }

    double estimateModifiedDuration(double YTM)
    {
        double duration(.0);
        duration = 100 * (getPrice(YTM) - getPrice(YTM + 0.01)) / getPrice(YTM);
        return duration;
    }

    double estimateSimulatedPrice(double hazardRate, double r, int numSimulations)
    {
        double price;
        for (int i = 0; i < numSimulations; i++)
        {
            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
            default_random_engine gen(seed);
            double T = log(2.0) / hazardRate;
            poisson_distribution<int> distribution(T);
            double defaultD = distribution(gen);
            double Tm = this->timeToMaturity;

            if (defaultD > Tm)
            {
                price = price + this->principal * 1. / pow(1+r, Tm);
            }
            while(Tm > 0)
            {
                if (defaultD > Tm)
                {
                    price = price + this->coupon * 1. / pow(1 + r, Tm);
                }
                Tm = Tm -1;
            }
        }

        price = price / double(numSimulations);
        return price;
    }

private:
    double f(double x, double price)
    {
        return price - getPrice(x);
    }
    double findRootSecant(double x, double price, double precision)
    {
        double err, xPrev, xRtn, fDelta(.0), tmp(.0);
        xPrev = x; xRtn = x + 0.25; err = f(xRtn, price);
        int cnt(0);

        while ( fabs(err) >= precision )
        {
            fDelta = f(xRtn, price) - f(xPrev, price);
            if ( fabs(fDelta) > 1e-10 ) // when fDelta is not essentially zero
            {
                tmp = xRtn;
                xRtn = xRtn - f(xRtn, price) * (xRtn - xPrev) / fDelta;
                xPrev = tmp;
                err = f(xRtn, price);
            }else{
                xPrev = xPrev + xPrev;
                err = f(xRtn, price);
            }
            cnt += 1;
        }

        return xRtn;
    }

};

#endif //ASSIGNMENT4_BOND_H
