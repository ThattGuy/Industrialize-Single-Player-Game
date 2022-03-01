//
// POO 2021-2022
// Tiago Garcia Quintas 2019128044
//Bruno Paulo 2018017477
//
#include "Jogo.h"

bool Jogo::verifica_dinheiro(const string &tipo, const int &pos) {

    if (tipo == "trab"){
        if (dinheiro_jogador >= preco_trab[pos])
            return true;
        else return false;
    }

    if (tipo == "edif"){
        if (dinheiro_jogador >= preco_edif[pos])
            return true;
        else return false;
    }

    return false;
}


float Jogo::get_dinheiro() const {
    return dinheiro_jogador;
}

float Jogo::chama_get_recurso(string recurso) {

    float ferro = 0, aco = 0, carvao = 0, madeira = 0, vigas = 0, eletricidade = 0;

    for (const auto &recursos_lin : recursos_jogador) {
        for (auto & j : recursos_lin) {
            ferro += j->get_ferro();
            aco += j->get_aco();
            carvao += j->get_carvao();
            madeira += j->get_madeira();
            vigas += j->get_vigas();
            eletricidade += j->get_eletricidade();
        }
    }

    if (recurso == "ferro"){
        return ferro;
    }
    if (recurso == "aco"){
        return aco;
    }
    if (recurso == "carvao"){
        return carvao;
    }
    if (recurso == "madeira"){
        return madeira;
    }
    if (recurso == "vigas"){
        return vigas;
    }
    if (recurso == "eletricidade"){
        return eletricidade;
    }

    return 0;
}

float Jogo::chama_vender_recurso(const string &recurso, float quantidade) {
    float dinheiro = 0.0f;
    float quantidadeNecessaria = quantidade;

    for (const auto &recursos_lin : recursos_jogador) {
        for (auto & j : recursos_lin) {
            float quantidadeRec = j->get_recurso(recurso);
            if(quantidadeRec >= quantidadeNecessaria) {
                dinheiro += j->vende_recurso(recurso, quantidadeNecessaria);
                return dinheiro;
            } else {
                dinheiro += j->vende_recurso(recurso, quantidadeRec);
                quantidadeNecessaria -= quantidadeRec;
            }
        }
    }

    return dinheiro;
}

void Jogo::muda_configuracaoTB(int pos, int valor) {
    cout << "Antes: " << preco_trab[pos] << endl; //antes
    preco_trab[pos] = valor;
    cout << "Despois: " << preco_trab[pos] << endl; // depois
}

void Jogo::muda_configuracaoED(int pos, int valor) {
    cout << "Antes: " << preco_edif[pos] << endl; //antes
    preco_edif[pos] = valor;
    cout << "Despois: " << preco_edif[pos] << endl; // depois
}

Recursos **Jogo::get_recursos(int lin,int col) {
    return &recursos_jogador[lin][col];
}

vector<vector <Recursos*>>* Jogo::get_vector_recursos() {
    return &recursos_jogador;
}

Jogo::Jogo(Jogo &old_jogo): Jogo()  {
    this->dinheiro_jogador = old_jogo.dinheiro_jogador;
    this->recursos_jogador = std::vector<vector <Recursos*>>();

    //copiar recursos
    for (const std::vector<Recursos*> &recursosLin : old_jogo.recursos_jogador) {
        std::vector<Recursos*> recursosLinCopia = std::vector<Recursos*>();
        for (Recursos* recursos: recursosLin) {
            auto* copiaRecursos = new Recursos(*recursos);
            recursosLinCopia.emplace_back(copiaRecursos);
        }
        this->recursos_jogador.emplace_back(recursosLinCopia);
    }
}

void Jogo::chama_remove_recurso(const string &recurso, float quantidade) {
    float quantidadeNecessaria = quantidade;

    for (const auto &recursos_lin : recursos_jogador) {
        for (auto & j : recursos_lin) {
            float quantidadeRec = j->get_recurso(recurso);
            if(quantidadeRec >= quantidadeNecessaria) {
                j->remove_recurso(recurso, quantidadeNecessaria);
            } else {
                j->remove_recurso(recurso, quantidadeRec);
            }
        }
    }
}

bool Jogo::remove_custo_trab(const int &trab) {

    if (dinheiro_jogador >= preco_trab[trab]){

        dinheiro_jogador = dinheiro_jogador - preco_trab[trab];
        return true;

    }

    return false;
}

void Jogo::set_dinheiro(const float &quantidade) {

    dinheiro_jogador += quantidade;

}

int Jogo::getCustoEdif(int pos) {
    return preco_edif[pos];
}
