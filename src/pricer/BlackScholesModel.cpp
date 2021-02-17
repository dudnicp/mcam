#include "BlackScholesModel.hpp"
#include <cmath>

BlackScholesModel::BlackScholesModel(int size, double r, double rho, const PnlVect *sigma,
                                     const PnlVect *divid, const PnlVect *spots)
    : size_(size), r_(r), rho_(rho)
{
    sigma_ = pnl_vect_copy(sigma);
    divid_ = pnl_vect_copy(divid);
    spots_ = pnl_vect_copy(spots);
    L_ = pnl_mat_create_from_scalar(size, size, rho);
    pnl_mat_set_diag(L_, 1.0, 0);
    pnl_mat_chol(L_);
    G_ = pnl_vect_create(size);
}

BlackScholesModel::~BlackScholesModel()
{
    pnl_vect_free(&sigma_);
    pnl_vect_free(&divid_);
    pnl_vect_free(&spots_);
    pnl_vect_free(&G_);
    pnl_mat_free(&L_);
}

void BlackScholesModel::asset(PnlMat *path, double T, int dates, PnlRng *rng)
{
    pnl_mat_set_row(path, spots_, 0);
    double timeStep = T / dates;

    double sigma_d, divid_d, scalarProd;
    int t, d, i;
    for (t = 1; t < dates; t++)
    {
        pnl_vect_rng_normal(G_, size_, rng);
        for (d = 0; d < size_; d++)
        {
            sigma_d = GET(sigma_, d);
            divid_d = GET(divid_, d);

            // scalarProd = l_d * G
            scalarProd = 0;
            for (i = 0; i < size_; i++)
            {
                scalarProd += GET(G_, i) * MGET(L_, d, i);
            }

            MLET(path, t, d) = MGET(path, t - 1, d) *
                               std::exp(
                                   (r_ - divid_d - sigma_d * sigma_d / 2.0) * timeStep +
                                   sigma_d * std::sqrt(timeStep) * scalarProd);
        }
    }
}