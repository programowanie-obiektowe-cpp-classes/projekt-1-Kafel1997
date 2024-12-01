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
#define PAY_MKT 150
#define PAY_ROB 200
// Maksymalna liczba kredytów
#define N_MAX_KRED 6
// Stała N - z ilu miesięcy wyznaczać wartość firmy
#define N 6
// Stała M określa ile razy zadłużenie może przekraczać wartość firmy
#define M 5
// variant dla różnych klas pracowników
using Pracownik = std::variant< Inz, Mag, Mkt, Rob >;

class Firma
{
private:
    const double          oblicz_przychod();
    std::vector< double > historia_przych_;

    double                stan_konta_;
    std::vector< Kredyt > kredyty_;
    int                   n_kredytow_;

    int n_prac_;

    int n_inz_;
    int n_mag_;
    int n_mkt_;
    int n_rob_;

    std::vector< Pracownik > pracownicy;

public:
    void const drukuj_pracownikow();

    void wez_kredyt(double kwota, int czas_splaty);

    void zatrudnij(int type);

    void zaplac_wynagrodzenie();
    void otrzymaj_przychod();
    void splac_raty();

    double const get_stan_konta();
    double       wartosc_firmy();
    double       zadluzenie();
    Firma();
    ~Firma() = default;
};

Firma::Firma() : stan_konta_{10000.}, n_kredytow_{0}, n_prac_{0}, n_inz_{0}, n_mag_{0}, n_mkt_{0}, n_rob_{0}
{}

void const Firma::drukuj_pracownikow()
{
    if (Firma::n_prac_ == 0)
    {
        std::cout << "Brak Prackowników!\n";
    }
    else

    {
        std::cout << "\nMasz obecnie " << Firma::n_prac_ << " pracowników:\n";
        for (const auto& p : Firma::pracownicy)
        {
            std::visit([](const auto& prac) { prac.print(); }, p);
        }
    }
}

void Firma::wez_kredyt(double kwota, int raty)
{
    if (Firma::n_kredytow_ < N_MAX_KRED)
    {
        if (Firma::zadluzenie() + kwota > M * Firma::wartosc_firmy())
        {
            std::cout << "Całkowite zadłużenie firmy nie może być większe niż jej wartość razy " << M << "!\n";
        }
        else
        {
            Firma::kredyty_.emplace_back(kwota * (1 + static_cast< double >(raty) * 0.01), raty);
            Firma::n_kredytow_ += 1;
            std::cout << "Wzięto kredyt na kwotę " << kwota << " ilość rat: " << raty << '\n';
            Firma::stan_konta_ += kwota;
        }
    }
    else
    {
        std::cout << "Nie możesz wziąć więcej niż " << N_MAX_KRED << " kredytów!\n";
    }
}

void Firma::zatrudnij(int type)
{
    Firma::n_prac_++;
    switch (type)
    {
    case 1:
        Firma::pracownicy.emplace_back(Inz{CI, PAY_INZ});
        Firma::n_inz_++;
        break;
    case 2:
        Firma::pracownicy.emplace_back(Mag{CMAG, PAY_MAG});
        Firma::n_mag_++;
        break;
    case 3:
        Firma::pracownicy.emplace_back(Mkt{CMKT, PAY_MKT});
        Firma::n_mkt_++;
        break;
    case 4:
        Firma::pracownicy.emplace_back(Rob{CROB, PAY_ROB});
        Firma::n_rob_++;
        break;
    }
}

void Firma::zaplac_wynagrodzenie()
{
    auto wynagrodzenie =
        Firma::n_inz_ * PAY_INZ + Firma::n_mag_ * PAY_MAG + Firma::n_mkt_ * PAY_MKT + Firma::n_rob_ * PAY_ROB;
    Firma::stan_konta_ -= wynagrodzenie;
    std::cout << "\nWypłacono pracownikom wynagrodzenie w wysokości: " << wynagrodzenie << '\n';
}

void Firma::splac_raty()
{
    int i = 0;
    for (Kredyt& k : Firma::kredyty_)
    {
        double rata = k.splac_rate();
        if (rata == 0)
        {
            std::cout << "kredyt nr " << i + 1 << " spłacony! \n";
            Firma::kredyty_.erase(Firma::kredyty_.begin() + i);
            Firma::n_kredytow_ -= 1;
        }
        else
        {
            Firma::stan_konta_ -= rata;
            i++;
        }
    }
    std::cout << "\nAktualna ilość kredytów do spłacenia: " << Firma::n_kredytow_ << '\n';
}

void Firma::otrzymaj_przychod()
{
    double produkt, przychod;
    int    pojemnosc, podaz, popyt, wyprodukowane;

    popyt     = Firma::n_mkt_ * CMKT;
    pojemnosc = Firma::n_mag_ * CMAG;
    podaz     = Firma::n_rob_ * CROB;

    produkt = Firma::n_inz_ * CI;

    if (podaz <= pojemnosc)
    {
        wyprodukowane = podaz;
    }
    else
    {
        wyprodukowane = pojemnosc;
    }

    std::cout << "\nWyprodukowano " << wyprodukowane << " produktów.\n";

    if (popyt >= wyprodukowane)
    {
        przychod = produkt * wyprodukowane;
    }
    else
    {
        przychod = produkt * popyt;
    }

    std::cout << "\nOtrzymany przychód: " << przychod << '\n';

    Firma::stan_konta_ += przychod;
    if (Firma::historia_przych_.size() < N)
    {
        Firma::historia_przych_.push_back(przychod);
    }
    else
    {
        Firma::historia_przych_.erase(Firma::historia_przych_.begin());
        Firma::historia_przych_.push_back(przychod);
    }
    std::cout << "\nHistoria przychodu:\n";
    for (double h : Firma::historia_przych_)
    {
        std::cout << h << '\n';
    }
}

double const Firma::get_stan_konta()
{
    return Firma::stan_konta_;
}

double Firma::wartosc_firmy()
{
    auto dlugosc = Firma::historia_przych_.size();
    if(dlugosc==0)
    {
        return 0;
    }
    else
    {
        double suma = 0;
        double wartosc_firmy;
        for (double m : Firma::historia_przych_)
        {
            suma += m;
        }
        wartosc_firmy = static_cast<double>(suma / dlugosc);
        return wartosc_firmy;
    }
}

double Firma::zadluzenie()
{
    if (Firma::n_kredytow_ == 0)
    {
        return 0;
    }
    else
    {
        double zadluzenie = 0;
        for (Kredyt k : Firma::kredyty_)
        {
            zadluzenie += k.get_dlug();
        }
        return zadluzenie;
    }
}

#endif