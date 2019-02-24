#include <iostream>
#include <math.h>

using namespace std;

double f(double x);
double fPrime(double x);
double findRootNewton(double x, double precision);
double findRootSecant(double x, double precision);
double findRootBisection(double x, double precision);
bool app(double x, double precision);

int main() {
    double xs[4] = {-12, 3.2, -9.5, 8};
    double precisions[3] = {1e-6, 1e-8, 1e-10};

//    for (unsigned int i = 0, i < 4, i++)
    for (auto& precision: precisions)
    {
        for(auto& x : xs)
        {
            app(x, precision);
        }
    }

    return 0;
}

bool app(double x, double precision)
{
    double xNewton, xSecant, xBisection;

    xNewton = findRootNewton(x, precision);
    xSecant = findRootSecant(x, precision);
    xBisection = findRootBisection(x, precision);

    return true;
}


double f(double x)
{
    double rtn(.0);
    rtn = x * x* x * x - 181.0 * x * x + 8100.0;
    return rtn;
}

double fPrime(double x)
{
    double rtn(.0);
    rtn = 4 * x * x * x - 362.0 * x;
    return rtn;
}

double findRootNewton(double x, double precision)
{
    double err, xRtn;
    err = f(x); xRtn = x;
    int cnt(0);

    while ( fabs(err) >= precision )
    {
        if ( fabs(fPrime(xRtn)) > 1e-10 ) // when fPrime is not essentially zero
        {
            xRtn = xRtn - f(xRtn) / fPrime(xRtn);
            err = f(xRtn);
        }else{
            cout << "[WARN:] findRootNewton divisor is closed to zero" << endl;
            xRtn = xRtn + xRtn;
            err = f(xRtn);
        }
        cnt += 1;
    }

    cout << "Under precision " << precision << " and starting point " << x << " by Newton's method:" << endl;
    cout << "The estimated root r is " << xRtn << ", value of f(r) is " << f(xRtn) << ", number of iters is " << cnt << endl;
    return xRtn;
}

double findRootSecant(double x, double precision)
{
    double err, xPrev, xRtn, fDelta(.0), tmp(.0);
    xPrev = x; xRtn = x + 0.25; err = f(xRtn);
    int cnt(0);

    while ( fabs(err) >= precision )
    {
        fDelta = f(xRtn) - f(xPrev);
        if ( fabs(fDelta) > 1e-10 ) // when fDelta is not essentially zero
        {
            tmp = xRtn;
            xRtn = xRtn - f(xRtn) * (xRtn - xPrev) / fDelta;
            xPrev = tmp;
            err = f(xRtn);
        }else{
            cout << "[WARN:] findRootSecant divisor is closed to zero" << endl;
            xPrev = xPrev + xPrev;
            err = f(xRtn);
        }
        cnt += 1;
    }


    cout << "Under precision " << precision << " and starting point " << x << " by Secant method:" << endl;
    cout << "The estimated root r is " << xRtn << ", value of f(r) is " << f(xRtn) << ", number of iters is " << cnt << endl;
    return xRtn;
}

double findRootBisection(double x, double precision)
{
    double err, xPrev, xRtn, fA(.0), fB(.0), fMid(.0), tmp(.0);
    int cnt(0);
    xPrev = x;
    if ( f(xPrev) > 0 )
    {
        xRtn = 9.5;
    }else if( f(xPrev) < 0 ){
        xRtn = - 11.0;
    }else{
        xRtn = xPrev;
        cout << "Under precision " << precision << " and starting point " << x << " by Bisection method:" << endl;
        cout << "The estimated root r is " << xRtn << ", value of f(r) is " << f(xRtn) << ", number of iters is " << cnt << endl;
        return xRtn; // for code performance optimization
    }
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
                cout << "[ERR:] This case in findRootBisection shouldn't happen " << endl;
                return 0; // this case shouldn't happen and will always return 0
            }
        }
        cnt += 1;
    }

    cout << "Under precision " << precision << " and starting point " << x << " by Bisection method:" << endl;
    cout << "The estimated root r is " << xRtn << ", value of f(r) is " << f(xRtn) << ", number of iters is " << cnt << endl;
    return xRtn;
}

