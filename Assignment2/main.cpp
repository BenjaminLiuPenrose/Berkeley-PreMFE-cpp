#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

double calculateCallExerciseValue(double spot, double strike);
double calculatePutExerciseValue(double spot, double strike);


int main() {
    char question1[] = "=====Q1. ask user to enter a spot and then a strike and then print out call and put exercise value.=====\n";
    char question2[] = "=========Q2. run *for* loop and prints out call and put exercise values for a strike of 100.============\n";
    char question3[] = "=========Q3. run *for* loop and prints out call and put exercise values for a spot of 111.==============\n";
    char question4[] = "===================================Q4. ask user to enter 0 or 1=========================================\n";
    char questionEnd[] = "======================================================================================================\n\n";
    double strike(0), spot(0);
    double cexValue(0), pexValue(0);
    int zeroOrOne(0);

    // question 1
    cout << question1;
    cout << "Please enter a spot price (float): \n";
    cin >> spot;
    cout << "Please enter a strike price (float): \n";
    cin >> strike;
    cexValue = calculateCallExerciseValue(spot, strike);
    cout << "Call exercise value for strike " << strike << " and spot " << spot << " is " << cexValue << endl;
    pexValue = calculatePutExerciseValue(spot, strike);
    cout << "Put exercise value for strike " << strike << " and spot " << spot << " is " << pexValue << endl;
    cout << questionEnd;

    // question 2
    cout << question2;
    strike = 100;
    for (unsigned int s = 75; s < 126; s++)
    {
        cexValue = calculateCallExerciseValue(s, strike);
        pexValue = calculatePutExerciseValue(s, strike);
        cout << "For strike " << strike << " and spot " << s << ", the call exercise value is " << cexValue << " and the put exercise value is " << pexValue << endl;
    }
    cout << questionEnd;

    // question 3
    cout << question3;
    spot = 111;
    for (unsigned int s = 75; s < 126; s++)
    {
        cexValue = calculateCallExerciseValue(spot, s);
        pexValue = calculatePutExerciseValue(spot, s);
        cout << "For strike " << s << " and spot " << spot << ", the call exercise value is " << cexValue << " and the put exercise value is " << pexValue << endl;

    }
    cout << questionEnd;

    // question 4
    cout << question4;
    cout << "Please enter either 0 or 1: \n";
    cin >> zeroOrOne;
    if (zeroOrOne == 0)
    {
        strike = 100.0;
        cout << "Please enter a spot price: \n";
        cin >> spot;
        pexValue = calculatePutExerciseValue(spot, strike);
        cout << "The put exercise value for spot " << spot << " and strike " << strike << " is " << pexValue << endl;
    }
    else if (zeroOrOne == 1)
    {
        spot = 63.50;
        cout << "PLease enter a strike price: \n";
        cin >> strike;
        cexValue = calculateCallExerciseValue(spot, strike);
        cout << "The call exercise value for spot " << spot << " and strike " << strike << " is " << cexValue << endl;
    }
    else
    {
        cout << "[ERR:] Please enter 0 or 1";
    }
    cout << questionEnd;

    return 0;
}


double calculateCallExerciseValue(double spot, double strike)
{
    double exValue(.0);
    exValue = fmax(spot - strike , .0);

    assert( exValue >= 0);
    return exValue;
}

double calculatePutExerciseValue(double spot, double strike)
{
    double exValue(.0);
    exValue = fmax(strike - spot, .0);

    assert( exValue >= 0);
    return exValue;
}