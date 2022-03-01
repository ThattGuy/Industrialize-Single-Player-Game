//
// POO 2021-2022
// Tiago Garcia Quintas 2019128044
//Bruno Paulo 2018017477
//
#ifndef TRABALHO_POO_META_2_COMANDOS_H
#define TRABALHO_POO_META_2_COMANDOS_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Ilha.h"
#include "Jogo.h"
#include "Save.h"
using namespace std;

class Comandos {
    const vector<string> comandos_edfc{"minaf", "minac", "central", "bat", "fund", "ser"};
    const vector<string> tipos_edf{"mnF", "mnC", "elec", "bat", "fun", "edX"};
    const vector<string> comandos_trab{"oper", "len", "miner"};

    vector<string> comandos;
    vector<Save*> saves;

    Jogo *jogo;

    int verifica_comando_edf(const string &edf);
    int verifica_comando_trab(const string &trab);
    int verifica_posicao_edf(const string &edf);

    void exec(const string &input,Ilha **ilha);
    void config(const string& input);
    void cons(string input,Ilha &ilha);
    static void muda_estado(string input,Ilha &ilha, bool estado);//comando liga/desliga
    static void move(string input,Ilha &ilha);
    void vende(string input,Ilha &ilha);
    void cont(string input, Ilha &ilha);
    void list(string input, Ilha &ilha);
    void next(Ilha &ilha);
    void save(string input, Ilha &ilha);
    void load(string input, Ilha **ilha);
    void apaga(string input);
    void debcash(string input);
    void debed(string input,Ilha &ilha);
    static void debkill(string input, Ilha &ilha);
    void upgrade(string input, Ilha &ilha);

public:
    explicit Comandos(Jogo *jogo);
    bool verifica_comandos(const string &input);
    void executa_comando(const string& input, Ilha **ilha);
};


#endif //TRABALHO_POO_META_2_COMANDOS_H