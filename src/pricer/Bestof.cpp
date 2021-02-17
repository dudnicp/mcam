#include "Bestof.hpp"
#include <algorithm>

Bestof::Bestof(double T, int dates, int size, const PnlVect *weights, double strike) : Option(T, dates, size),
                                                                                       strike_(strike)
{
    weights_ = pnl_vect_copy(weights);
    spots_ = pnl_vect_create(size);
}

Bestof::~Bestof()
{
    pnl_vect_free(&weights_);
    pnl_vect_free(&spots_);
}

double Bestof::payoff(const PnlMat *path, int date)
{
    pnl_mat_get_row(spots_, path, date);
    pnl_vect_mult_vect_term(spots_, weights_);
    double payoff = pnl_vect_max(spots_) - strike_;
    return std::max(payoff, 0.0);
}