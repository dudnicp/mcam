#pragma once

#include "pnl/pnl_random.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

/// \brief Modèle de Black Scholes
class BlackScholesModel
{
public:
    int size_;       /// nombre d'actifs du modèle
    double r_;       /// taux d'intérêt
    double rho_;     /// paramètre de corrélation
    PnlVect *sigma_; /// vecteur de volatilités
    PnlVect *divid_; /// vecteur des dividendes
    PnlVect *spots_; /// valeurs initiales des sous-jacents

    /**
     * Génère une trajectoire du modèle et la stocke dans path
     *
     * @param[out] path contient une trajectoire du modèle.
     * C'est une matrice de taille (nbTimeSteps+1) x d
     * @param[in] T  maturité
     * @param[in] dates nombre de dates d'exercice
     */
    void asset(PnlMat *path, double T, int dates, PnlRng *rng);

    /**
     * Crée un modèle de Black-Scholes en remplissant ses attributs
     * 
     * @param[in] size est le nombre d'actifs du modèle
     * @param[in] r est le taux d'intérêt
     * @param[in] rho est le paramètre de corrélation
     * @param[in] sigma est le vecteur des volatilités
     * @param[in] divid est le vecteur des dividendes
     * @param[in] spots est le vecteur des valeurs initiales des sous-jacents
     */
    BlackScholesModel(int size, double r, double rho, const PnlVect *sigma, const PnlVect *divid, const PnlVect *spots);

    /**
     * Détruit l'objet et libère la mémoire
     */
    ~BlackScholesModel();

private:
    PnlMat *L_;  /// Cholesky de la matrice de correlation
    PnlVect *G_; /// Vecteur de variables aléatoires normales centrées réduites
};
