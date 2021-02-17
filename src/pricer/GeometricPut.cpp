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
    pnl_mat_get_row(spots_, path, date);
    pnl_vect_cumprod(spots_);
    double payoff = strike_ - std::pow(pnl_vect_get(spots_, size_ - 1), 1.0 / size_);
    return std::max(payoff, 0.0);
}