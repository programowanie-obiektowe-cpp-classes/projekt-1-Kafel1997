#ifndef PRACOWNIK_HPP
#define PRACOWNIK_HPP
#include "RandomNameGenerator.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
class Pracownik
{
protected:
    double      wynagrodzenie;
    std::string imie;

public:
    virtual void print() const { std::cout << Pracownik::imie << '\n'; };
    Pracownik();
    Pracownik(double wynagrodzenie);
    ~Pracownik();
};

class Inz : public Pracownik
{
private:
    double CI;

public:
    void        print() const override { std::cout << "Inżynier " << Inz::imie << " z wydziału " << Inz::wydzial << '\n'; }
    std::string wydzial;
    Inz(double CI, double payInz);
};

class Mag : public Pracownik
{
private:
    double CMag;

public:
    void        print() const override { std::cout << "Magazynier " << Mag::imie << " operator wózka: " << Mag::wozek << '\n'; }
    bool wozek;
    Mag(double CMag, double payMag);
};

class Mkt : public Pracownik
{
private:
    double CMkt;

public:
    void        print() const override { std::cout << "Marketer " << Mkt::imie << " obserwujący: " << Mkt::obserwujacy << '\n'; }
    int obserwujacy;
    Mkt(double CMkt, double payMkt);
};

class Rob : public Pracownik
{
private:
    double CRob;

public:
    void        print() const override { std::cout << "Robotnik " << Rob::imie << " rozmiar buta: " << Rob::but << '\n'; }
    double but;
    Rob(double CRob, double payRob);
};

Pracownik::Pracownik(double wynagrodzenie) : imie{getRandomName()}, wynagrodzenie{wynagrodzenie}
{}

Pracownik::Pracownik() : imie{getRandomName()}, wynagrodzenie{100}
{}

Pracownik::~Pracownik()
{}

Inz::Inz(double Ci, double payInz) : CI{Ci}, Pracownik{payInz}, wydzial{"MEiL"}
{}
Mag::Mag(double CMag, double payMag) : CMag{CMag}, Pracownik{payMag}, wozek{true}
{}
Mkt::Mkt(double CMkt, double payMkt) : CMkt{CMkt}, Pracownik{payMkt}, obserwujacy{2000}
{}
Rob::Rob(double CRob, double payRob) : CRob{CRob}, Pracownik{payRob}, but{43.5}
{}

#endif