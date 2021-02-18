#include "Basket.hpp"
#include <algorithm>

Basket::Basket(double T, int dates, int size, const PnlVect *weights, double strike)
    : Option(T, dates, size), strike_(strike)
{
    weights_ = pnl_vect_copy(weights);
}

Basket::~Basket()
{
    pnl_vect_free(&weights_);
}

double Basket::payoff(const PnlVect *spots)
{
    double payoff = pnl_vect_scalar_prod(spots, weights_) - strike_;
    return std::max(payoff, 0.0);
}