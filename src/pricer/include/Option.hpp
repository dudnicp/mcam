#pragma once

#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

/// \brief Classe Option abstraite
class Option
{
public:
    double T_;  /// maturité
    int dates_; /// nombre de dates d'exercice
    int size_;  /// dimension du modèle, redondant avec BlackScholesModel::size_

    /**
     * Calcule la valeur du payoff sur la trajectoire, à la date donnée
     *
     * @param[in] spots est le vecteur des valeurs des sous-jacents
     * @return phi(trajectoire)
     */
    virtual double payoff(const PnlVect *spots) = 0;

    /**
     * Crée une option en remplissant ses attributs
     * 
     * @param[in] T est la maturité de l'option
     * @param[in] dates est le nombre de dates d'exercice de l'option
     * @param[in] size est la dimension du modèle, il s'agit du nombre de sous-jacens de l'option
     */
    Option(double T, int dates, int size);

    /**
     * Detruit l'objet et libère la mémoire
     */
    virtual ~Option();
};
