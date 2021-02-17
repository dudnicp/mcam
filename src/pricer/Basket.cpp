#include "Basket.hpp"

Basket::Basket(double T, int dates, int size, const PnlVect *weights, double strike) : Option(T, dates, size),
                                                                                       strike_(strike)
{
    weights_ = pnl_vect_copy(weights);
}

Basket::~Basket()
{
    pnl_vect_free(&weights_);
}

double Basket::payoff(const PnlMat *path, int date)
{
    return 0.0;
}