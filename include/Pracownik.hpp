#ifndef PRACOWNIK_HPP
#define PRACOWNIK_HPP
#include "RandomNameGenerator.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
// Brak klasy bazowej pracownika, gdyż używamy std::variant i std::visit

class Inz
{
private:
    const double Ci_;
    double       wynagrodzenie_;
    std::string  imie_;

public:
    void        print() const { std::cout << "Inżynier " << Inz::imie_ << " z wydziału " << Inz::wydzial << '\n'; }
    std::string wydzial;
    Inz(double Ci_, double payInz);
};

class Mag
{
private:
    double      CMag_;
    double      wynagrodzenie_;
    std::string imie_;

public:
    void print() const { std::cout << "Magazynier " << Mag::imie_ << " operator wózka: " << Mag::wozek << '\n'; }
    bool wozek;
    Mag(double CMag_, double payMag);
};

class Mkt
{
private:
    double      CMkt;
    double      wynagrodzenie_;
    std::string imie_;

public:
    void print() const { std::cout << "Marketer " << Mkt::imie_ << " obserwujący: " << Mkt::obserwujacy << '\n'; }
    int  obserwujacy;
    Mkt(double CMkt, double payMkt);
};

class Rob
{
private:
    double      CRob;
    double      wynagrodzenie_;
    std::string imie_;

public:
    void   print() const { std::cout << "Robotnik " << Rob::imie_ << " rozmiar buta: " << Rob::but << '\n'; }
    double but;
    Rob(double CRob, double payRob);
};

Inz::Inz(double ci_, double payInz) : imie_{getRandomName()}, Ci_{ci_}, wynagrodzenie_{payInz}, wydzial{"MEiL"}
{}
Mag::Mag(double cmag_, double payMag) : imie_{getRandomName()}, CMag_{cmag_}, wynagrodzenie_{payMag}, wozek{true}
{}
Mkt::Mkt(double cmkt, double payMkt) : imie_{getRandomName()}, CMkt{cmkt}, wynagrodzenie_{payMkt}, obserwujacy{2000}
{}
Rob::Rob(double crob, double payRob) : imie_{getRandomName()}, CRob{crob}, wynagrodzenie_{payRob}, but{43.5}
{}

#endif