#include "Bestof.hpp"
#include <algorithm>

Bestof::Bestof(double T, int dates, int size, const PnlVect *weights, double strike)
    : Option(T, dates, size), strike_(strike)
{
    weights_ = pnl_vect_copy(weights);
}

Bestof::~Bestof()
{
    pnl_vect_free(&weights_);
}

double Bestof::payoff(const PnlVect *spots)
{
    double payoff = GET(spots, 0) * GET(weights_, 0), current = 0;
    for (int i = 1; i < size_; i++)
    {
        current = GET(spots, i) * GET(weights_, i);
        if (current > payoff)
            payoff = current;
    }
    payoff -= strike_;
    return std::max(payoff, 0.0);
}