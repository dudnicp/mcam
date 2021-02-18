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
    int N_;                  /// degré de la régression polynomiale

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
     * @param[in] N est le degré de la régression polynomiale
     */
    MonteCarlo(BlackScholesModel *mod, Option *opt, int nSamples, int N);

    /**
     * Détruit l'objet et libère la mémoire
     */
    ~MonteCarlo();

private:
    PnlRng *rng_;
    PnlBasis *basis_;
    PnlMat **samples_;
    PnlMat *exerciseDates_;
    PnlVect *psiCoefs_;
    PnlMat *x_;
    PnlVect *y_;
    PnlVect *auxSpots_;

    void sample();
    void fillX(int t);
    void fillY(int t);
    void fillExerciseDates(int t);
    double getPrice() const;
};
