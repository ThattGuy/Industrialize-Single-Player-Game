
//
// POO 2021-2022
// Tiago Garcia Quintas 2019128044
//Bruno Paulo 2018017477
//

#include <iostream>
#include "Interface.h"
#include <ctime>



int main() {

    srand((unsigned int)time(nullptr));

    Ilha* ilha = new Ilha;
    Jogo* jogo = new Jogo;
    Comandos c(jogo);
    Interface::interface_main(&ilha, jogo, c);
    ilha->~Ilha();
    delete ilha;
    delete jogo;

    return 0;
}
