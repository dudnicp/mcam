#include <exception>
#include "OptionFactory.hpp"
#include "Basket.hpp"
#include "Bestof.hpp"
#include "GeometricPut.hpp"

Option *OptionFactory::build(std::string optionType, double T, int dates, int size, const PnlVect *weights, double strike)
{
    if (optionType == "exchange")
    {
        Basket *basket = new Basket(T, dates, size, weights, strike);
        return basket;
    }
    else if (optionType == "bestof")
    {
        Bestof *bestof = new Bestof(T, dates, size, weights, strike);
        return bestof;
    }
    else if (optionType == "geometric_put")
    {
        GeometricPut *geometricPut = new GeometricPut(T, dates, size, strike);
        return geometricPut;
    }
    else
        throw std::invalid_argument("Unknown option type!");
}
