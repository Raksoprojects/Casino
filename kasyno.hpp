#include <list>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
//#include <vector>
#include "gracz.hpp"

class Kasyno{

private:
    
    std::vector<Karta> talia;
    std::list<Karta> talia_const;
    vector<Gracz> gracze;
    vector<Bot> graczewirtualni;
    int ktora_karta;
    bool koniec;
    bool koniecBot;

public:
    Kasyno();
    void tasujKarty();
    Karta * dajKarte();
    void graj();
    void savetoFile();

};