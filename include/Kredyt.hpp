#ifndef KREDYT_HPP
#define KREDYT_HPP

#include <iostream>

class Kredyt
{
private:
    int    pozostale_raty;
    double dlug;

public:
    double splac_rate();
    Kredyt();
    Kredyt(double kwota, int raty);
    ~Kredyt();
};

Kredyt::Kredyt() : pozostale_raty{0}, dlug{0}
{}
Kredyt::Kredyt(double kwota, int raty) : pozostale_raty{raty}, dlug{kwota}
{}
Kredyt::~Kredyt()
{}

double Kredyt::splac_rate()
{
    if (Kredyt::pozostale_raty == 0)
    {
        return 0.0;
    }
    else
    {
        double rata = Kredyt::dlug / static_cast< double >(Kredyt::pozostale_raty);
        Kredyt::dlug -= rata;
        Kredyt::pozostale_raty -= 1;
        std::cout << Kredyt::pozostale_raty << '\n';
        std::cout << Kredyt::dlug << '\n';
        return rata;
    }
}

#endif