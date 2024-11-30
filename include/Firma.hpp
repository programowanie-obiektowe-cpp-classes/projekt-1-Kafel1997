#ifndef FIRMA_HPP
#define FIRMA_HPP
#include "Kredyt.hpp"
#include "Pracownik.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <variant>
#include <vector>
// stałe poszczególnych pracowników
#define CI 100
#define CMAG 100
#define CMKT 100
#define CROB 100
// Wynagrodzenie poszczególnych pracowników
#define PAY_INZ 100
#define PAY_MAG 100
#define PAY_MKT 100
#define PAY_ROB 100

#define N_MAX_KRED 6
#define N 6

class Firma
{
private:
    const double          oblicz_przychod();
    std::vector< double > historia_przych;

    double                stan_konta;
    std::vector< Kredyt > kredyty;
    int                   n_kredytow;

    int n_prac;

    int n_inz;
    int n_mag;
    int n_mkt;
    int n_rob;

    std::vector< std::unique_ptr< Pracownik > > pracownicy;

public:
    void const drukuj_pracownikow();

    void wez_kredyt(double kwota, int czas_splaty);

    void zatrudnij(int type);

    void zaplac_wynagrodzenie();
    void otrzymaj_przychod();
    void splac_raty();

    double const get_stan_konta();
    double       wartosc_firmy();
    Firma();
    ~Firma();
};

Firma::Firma() : stan_konta{10000.}, n_kredytow{0}, n_prac{0}, n_inz{0}, n_mag{0}, n_mkt{0}, n_rob{0}
{}

Firma::~Firma()
{}

void const Firma::drukuj_pracownikow()
{
    if (Firma::n_prac == 0)
    {
        std::cout << "Brak Prackowników!\n";
    }
    else
    {
        std::cout <<"\nMasz obecnie " << Firma::n_prac <<" pracowników:\n";
        for (int i = 0; i < Firma::n_prac; i++)
        {
            Firma::pracownicy[i]->print();
        }
        std::cout<<'\n';
    }
}

void Firma::wez_kredyt(double kwota, int raty)
{
    if (Firma::n_kredytow < N_MAX_KRED)
    {
        Firma::kredyty.emplace_back(kwota * (1 + static_cast< double >(raty) * 0.01), raty);
        Firma::n_kredytow += 1;
        std::cout << "Wzięto kredyt na kwotę " << kwota << " ilość rat: " << raty << '\n';
        Firma::stan_konta += kwota;
    }
    else
    {
        std::cout << "Nie możesz wziąć więcej niż " << N_MAX_KRED << " kredytów!\n";
    }
}

void Firma::zatrudnij(int type)
{
    Firma::n_prac++;
    switch (type)
    {
    case 1:
        Firma::pracownicy.push_back(std::make_unique< Inz >(CI, PAY_INZ));
        Firma::n_inz++;
        break;
    case 2:
        Firma::pracownicy.push_back(std::make_unique< Mag >(CMAG, PAY_MAG));
        Firma::n_mag++;
        break;
    case 3:
        Firma::pracownicy.push_back(std::make_unique< Mkt >(CMKT, PAY_MKT));
        Firma::n_mkt++;
        break;
    case 4:
        Firma::pracownicy.push_back(std::make_unique< Rob >(CROB, PAY_ROB));
        Firma::n_rob++;
        break;
    }
}

void Firma::zaplac_wynagrodzenie()
{
    Firma::stan_konta -=
        Firma::n_inz * PAY_INZ + Firma::n_mag * PAY_MAG + Firma::n_mkt * PAY_MKT + Firma::n_rob * PAY_ROB;
}

void Firma::splac_raty()
{
    int i = 0;
    for (Kredyt& k : Firma::kredyty)
    {
        double rata = k.splac_rate();
        if (rata == 0)
        {
            std::cout << "kredyt nr " << i + 1 << " spłacony! \n";
            Firma::kredyty.erase(Firma::kredyty.begin() + i);
            Firma::n_kredytow -= 1;
        }
        else
        {
            Firma::stan_konta -= rata;
            i++;
        }
    }
    std::cout  << "Aktualna ilość kredytów do spłacenia: " << Firma::n_kredytow << '\n';
}

void Firma::otrzymaj_przychod()
{
    double produkt, przychod;
    int    pojemnosc, podaz, popyt, wyprodukowane;

    popyt     = Firma::n_mkt * CMKT;
    pojemnosc = Firma::n_mag * CMAG;
    podaz     = Firma::n_rob * CROB;

    produkt = Firma::n_inz * CI;

    if (podaz <= pojemnosc)
    {
        wyprodukowane = podaz;
    }
    else
    {
        wyprodukowane = pojemnosc;
    }

    if (popyt >= wyprodukowane)
    {
        przychod = produkt * wyprodukowane;
    }
    else
    {
        przychod = produkt * popyt;
    }

    Firma::stan_konta += przychod;
    if (Firma::historia_przych.size() < N)
    {
        Firma::historia_przych.push_back(przychod);
    }
    else
    {
        Firma::historia_przych.erase(Firma::historia_przych.begin());
        Firma::historia_przych.push_back(przychod);
    }
    for (double h : Firma::historia_przych)
    {
        std::cout << h << '\n';
    }
}

double const Firma::get_stan_konta()
{
    return Firma::stan_konta;
}

double Firma::wartosc_firmy()
{
    double suma = 0;
    for (double m : Firma::historia_przych)
    {
        suma += m;
    }
    return suma / Firma::historia_przych.size();
}

#endif