//
// POO 2021-2022
// Tiago Garcia Quintas 2019128044
//Bruno Paulo 2018017477
//

#include "Save.h"
Save::Save(Ilha &ilha,Jogo &jogo, std::string& nome) {
    Jogo* jogoAGuardar = new Jogo(jogo);
    Ilha* ilhaAGuardar = new Ilha(ilha, jogo.get_vector_recursos());
    this->ilha = ilhaAGuardar;
    this->jogo = jogoAGuardar;
    this->nome = nome;
}

Save::~Save() {
    delete this->jogo;
    delete this->ilha;
}

std::string Save::get_nome() const{
    return this->nome;
}

Ilha* Save::get_ilha() const{
    return this->ilha;
}

Jogo* Save::get_jogo() const{
    return this->jogo;
}
