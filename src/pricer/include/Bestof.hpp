#include "Option.hpp"

class Bestof : Option
{
public:
    PnlVect *weights_; /// poids des sous jacents
    double strike_;    /// strike

    double payoff(const PnlMat *path, int date);

    /**
     * Crée une option Bestof en remplissant ses attributs
     * 
     * @param[in] T est la maturité de l'option
     * @param[in] dates est le nombre de dates d'exercice de l'option
     * @param[in] size est la dimension du modèle, il s'agit du nombre de sous-jacens de l'option
     * @param[in] weights est le vecteur des poids des sous-jacents
     * @param[in] strike est le strike de l'option
     */
    Bestof(double T, int dates, int size, const PnlVect *weight, double strike);

    /**
     * Détruit l'objet et libère la mémoire
     */
    ~Bestof();
};