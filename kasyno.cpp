#include "kasyno.hpp"
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Inicjalizacja kasyna, ustawienia wartości zmiennej sprawdzającej którą kartę wydać
// oraz inicjalizacja talii kart w formie wektora
Kasyno::Kasyno() : ktora_karta(52), koniec(false), koniecBot(false){
        
        Karta temp;
        for(int i=0;i<4;++i){
            for (int j =0;j<13;++j){
                
                temp.setKolor(i);
                temp.setWartosc(j);
                this->talia.push_back(temp);
            }
        }
    }

// Potasowanie kart znajdujądcych się w wektorze zgodnie z podpowiedzią w zadaniu
void Kasyno::tasujKarty(){

    int number1 = 0;
    int number2 = 0;
    Karta card1;
    Karta card2;

    for(int i=0; i< 100; ++i){

        number1 = rand() % 52;
        number2 = rand() % 52;

        card1 = this->talia[number1];
        card2 = this->talia[number2];
        this->talia[number1] = card2;
        this->talia[number2] = card1;

    }
    // a następne skopiowanie tego do listy
    // robi się to bo elementów listy nie można normalnie zmieniać
    // i by spełnić założenia projektu w ramach funkcji Karta * dajKarte()
    std::copy(this->talia.begin(), this->talia.end(), std::back_inserter(this->talia_const));

}

Karta * Kasyno::dajKarte(){

    // przy wydawaniu kart zmniejszamy zmienną pilnującą która karta jest do wydania
    this->ktora_karta -=1;
    if (this->ktora_karta >=0) {
        // auto by automatycznmie wykryć typ zmiennej
        auto it = this->talia_const.begin();
        auto nx = next(it, ktora_karta);
        // wobec wymagań projektowych by zwrócić typ jaki jest wymagany przez funkcję
        // musimy użyć listy by przekazać referencję do karty
        return &*nx;
        
        }
    return 0;    
}

void Kasyno::graj(){

    // rozpoczęcie grania z pierwszego etapu
    // rozszerzenie o drugi etap
    // rozdanie dwóch kart i rozpoczęcie gry
    string input;
    int ludzie;
    cout<<"Podaj liczbe graczy ludzkich(1-3): ";
    while(1){
        
        cin>>input;
        ludzie = stoi(input);
        if (cin.fail() || ludzie>3 || ludzie<1){
            cout<<" blad, podaj jeszcze raz\n";
            cin.clear();
            cin.ignore(256, '\n');
        }
        else break;
    }

    // Ustawianie nazw graczy
    for(int i=0;i<ludzie;++i){
        Gracz temp;
        temp.ustawNazwe();
        this->gracze.push_back(temp);
    }
    system("CLS");
    int boty;
    cout<<"Podaj liczbe graczy wirtualnych(1-3): ";
    while(1){
        
        cin>>input;
        boty = stoi(input);
        if (cin.fail() || boty>3 || boty<1){
            cout<<" blad, podaj jeszcze raz\n";
            cin.clear();
            cin.ignore(256, '\n');
        }
        else break;
    }
    system("CLS");
    // Ustawianie nazw botów
    for(int i=0;i<boty;++i){
        Bot temp1;
        this->graczewirtualni.push_back(temp1);
        this->graczewirtualni[i].ustawNazweBot(to_string(i+1));
        this->graczewirtualni[i].nadajRyzyko();
    }

    // tasowanie talii
    this->tasujKarty();
    // dobieranie dla botów i ludzi
    for(int i=0;i<this->gracze.size();++i){
        
        this->gracze[i].wezKarte(this->dajKarte());
        this->gracze[i].wezKarte(this->dajKarte());
    }
    
    for(int i=0;i<this->graczewirtualni.size();++i){
        
        this->graczewirtualni[i].wezKarte(this->dajKarte());
        this->graczewirtualni[i].wezKarte(this->dajKarte());
    }

    system("pause");
    while(!this->koniec && !this->koniecBot){
        // wykonywane dopóki gra się nie skończy
        // o ile nie spasowano to następuje tura gracza
        
        // tury botów, działa tak samo jak graczy
        for(int i=0;i<this->graczewirtualni.size();++i){
            if(this->graczewirtualni[i].czySpasowano()){

                this->koniecBot = true;
            }
            else{
                this->koniecBot = false;
                this->graczewirtualni[i].turaBot();
                if(!this->graczewirtualni[i].czySpasowano()) this->graczewirtualni[i].wezKarte(this->dajKarte());
            }
        }

        for(int i=0;i<this->gracze.size();++i){
            if(this->gracze[i].czySpasowano()){

                this->koniec = true;
            }
            else{
                this->koniec = false;
                this->gracze[i].tura();
                if(!this->gracze[i].czySpasowano()) this->gracze[i].wezKarte(this->dajKarte());
            }
        }

    }
    // Wyświetlanie i obsługa wyników gry
    system("CLS");
    cout<<"Zakonczono gre\n";
    int najwiecej=0;

    for(int i=0;i<this->gracze.size();++i){

        if(this->gracze[i].ile_zdobyto_punktow() > najwiecej && this->gracze[i].ile_zdobyto_punktow()<22) najwiecej = this->gracze[i].ile_zdobyto_punktow();
    }

    // sprawdzanie warunków dla botów
    for(int i=0;i<this->graczewirtualni.size();++i){

        if(this->graczewirtualni[i].ile_zdobyto_punktow() > najwiecej && this->graczewirtualni[i].ile_zdobyto_punktow()<22) najwiecej = this->graczewirtualni[i].ile_zdobyto_punktow();
    }


    for(int i=0;i<this->gracze.size();++i){
        if(this->gracze[i].ile_zdobyto_punktow() == najwiecej){
            cout<<"Wygrywa "<<gracze[i].zwrocNazwe()<<", zdobyl "<< this->gracze[i].ile_zdobyto_punktow()<<"!\n";
        }
    }
    // sprawdzenie wyników botów
    for(int i=0;i<this->graczewirtualni.size();++i){
        if(this->graczewirtualni[i].ile_zdobyto_punktow() == najwiecej){
            cout<<"Wygrywa "<<graczewirtualni[i].zwrocNazwe()<<", zdobyl "<< this->graczewirtualni[i].ile_zdobyto_punktow()<<"!\n";
        }
    }
    


    cout<<"Wyniki:\n";
    for(int i=0;i<this->gracze.size();++i){
        
        cout<<gracze[i].zwrocNazwe()<<" "<< this->gracze[i].ile_zdobyto_punktow()<<" punktow, "; this->gracze[i].pokazKarty(); cout<<"\n";
    }
    // przedstawienie wyników botów
    for(int i=0;i<this->graczewirtualni.size();++i){
        
        cout<<graczewirtualni[i].zwrocNazwe()<<" "<< this->graczewirtualni[i].ile_zdobyto_punktow()<<" punktow, "; this->graczewirtualni[i].pokazKarty(); cout<<"\n";
    }
    
    
    system("pause");
    system("CLS");
    cout<<"Czy chcesz zagrac jeszcze raz?...\n";
    cout<<"Wcisnij 1 by rozpoczac nows gre\n";
    cout<<"Wcisnij 2 by wyjsc\n";

    // Element obsługujący rozpoczęcie nowej gry
    
    while(1){
        // Dodano kontrole strumienia
        cin>>input;
        if (cin.fail()){
            cout<<" blad, podaj jeszcze raz\n";
            cin.clear();
            cin.ignore(256, '\n');
        }
        else break;
    }
    
    if(input == "1"){
        this->savetoFile();
        
        this->gracze.clear();
        this->graczewirtualni.clear();
        this->ktora_karta = 52;
        this->koniec = false;
        this->koniecBot = false;
        this->talia_const.clear();
        system("CLS");
        this->graj();
    }
    else this->savetoFile();
    
}

void Kasyno::savetoFile(){

    // Metoda zapisująca do pliku
    fstream file;
    
    file.open("Zapis.txt", ios::app);
    
    // zapisywanie wyników gry do pliku

     for(int i=0;i<this->gracze.size();++i){
        
        file<< gracze[i].zwrocNazwe() << setw(20) <<gracze[i].zwrocReke() << setw(20) << gracze[i].ile_zdobyto_punktow() <<"\n";
        
    }
    for(int i=0;i<this->graczewirtualni.size();++i){
        
        file<< graczewirtualni[i].zwrocNazwe() << setw(20) <<graczewirtualni[i].zwrocReke() << setw(20) << graczewirtualni[i].ile_zdobyto_punktow() <<"\n";
        
    }
    file<<"----------------------------------------------------------------------------------------------------------------------------------------------";
    file.close();

}