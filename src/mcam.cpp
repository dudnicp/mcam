#include <iostream>
#include "jlparser/parser.hpp"
#include "PricingResults.hpp"
#include "MonteCarlo.hpp"
#include "OptionFactory.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    double T, r, strike, rho;
    PnlVect *spots, *sigma, *divid, *weights;
    string optionType;
    int size, dates, N, nSamples;

    char *infile = argv[1];
    Param *P = new Parser(infile);

    P->extract("model size", size);
    P->extract("strike", strike);
    P->extract("spot", spots, size);
    P->extract("maturity", T);
    P->extract("volatility", sigma, size);
    P->extract("interest rate", r);
    P->extract("correlation", rho);
    if (P->extract("dividend rate", divid, size, true) == false)
    {
        divid = pnl_vect_create_from_zero(size);
    }
    P->extract("option type", optionType);
    if (P->extract("payoff coefficients", weights, size, true) == false)
    {
        weights = pnl_vect_create_from_zero(size);
    }
    P->extract("dates", dates);
    P->extract("MC iterations", nSamples);
    P->extract("degree for polynomial regression", N);

    Option *opt = OptionFactory::build(optionType, T, dates, size, weights, strike);
    BlackScholesModel *bsm = new BlackScholesModel(size, r, rho, sigma, divid, spots);
    MonteCarlo mc(bsm, opt, nSamples, N);

    cout << PricingResults(mc.price()) << endl;

    pnl_vect_free(&spots);
    pnl_vect_free(&weights);
    pnl_vect_free(&sigma);
    pnl_vect_free(&divid);
    delete P;
    delete opt;
    delete bsm;

    return EXIT_SUCCESS;
}
