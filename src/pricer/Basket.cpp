#include "Basket.hpp"
#include <algorithm>

Basket::Basket(double T, int dates, int size, const PnlVect *weights, double strike) : Option(T, dates, size),
                                                                                       strike_(strike)
{
    weights_ = pnl_vect_copy(weights);
    spots_ = pnl_vect_create(size);
}

Basket::~Basket()
{
    pnl_vect_free(&weights_);
    pnl_vect_free(&spots_);
}

double Basket::payoff(const PnlMat *path, int date)
{
    pnl_mat_get_row(spots_, path, date);
    double payoff = pnl_vect_scalar_prod(spots_, weights_) - strike_;
    return std::max(payoff, 0.0);
}