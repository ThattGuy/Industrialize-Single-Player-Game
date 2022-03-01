//
// POO 2021-2022
// Tiago Garcia Quintas 2019128044
//Bruno Paulo 2018017477
//
#ifndef TRABALHO_POO_META_2_JOGO_H
#define TRABALHO_POO_META_2_JOGO_H

#include <iostream>
#include "vector"
#include "Recursos/Recursos.h"

using namespace std;

class Jogo {

    float dinheiro_jogador = 50;
    vector<vector <Recursos*>> recursos_jogador;
    vector<int> preco_trab{15, 20, 10};
    vector<int> preco_edif{100, 100, 15, 10, 10, 20};

public:
    Jogo() = default;
    Jogo(Jogo &old_jogo);
    bool verifica_dinheiro(const string &tipo, const int &pos);
    float get_dinheiro() const;
    void set_dinheiro(const float &quantidade);
    float chama_get_recurso(string recur);
    float chama_vender_recurso(const string& recurso, float quantidade);

    void chama_remove_recurso(const string& recurso, float quantidade);
    void muda_configuracaoTB(int pos, int valor);
    void muda_configuracaoED(int pos, int valor);
    int getCustoEdif(int pos);

    Recursos **get_recursos(int lin, int col);
    vector<vector <Recursos*>>* get_vector_recursos();
    bool remove_custo_trab(const int& trab);
};


#endif //TRABALHO_POO_META_2_JOGO_H
