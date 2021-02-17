#include "MonteCarlo.hpp"
#include <cmath>
#include <algorithm>

MonteCarlo::MonteCarlo(BlackScholesModel *mod, Option *opt, int nSamples, int N)
    : mod_(mod), opt_(opt), nSamples_(nSamples), N_(N)
{
    rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    basis_ = pnl_basis_create_from_degree(PNL_BASIS_CANONICAL, N, nSamples);
}

MonteCarlo::~MonteCarlo()
{
    pnl_rng_free(&rng_);
    pnl_basis_free(&basis_);
}

double MonteCarlo::price()
{
    double timeStep = opt_->T_ / opt_->dates_;

    PnlMat **samples = createSamples();
    PnlMat *exerciceDates = pnl_mat_create_from_scalar(nSamples_, opt_->dates_, opt_->dates_);

    PnlVect *psiCoefs = pnl_vect_create(N_);
    PnlMat *x = pnl_mat_create(nSamples_, opt_->size_);
    PnlVect *y = pnl_vect_create(nSamples_);

    for (int i = opt_->dates_ - 2; i >= 0; i--)
    {
        // TODO
    }

    PnlVect *spots = pnl_vect_create(opt_->size_);
    double price = 0;
    int firstExerciceDate;
    for (int m = 0; m < nSamples_; m++)
    {
        firstExerciceDate = MGET(exerciceDates, m, 0);
        pnl_mat_get_row(spots, samples[m], firstExerciceDate);
        price += std::exp(-mod_->r_ * firstExerciceDate * timeStep) * opt_->payoff(spots);
    }
    price = std::max(opt_->payoff(mod_->spots_), price);

    pnl_vect_free(&spots);
    pnl_vect_free(&y);
    pnl_mat_free(&x);
    pnl_vect_free(&psiCoefs);
    pnl_mat_free(&exerciceDates);
    freeSamples(&samples);

    return price;
}

PnlMat **MonteCarlo::createSamples()
{
    PnlMat **samples = new PnlMat *[nSamples_];
    for (int i = 0; i < nSamples_; i++)
    {
        samples[i] = pnl_mat_create(opt_->dates_ + 1, opt_->size_);
        mod_->asset(samples[i], opt_->T_, opt_->dates_, rng_);
    }

    return samples;
}

void MonteCarlo::freeSamples(PnlMat ***samples)
{
    for (int i = 0; i < nSamples_; i++)
    {
        pnl_mat_free(&((*samples)[i]));
    }
    delete[] * samples;
}
