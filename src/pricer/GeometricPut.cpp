#include "GeometricPut.hpp"
#include <algorithm>
#include <cmath>

GeometricPut::GeometricPut(double T, int dates, int size, double strike)
    : Option(T, dates, size), strike_(strike)
{
}

GeometricPut::~GeometricPut()
{
}

double GeometricPut::payoff(const PnlVect *spots)
{
    double payoff = 1;
    for (int i = 0; i < size_; i++)
    {
        payoff *= GET(spots, i);
    }
    payoff = std::pow(payoff, 1.0 / size_);
    payoff = strike_ - payoff;
    return std::max(payoff, 0.0);
}