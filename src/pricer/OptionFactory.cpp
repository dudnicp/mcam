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
    if (optionType == "bestof")
    {
        Bestof *bestof = new Bestof(T, dates, size, weights, strike);
        return bestof;
    }
    if (optionType == "geometric_put")
    {
        GeometricPut *geometricPut = new GeometricPut(T, dates, size, strike);
        return geometricPut;
    }
}
