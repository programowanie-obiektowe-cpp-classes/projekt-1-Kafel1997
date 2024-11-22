#ifndef KREDYT_HPP
#define KREDYT_HPP

class Kredyt
{
private:
    int pozostale_raty;
    double dlug;
public:
    double splac_rate();
    Kredyt();
    Kredyt(double kwota, int raty);
    ~Kredyt();
};

Kredyt::Kredyt() : pozostale_raty{0}, dlug{0} {}
Kredyt::Kredyt(double kwota,int raty) : pozostale_raty{raty}, dlug{kwota}{}
Kredyt::~Kredyt(){}

double Kredyt::splac_rate(){
    auto rata = Kredyt::dlug/Kredyt::pozostale_raty;
    Kredyt::dlug-=rata;
    return rata;
}

#endif