#include "gracz.hpp"
#include <stdlib.h>
#include <string>

using namespace std;

// konstruktor gracza, póki co niewiele tam jest poza inicjalizacją zmiennej
Gracz::Gracz(string n) : ilePunktow(0), czyPas(false), nazwa(n){
    
}

// Funkcja dodająca punkty graczowi
void Gracz::dodajPunkty(){
    this->ilePunktow += this->reka.back().getWartosc();
    cout<<this->ilePunktow<<"\n";
}

// Proste wypisanie kart jakie posiada gracz
void Gracz::pokazKarty(){
    for(int i=0;i<this->reka.size(); ++i){
        this->reka[i].wypisz();
        cout<<"\t";
    }
    cout<<"\n";
}

// Zgodnie z wymogami zadania funkcja pobierająca kartę na rękę gracza, dodająca punkty zaraz po tym
void Gracz::wezKarte(Karta * _karta){
    this->reka.push_back(*_karta);
    this->dodajPunkty();

}

void Gracz::tura(){
    //Funkcja obejmująca turę gracza, na dobrą sprawę spradza czy nie spasowana i daje
    //możliwośc spasowania

    string input;
    system("CLS");
    
    if (!this->czySpasowano()){

        if(this->ilePunktow >= 21) this->pasuj();
        else{
            cout<<"Tura gracza "<<this->nazwa<<", masz "<<this->ilePunktow<<" punktow\ntwoja reka: "; 
            this->pokazKarty();
            cout<<"1. Pasuj\n";
            cout<<"2. Dobierz karte\n";
            while(1){
                cin>>input;
                if (cin.fail()){
                    cout<<" blad, podaj jeszcze raz\n";
                    cin.clear();
                    cin.ignore(256, '\n');
                }
                else break;
            }
            
            if(input=="1"){
                this->pasuj();
                
            }
            else{
                return;  
            }
        }
    }
    
    cout<<"Gracz spasowal\n";
    system("pause");
    
}

void Gracz::pasuj(){
    //zmienna określająca czy gracz spasował
    this->czyPas = true;
}

Gracz::~Gracz(){
    this->reka.clear();
    this->nazwa.clear();

}

void Gracz::ustawNazwe(){

    // Ustaiwanie nazwy gracza, z wykorzystaniem wymaganych kontroli strumieni
    string input;
    cout<<"Podaj swoja nazwe(maks. 20 znakow): ";

    while(1){
        cin>>input;
        if (cin.fail() || input.size()>20){
            cout<<" Blad, podaj jeszcze raz(maks. 20 znaków): ";
            cin.clear();
            cin.ignore(256, '\n');
        }
        else{
            this->nazwa = input;
            break;
        }
    }
}

void Gracz::pokazNazwe(){

    cout<<this->nazwa;
}

string Gracz::zwrocReke(){
    
    // zwracanie talii gracza, do zastąpienia symbole kolorów
    string karta;

    for(int i=0; i<this->reka.size();++i){
        // zamiana znaczków kart na kod ASCII, kier - #, karo - $, trefl - %, pik - &
        char temp = this->reka[i].getKolor()+32;
        karta = karta + this->reka[i].getFigura() + temp + " "; 
    }
    return karta;

}

ostream& operator<<(ostream& os, const Karta& dt)
{
    // specjalny operator "dla ambitnych", przy napisaniu cout<< (obiekt klasy karta); wypisze nam kartę
    os << dt.getFigura() << dt.getKolor();
    return os;
}

void Bot::turaBot(){

    // tura bota, analogicznie jak w graczu tylko obsługuje go if zależny od poziomu ryzyka

    system("CLS");
    
    if (!this->czySpasowano()){

        if(this->ilePunktow >= 21) this->pasuj();
        else{
            cout<<"Tura bota "<<this->nazwa<<", ma "<<this->ilePunktow<<" punktow\nJego reka: "; 
            this->pokazKarty();
            if(this->ilePunktow > this->limit_punktow){
                this->pasuj();
            }
            else{
                cout<<this->nazwa<<" dobiera karte\n";
                system("pause");
                return;
            }
            
        }
    }
    
    cout<<this->nazwa<<" spasowal\n";
    system("pause");
}

Bot::Bot() : limit_punktow(10){

}
Bot::~Bot(){
    this->reka.clear();
    this->nazwa.clear();
}

void Bot::ustawNazweBot(string numer){

    this->nazwa = "Bot" + numer;

}

void Bot::nadajRyzyko(){

    //ustalamy stopień ryzyka bota zgodnie z poleceniem
    string input;
    int k;
    cout<<"Podaj stopien ryzyka bota:\n";
    cout<<"0 - normalny\n";
    cout<<"1 - ryzykujacy\n";
    cout<<"2 - zachowawczy\n";
    while(1){
        
        cin>>input;
        if (cin.fail() || !(input=="0" || input=="1" || input=="2")){
            cout<<" blad, podaj jeszcze raz\n";
            cin.clear();
            cin.ignore(256, '\n');
        }
        else break;
    }
    system("CLS");
    if(input=="0") k = 0;
    else if(input=="1") k = 1;
    else k = 2;

    if(k==0) this->limit_punktow = 15;
    else if(k==1) this->limit_punktow = 19;
    else this->limit_punktow = 10;

}