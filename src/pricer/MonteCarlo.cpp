#include "MonteCarlo.hpp"
#include <cmath>
#include <ctime>
#include <algorithm>

MonteCarlo::MonteCarlo(BlackScholesModel *mod, Option *opt, int nSamples, int N)
    : mod_(mod), opt_(opt), nSamples_(nSamples), N_(N)
{
    rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng_, time(nullptr));
    basis_ = pnl_basis_create_from_degree(PNL_BASIS_CANONICAL, N, opt->size_);
    samples_ = new PnlMat *[nSamples];
    for (int m = 0; m < nSamples; m++)
    {
        samples_[m] = pnl_mat_create(opt->dates_ + 1, opt->size_);
    }
    exerciseDates_ = pnl_vect_create(nSamples);
    psiCoefs_ = pnl_vect_create(N + 1);
    x_ = pnl_mat_create(nSamples, opt->size_);
    y_ = pnl_vect_create(nSamples);
    auxSpots_ = pnl_vect_create(opt->size_);
}

MonteCarlo::~MonteCarlo()
{
    pnl_rng_free(&rng_);
    pnl_basis_free(&basis_);
    for (int i = 0; i < nSamples_; i++)
    {
        pnl_mat_free(&(samples_[i]));
    }
    delete[] samples_;
    pnl_vect_free(&exerciseDates_);
    pnl_vect_free(&psiCoefs_);
    pnl_mat_free(&x_);
    pnl_vect_free(&y_);
    pnl_vect_free(&auxSpots_);
}

double MonteCarlo::price()
{
    sample();
    pnl_vect_set_all(exerciseDates_, opt_->dates_);

    for (int i = opt_->dates_ - 1; i >= 1; i--)
    {
        fillX(i);
        fillY(i);
        pnl_basis_fit_ls(basis_, psiCoefs_, x_, y_);
        fillExerciseDates(i);
    }

    return getPrice();
}

void MonteCarlo::sample()
{
    for (int m = 0; m < nSamples_; m++)
    {
        mod_->asset(samples_[m], opt_->T_, opt_->dates_, rng_);
    }
}

void MonteCarlo::fillX(int t)
{
    for (int m = 0; m < nSamples_; m++)
    {
        for (int i = 0; i < opt_->size_; i++)
        {
            MLET(x_, m, i) = MGET(samples_[m], t, i);
        }
    }
}

void MonteCarlo::fillY(int t)
{
    double timeStep = opt_->T_ / opt_->dates_;
    int nextExerciceDate;
    for (int m = 0; m < nSamples_; m++)
    {
        nextExerciceDate = GET(exerciseDates_, m);
        pnl_mat_get_row(auxSpots_, samples_[m], nextExerciceDate);
        LET(y_, m) = std::exp(-mod_->r_ * (nextExerciceDate - t) * timeStep) * opt_->payoff(auxSpots_);
    }
}

void MonteCarlo::fillExerciseDates(int t)
{
    double psiPayoff;
    for (int m = 0; m < nSamples_; m++)
    {
        pnl_mat_get_row(auxSpots_, samples_[m], t);
        psiPayoff = pnl_basis_eval_vect(basis_, psiCoefs_, auxSpots_);
        if (opt_->payoff(auxSpots_) >= psiPayoff)
            LET(exerciseDates_, m) = t;
    }
}

double MonteCarlo::getPrice() const
{
    double price = 0, timeStep = opt_->T_ / opt_->dates_;
    int firstExerciceDate;
    for (int m = 0; m < nSamples_; m++)
    {
        firstExerciceDate = GET(exerciseDates_, m);
        pnl_mat_get_row(auxSpots_, samples_[m], firstExerciceDate);
        price += std::exp(-mod_->r_ * firstExerciceDate * timeStep) * opt_->payoff(auxSpots_);
    }
    price /= nSamples_;
    price = std::max(opt_->payoff(mod_->spots_), price);

    return price;
}
