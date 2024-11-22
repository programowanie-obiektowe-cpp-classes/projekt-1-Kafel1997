#ifndef FIRMA_HPP
#define FIRMA_HPP
#include "Kredyt.hpp"
#include "Pracownik.hpp"
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
    const double oblicz_przychod();
    double historia_przych[N];

    double                stan_konta;
    std::vector< Kredyt > kredyty;
    int                   n_kredytow;

    int n_inz;
    int n_mag;
    int n_mkt;
    int n_rob;

    std::vector< Inz > inz;
    std::vector< Mag > mag;
    std::vector< Mkt > mkt;
    std::vector< Rob > rob;

public:
    void const drukuj_pracownikow();

    void wez_kredyt(double kwota, int czas_splaty);

    void zatrudnij_inz();
    void zatrudnij_mag();
    void zatrudnij_mkt();
    void zatrudnij_rob();

    void zaplac_wynagrodzenie();
    void otrzymaj_przychod();
    void splac_raty();

    double const get_stan_konta();
    double       wartosc_firmy();
    Firma();
    ~Firma();
};

Firma::Firma() : stan_konta{10000.}, n_kredytow{0}, n_inz{0}, n_mag{0}, n_mkt{0}, n_rob{0}
{}

Firma::~Firma()
{}

void const Firma::drukuj_pracownikow()
{
    if (Firma::n_inz == 0 && Firma::n_mag == 0 && Firma::n_mkt == 0 && Firma::n_rob == 0)
    {
        std::cout << "Brak Prackowników!\n";
    }
    else
    {

        for (Inz i : Firma::inz)
        {
            i.print();
        }
        for (Mag i : Firma::mag)
        {
            i.print();
        }
        for (Mkt i : Firma::mkt)
        {
            i.print();
        }
        for (Rob i : Firma::rob)
        {
            i.print();
        }
    }
}

void Firma::wez_kredyt(double kwota, int raty)
{
    if (Firma::n_kredytow < N_MAX_KRED)
    {
        Firma::kredyty.emplace_back(kwota, raty);
        Firma::n_kredytow += 1;
        std::cout << "Wzięto kredyt na kwotę " << kwota << " ilość rat: " << raty << '\n'
                  << "Aktualna ilość kredytów do spłacenia: " << Firma::n_kredytow << '\n';
    }
    else
    {
        std::cout << "Nie możesz wziąć więcej niż " << N_MAX_KRED << " kredytów!\n";
    }
}

void Firma::zatrudnij_inz()
{
    Firma::inz.emplace_back(CI, PAY_INZ);
    Firma::n_inz++;
}

void Firma::zatrudnij_mag()
{
    Firma::mag.emplace_back(CMAG, PAY_MAG);
    Firma::n_mag++;
}

void Firma::zatrudnij_mkt()
{
    Firma::mkt.emplace_back(CMKT, PAY_MKT);
    Firma::n_mkt++;
}

void Firma::zatrudnij_rob()
{
    Firma::rob.emplace_back(CROB, PAY_ROB);
    Firma::n_rob++;
}

void Firma::zaplac_wynagrodzenie()
{
    Firma::stan_konta -=
        Firma::n_inz * PAY_INZ + Firma::n_mag * PAY_MAG + Firma::n_mkt * PAY_MKT + Firma::n_rob * PAY_ROB;
}

void Firma::splac_raty()
{
    for (Kredyt k : Firma::kredyty)
    {
        Firma::stan_konta -= k.splac_rate();
    }
}

void Firma::otrzymaj_przychod()
{
    double produkt;
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
        Firma::stan_konta += produkt * wyprodukowane;
    }
    else
    {
        Firma::stan_konta += produkt * popyt;
    }
}

double const Firma::get_stan_konta()
{
    return Firma::stan_konta;
}

double Firma::wartosc_firmy()
{
    return -1500.0;
}

#endif