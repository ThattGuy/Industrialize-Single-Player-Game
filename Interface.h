//
// POO 2021-2022
// Tiago Garcia Quintas 2019128044
//Bruno Paulo 2018017477
//
#ifndef TRABALHO_POO_META_2_INTERFACE_H
#define TRABALHO_POO_META_2_INTERFACE_H
#include "Comandos.h"
#include "Ilha.h"
#include "Jogo.h"

class Interface {
    static int interface_comandos(Ilha **ilha, Comandos &c);
    static void mostra_ilha(Ilha &ilha);
    static int interface_dim(Ilha &Ilha);
    static void mostra_trab(const int &lin, const int &col, Ilha &ilha);

public:
    Interface();
    static int interface_main(Ilha **ilha, Jogo *jogo, Comandos &c);

};

#endif //TRABALHO_POO_META_2_INTERFACE_H
