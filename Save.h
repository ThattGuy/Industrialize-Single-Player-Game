//
// POO 2021-2022
// Tiago Garcia Quintas 2019128044
//Bruno Paulo 2018017477
//
#ifndef TRABALHO_POO_META_2_SAVE_H
#define TRABALHO_POO_META_2_SAVE_H

#include "Ilha.h"

class Save {
private:
    Ilha* ilha;
    Jogo* jogo;
    std::string nome;
public:
    Save() = delete;
    ~Save();
    Save(Ilha &ilha, Jogo& jogo,std::string& nome);
    std::string get_nome() const;
    Ilha* get_ilha() const;
    Jogo* get_jogo() const;


};


#endif //TRABALHO_POO_META_2_SAVE_H
