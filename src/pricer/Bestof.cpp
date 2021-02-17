#include "Bestof.hpp"

Bestof::Bestof(double T, int dates, int size, const PnlVect *weights, double strike) : Option(T, dates, size),
                                                                                       strike_(strike)
{
    weights_ = pnl_vect_copy(weights);
}

Bestof::~Bestof()
{
    pnl_vect_free(&weights_);
}

double Bestof::payoff(const PnlMat *path, int date)
{
    return 0.0;
}