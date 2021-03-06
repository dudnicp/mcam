#pragma once

#include "Option.hpp"

class GeometricPut : public Option
{
public:
    double strike_; /// strike

    double payoff(const PnlVect *spots);

    /**
     * Crée une option put géométrique en remplissant ses attributs
     * 
     * @param[in] T est la maturité de l'option
     * @param[in] dates est le nombre de dates d'exercice de l'option
     * @param[in] size est la dimension du modèle, il s'agit du nombre de sous-jacens de l'option
     * @param[in] strike est le strike de l'option
     */
    GeometricPut(double T, int dates, int size, double strike);

    /**
     * Détruit l'objet et libère la mémoire
     */
    ~GeometricPut();
};