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
    int   tura_;

public:
    void akcjaGracza();
    bool getStan() { return stan_; }
    Gra() : stan_{true}, tura_{1} {}
    ~Gra() {}
};

void Gra::akcjaGracza()
{
    std::string komenda;
    std::cout << "Miesiąc nr. " << Gra::tura_ << '\n';
    std::cout << "\npodaj akcję do wykonania...\n";
    std::cin >> komenda;
    if (komenda == "zinz")
    {
        std::cout << "zatrudnij inzyniera\n";
        Gra::firma_.zatrudnij(1);
    }
    else if (komenda == "zmag")
    {
        std::cout << "zatrudnij magazyniera\n";
        Gra::firma_.zatrudnij(2);
    }
    else if (komenda == "zmkt")
    {
        std::cout << "zatrudnij marketera\n";
        Gra::firma_.zatrudnij(3);
    }
    else if (komenda == "zrob")
    {
        std::cout << "zatrudnij robotnika\n";
        Gra::firma_.zatrudnij(4);
    }
    else if (komenda == "kredyt")
    {
        double kwota;
        int    raty;

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

        Gra::firma_.wezKredyt(kwota, raty);
    }
    else if (komenda == "lp")
    {
        std::cout << "###### lista pracownikow #####\n";
        Gra::firma_.drukujPracownikow();
    }
    else if (komenda == "kt")
    {
        std::cout << "\n##### KONIEC MIESIĄCA #####";
        Gra::tura_++;
        Gra::firma_.zaplacWynagrodzenie();
        Gra::firma_.splacRaty();
        Gra::firma_.otrzymajPrzychod();

        double stan_konta    = Gra::firma_.getStanKonta();
        double wartoscFirmy = Gra::firma_.wartoscFirmy();
        std::cout << "Stan konta wynosi: " << stan_konta << '\n';
        std::cout << "\nWartość firmy wynosi: " << wartoscFirmy << "\n";

        if (wartoscFirmy - Gra::firma_.zadluzenie() >= WYGRANA)
        {
            std::cout << "Gratulacje, Wygrałeś!\n";
            Gra::stan_ = false;
        }
        else if (stan_konta < 0)
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