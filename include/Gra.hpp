#ifndef GRA_HPP
#define GRA_HPP
#include "Firma.hpp"
#include "Kredyt.hpp"
#include "Pracownik.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#define WYGRANA 1000000

class Gra
{
private:
    bool  stan_;
    Firma firma_;

public:
    void akcja_gracza();
    bool get_stan() { return stan_; }
    Gra() : stan_{true} {}
    ~Gra() {}
};

void Gra::akcja_gracza()
{
    std::string komenda;
    std::cout << "podaj akcję do wykonania...\n";
    std::cin >> komenda;
    if (komenda == "zinz")
    {
        std::cout << "zatrudnij inzyniera\n";
        Gra::firma_.zatrudnij_inz();
    }
    else if (komenda == "zmag")
    {

        std::cout << "zatrudnij magazyniera\n";
        Gra::firma_.zatrudnij_mag();
    }
    else if (komenda == "zmkt")
    {

        std::cout << "zatrudnij marketera\n";
        Gra::firma_.zatrudnij_mkt();
    }
    else if (komenda == "zrob")
    {

        std::cout << "zatrudnij robotyka\n";
        Gra::firma_.zatrudnij_rob();
    }
    else if (komenda == "kredyt")
    {
        double kwota;
        int raty;

        std::cout << "jaka kwota kredytu? Max 100k\n";
        while (true)
        {
            while (!(std::cin >> kwota))
            {
                std::cout << "Invalid input. Please enter a floating-point number!\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
            }

            if (kwota > 0 && kwota <= 100000)
            {
                break;
            }
            else
            {
                std::cout << "Nieprawidlowa kwota kredytu! Sprobuj ponownie!\n";
                continue;
            }
        }

        std::cout << "Ile rat? Max 12\n";
        while (true)
        {
            while (!(std::cin >> raty))
            {
                std::cout << "Invalid input. Please enter an integer!\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
            }

            if (raty > 0 && raty <= 12)
            {
                break;
            }
            else
            {
                std::cout << "Nieprawidlowa liczba rat kredytu! Sprobuj ponownie!\n";
                continue;
            }
        }

        Gra::firma_.wez_kredyt(kwota,raty);

    }
    else if (komenda == "lp")
    {
        std::cout << "lista pracownikow:\n";
        Gra::firma_.drukuj_pracownikow();
    }
    else if (komenda == "kt")
    {
        std::cout << "koniec tury\n";

        Gra::firma_.zaplac_wynagrodzenie();
        Gra::firma_.splac_raty();
        Gra::firma_.otrzymaj_przychod();

        double wartosc = Gra::firma_.get_stan_konta();
        std::cout << "Stan konta wynosi: " << wartosc << '\n';

        if (wartosc >= WYGRANA)
        {
            std::cout << "Gratulacje, Wygrałeś!\n";
        }
        else if (wartosc < 0)
        {
            std::cout << "Game Over! :(\n";
            Gra::stan_ = false;
        }
    }
    else
    {
        std::cout << "nieprawidlowa komenda!\n";
    }
};

#endif