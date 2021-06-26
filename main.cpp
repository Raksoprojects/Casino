#include "kasyno.hpp"

using namespace std;


int main(){
    // Zwykła klasa main, wywoływane jest tylko granie

    srand(time(NULL));
    Kasyno kasyno;
    kasyno.graj();
    

    return 0;
}