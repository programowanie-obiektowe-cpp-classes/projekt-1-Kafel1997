#ifndef KREDYT_HPP
#define KREDYT_HPP

class Kredyt
{
private:
    int    pozostale_raty_;
    double dlug_;

public:
    double splac_rate();
    double get_dlug();
    Kredyt();
    Kredyt(double kwota, int raty);
    ~Kredyt();
};

Kredyt::Kredyt() : pozostale_raty_{0}, dlug_{0}
{}
Kredyt::Kredyt(double kwota, int raty) : pozostale_raty_{raty}, dlug_{kwota}
{}
Kredyt::~Kredyt()
{}

double Kredyt::splac_rate()
{
    if (Kredyt::pozostale_raty_ == 0)
    {
        return 0.0;
    }
    else
    {
        double rata = Kredyt::dlug_ / static_cast< double >(Kredyt::pozostale_raty_);
        Kredyt::dlug_ -= rata;
        Kredyt::pozostale_raty_ -= 1;
        return rata;
    }
}

double Kredyt::get_dlug()
{
    return Kredyt::dlug_;
}

#endif