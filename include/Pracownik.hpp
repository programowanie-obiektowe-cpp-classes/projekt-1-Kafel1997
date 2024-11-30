#ifndef PRACOWNIK_HPP
#define PRACOWNIK_HPP
#include "RandomNameGenerator.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>

class Inz
{
private:
    const double Ci;
    double       wynagrodzenie;
    std::string  imie;

public:
    void        print() const { std::cout << "Inżynier " << Inz::imie << " z wydziału " << Inz::wydzial << '\n'; }
    std::string wydzial;
    Inz(double Ci, double payInz);
};

class Mag
{
private:
    double      CMag;
    double      wynagrodzenie;
    std::string imie;

public:
    void print() const { std::cout << "Magazynier " << Mag::imie << " operator wózka: " << Mag::wozek << '\n'; }
    bool wozek;
    Mag(double CMag, double payMag);
};

class Mkt
{
private:
    double      CMkt;
    double      wynagrodzenie;
    std::string imie;

public:
    void print() const { std::cout << "Marketer " << Mkt::imie << " obserwujący: " << Mkt::obserwujacy << '\n'; }
    int  obserwujacy;
    Mkt(double CMkt, double payMkt);
};

class Rob
{
private:
    double      CRob;
    double      wynagrodzenie;
    std::string imie;

public:
    void   print() const { std::cout << "Robotnik " << Rob::imie << " rozmiar buta: " << Rob::but << '\n'; }
    double but;
    Rob(double CRob, double payRob);
};

Inz::Inz(double Ci, double payInz) : imie{getRandomName()}, Ci{Ci}, wynagrodzenie{payInz}, wydzial{"MEiL"}
{}
Mag::Mag(double CMag, double payMag) : imie{getRandomName()}, CMag{CMag}, wynagrodzenie{payMag}, wozek{true}
{}
Mkt::Mkt(double CMkt, double payMkt) : imie{getRandomName()}, CMkt{CMkt}, wynagrodzenie{payMkt}, obserwujacy{2000}
{}
Rob::Rob(double CRob, double payRob) : imie{getRandomName()}, CRob{CRob}, wynagrodzenie{payRob}, but{43.5}
{}

#endif