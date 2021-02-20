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
    PnlRng *rng_;            /// générateur de nombres aléatoires
    PnlBasis *basis_;        /// base de régression polynomiale
    PnlMat **samples_;       /// liste des trajéctoires simulées
    PnlVect *exerciseDates_; /// vecteur des dates d'exercice (Tau_i^m dans l'algorithme de LS)
    PnlVect *psiCoefs_;      /// coefficients de la régression polynomiale
    PnlMat *x_;              /// points où la valeur de la régression polynomiale est connée
    PnlVect *y_;             /// valeurs connues de la regression polynomiale
    PnlVect *auxSpots_;      /// vecteur auxiliaire pour stocker temporairement les prix des sous-jacents

    /**
     * Simule nSamples_ trajectoires de sous-jacents
     */
    void sample();

    /**
     * Rempli la matrice x_ pour la regression polynomiale
     * 
     * @param[in] t correspond au t_i de l'algorithme LS
     */
    void fillX(int t);

    /**
     * Rempli le vecteur y_ pour la regression polynomiale
     * 
     * @param[in] t correspond au t_i de l'algorithme LS
     */
    void fillY(int t);

    /**
     * Rempli la matrice des dates d'exercice
     * 
     * @param[in] t correspond au t_i de l'algorithme LS
     */
    void fillExerciseDates(int t);

    /**
     * Dernière étape de l'algorithme LS
     * @return le prix en 0 de l'option
     */
    double getPrice() const;
};
