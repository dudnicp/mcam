#include <iostream>
#include "Option.hpp"

/**
 * @brief Fabrique d'option
 */
class OptionFactory
{
public:
    /**
     * Retourne une option du type bon type selon les paramètres d'entrée
     *
     * @param[in] optionType est une chaine de caractères définissant le type de l'option
     * @param[in] T est la maturité de l'option
     * @param[in] dates est le nombre de dates d'exercices de l'option
     * @param[in] size est le nombre de sous-jacents de l'option
     * @param[in] strike est le strike de l'option
     * @return un pointeur sur une option du type demandé construite selon les paramètres size et strike
     */
    static Option *build(std::string optionType, double T, int dates, int size, const PnlVect *weights, double strike);
};