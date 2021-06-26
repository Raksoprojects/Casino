#include "karta.hpp"
//#include "kasyno.hpp"
#include <vector>

using namespace std;


class Gracz{

protected:
vector<Karta> reka;
int ilePunktow;
bool czyPas;
string nazwa;

public:
Gracz(string n="zawodnik");
~Gracz();
void wezKarte(Karta * _karta);
void dodajPunkty();
void pokazKarty();
bool czySpasowano() const { return this->czyPas; }
void pasuj();
void tura();
int ile_zdobyto_punktow() const { return this->ilePunktow; } // Podlicza punkty
void ustawNazwe();
void pokazNazwe();
string zwrocReke();
string zwrocNazwe() { return this->nazwa;}
friend ostream& operator<<(ostream& os, const Karta& dt);
int wielkoscReki() const { return this->reka.size(); }

};

class Bot : public Gracz{
    // klasa bot dziedzicząca po graczu

    private:
    
    int limit_punktow; // 0 - podstawowe ryzyko/normalny, 1- ryzykujący, 2-zachowawczy 

    public:
    void turaBot();
    void ustawNazweBot(string numer);
    Bot();
    ~Bot();
    void nadajRyzyko();

};