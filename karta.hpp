#pragma once
#include <iostream>

class Karta {
private:
    char kolor;
    char figura;
    int wartosc;
public:
    Karta(int _kolor = 0, int _wartosc = 0);
    void setKolor(int _kolor);
    void setWartosc(int _wartosc);
    char getKolor() const { return this->kolor; }
    char getFigura() const { return this->figura; }
    int getWartosc() const { return this->wartosc; }
    void wypisz() const { std::cout << figura << kolor; }
};