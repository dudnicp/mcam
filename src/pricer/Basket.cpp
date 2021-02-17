#include "Basket.hpp"
#include <algorithm>

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
    double payoff = 0;
    for (int i = 0; i < size_; i++)
    {
        payoff += MGET(path, date, i) * GET(weights_, i);
    }
    payoff -= strike_;
    return std::max(payoff, 0.0);
}