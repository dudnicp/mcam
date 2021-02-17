#pragma once

#include "Option.hpp"
#include "BlackScholesModel.hpp"
#include "pnl/pnl_random.h"
#include "pnl/pnl_basis.h"

class MonteCarlo
{
public:
    BlackScholesModel *mod_; /// pointeur vers le modèle
    Option *opt_;            /// pointeur sur l'option
    int nSamples_;           /// nombre de tirages Monte Carlo
    int N_;                  /// dimension de la base de régression

    /**
     * Calcule le prix de l'option à la date 0
     *
     * @return valeur de l'estimateur Monte Carlo
     */
    double price();

    /**
     * Crée une pricer de Monte Carlo et rempli ses attributs
     * 
     * @param[in] mod est le modèle de Black-Scholes utilisé par le pricer
     * @param[in] opt est l'option à pricer
     * @param[in] nSamples est le nombre de tirages Monte Carlo
     * @param[in] N est la dimension de la base de régression
     */
    MonteCarlo(BlackScholesModel *mod, Option *opt, int nSamples, int N);

    /**
     * Détruit l'objet et libère la mémoire
     */
    ~MonteCarlo();

private:
    PnlRng *rng_;
    PnlBasis *basis_;

    PnlMat **createSamples();
    void freeSamples(PnlMat ***samples);
};
