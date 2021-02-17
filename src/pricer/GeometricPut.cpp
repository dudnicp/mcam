#include "GeometricPut.hpp"

GeometricPut::GeometricPut(double T, int dates, int size, double strike) : Option(T, dates, size),
                                                                           strike_(strike)
{
}

GeometricPut::~GeometricPut()
{
}

double GeometricPut::payoff(const PnlMat *path, int date)
{
    return 0.0;
}