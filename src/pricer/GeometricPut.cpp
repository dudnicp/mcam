#include "GeometricPut.hpp"
#include <algorithm>
#include <cmath>

GeometricPut::GeometricPut(double T, int dates, int size, double strike) : Option(T, dates, size),
                                                                           strike_(strike)
{
    spots_ = pnl_vect_create(size);
}

GeometricPut::~GeometricPut()
{
    pnl_vect_free(&spots_);
}

double GeometricPut::payoff(const PnlMat *path, int date)
{
    double payoff = 1;
    for (int i = 0; i < size_; i++)
    {
        payoff *= MGET(path, date, i);
    }
    payoff = std::pow(payoff, 1.0 / size_);
    payoff = strike_ - payoff;
    return std::max(payoff, 0.0);
}