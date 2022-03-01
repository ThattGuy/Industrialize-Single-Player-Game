//
// POO 2021-2022
// Tiago Garcia Quintas 2019128044
//Bruno Paulo 2018017477
//

#include "Comandos.h"

Comandos::Comandos(Jogo *jogo) : jogo(jogo) {
    comandos.emplace_back("exec");
    comandos.emplace_back("cons");
    comandos.emplace_back("liga");
    comandos.emplace_back("des");
    comandos.emplace_back("move");
    comandos.emplace_back("vende");
    comandos.emplace_back("cont");
    comandos.emplace_back("list");
    comandos.emplace_back("next");
    comandos.emplace_back("save");
    comandos.emplace_back("load");
    comandos.emplace_back("apaga");
    comandos.emplace_back("config");
    comandos.emplace_back("debcash");
    comandos.emplace_back("debed");
    comandos.emplace_back("debkill");
    comandos.emplace_back("upgrade");
}

bool Comandos::verifica_comandos(const string& input) {

    string cmd;
    istringstream s(input);
    s >> cmd;

    for(const std::string &comando : comandos) {
        if(cmd == comando) {
            return true;
        }
    }

    return false;
}

void Comandos::executa_comando(const string &input, Ilha **ilha) {

    string cmd;
    int pos;
    istringstream s(input);
    s >> cmd;

    for (pos = 0; pos < comandos.size(); ++pos) {
        if (cmd == comandos[pos])
            break;
    }

    switch (pos) {
        case 0:
            exec(input, ilha);
            break;

        case 1:
            cons(input, **ilha);
            break;

        case 2:
            muda_estado(input, **ilha, true);
            break;

        case 3:
            muda_estado(input, **ilha, false);
            break;

        case 4:
            move(input, **ilha);
            break;

        case 5:
            vende(input, **ilha);
            break;

        case 6:
            cont(input, **ilha);
            break;

        case 7:
            list(input, **ilha);
            break;

        case 8:
            next(**ilha);
            break;

        case 9:
            save(input, **ilha);
            break;

        case 10:
            load(input, ilha);
            break;

        case 11:
            apaga(input);
            break;

        case 12:
            config(input);
            break;

        case 13:
            debcash(input);
            break;

        case 14:
            debed(input, **ilha);
            break;

        case 15:
            debkill(input, **ilha);
            break;

        case 16:
            upgrade(input, **ilha);
            break;
        default:
            cout << "[ERRO]: Comando Invalido" << endl;
            break;
    }
}

int Comandos::verifica_comando_edf(const string &edf) {
    for (int i = 0; i < comandos_edfc.size(); ++i) {
        if (edf == comandos_edfc[i])
            return i;
    }
    return -1;
}


int Comandos::verifica_comando_trab(const string &trab) {
    for (int i = 0; i < comandos_trab.size(); ++i) {
        if (trab == comandos_trab[i])
            return i;
    }
    return -1;

}


void Comandos::exec(const string &inp, Ilha **ilha) {
    string nome;
    stringstream ss(inp);
    int i = 0;
    while (ss >> nome) {
        ++i;
    }
    if (i > 2 || i == 1) {
        cout << "Comando errado! Exemplo: exec cmd.txt\n";
    } else {
        fstream ficheiro;
        ficheiro.open(nome, ios::in); // read
        if (ficheiro.is_open()) {
            string input;
            while (getline(ficheiro, input)) {
                executa_comando(input, ilha);
            }
            ficheiro.close();
        } else {
            cout << "Ficheiro nao existe!\n";
        }
    }
}


void Comandos::config(const string &inp) {
    string nome;
    stringstream ss(inp);
    int i = 0, pos, pos2;
    while (ss >> nome) {
        ++i;
    }
    if (i > 2 || i == 1) {
        cout << "Comando errado! Exemplo: exec conf.txt\n";
    } else {
        fstream ficheiro;
        ficheiro.open(nome, ios::in); // read
        if (ficheiro.is_open()) {
            string input;
            while (getline(ficheiro, input)) {
                istringstream fss(input);
                string cmd;
                int valor = 0;
                fss >> cmd;
                fss >> valor;
                pos = verifica_comando_trab(cmd);
                pos2 = verifica_comando_edf(cmd);
                if (pos != -1) {
                    (jogo)->muda_configuracaoTB(pos, valor);
                }
                if (pos2 != -1) {
                    (jogo)->muda_configuracaoED(pos2, valor);
                }
                if (pos == -1 && pos2 == -1) {
                    cout << "Comando errado! Ficheiro contem comando errado!\n";
                    break;
                }
            }
            ficheiro.close();
        } else {
            cout << "Ficheiro nao existe!\n";
        }
    }
}

void Comandos::cons(string input, Ilha &ilha) {

    stringstream cmd(input);
    string tipo_edf;
    int edf;
    int linha = 0, coluna = 0;


    //verifica linha, coluna e argumentos
    if (cmd >> input >> tipo_edf >> linha >> coluna) {
        if (!ilha.verifica_lin_col(linha, coluna)) {
            cout << "[ERRO]: Coordenada nao e valida! Insira outro valor" << endl;
            return;
        }
    } else {
        cout << "Argumentos insufucientes!" << endl;
        return;
    }

    //verifica se tipo de edificio existe
    edf = verifica_comando_edf(tipo_edf);
    if (edf == -1) {
        cout << "[ERRO]: Edificio nao e existe!" << endl;
        return;
    }
    //verifica se zona tem edificio
    if (ilha.chama_verifica_ocp_edf(linha - 1, coluna - 1)) {
        cout << "[ERRO]: Zona ja tem edificio!" << endl;
        return;
    } else {
        int posEdf = this->verifica_comando_edf(tipo_edf);
        auto precoEdf = static_cast<float>(jogo->getCustoEdif(posEdf));
        float dinheiroDisponivel = jogo->get_dinheiro();
        float quantidadeVigas = jogo->chama_get_recurso("vigas");

        // mina ferro e mina carvao
        if(tipo_edf == "minaf" || tipo_edf == "minac") {

            float vigasNecessarias = static_cast<float>(precoEdf) / 10;
            if(quantidadeVigas < vigasNecessarias) {
                float dinheiroAPagar = (vigasNecessarias - quantidadeVigas) * 10;
                if(dinheiroAPagar > dinheiroDisponivel) {
                    cout << "[ERRO]: Nao tem dinheiro nem recursos suficientes!" << endl;
                    return;
                }
                jogo->chama_remove_recurso("vigas", quantidadeVigas);
                jogo->set_dinheiro(-dinheiroAPagar);
            } else {
                jogo->chama_remove_recurso("vigas", vigasNecessarias);
            }
        }

        // central e fundicao e serracao
        if(tipo_edf == "central" || tipo_edf == "fund" || tipo_edf == "ser") {
            if(precoEdf > dinheiroDisponivel) {
                cout << "[ERRO]: Nao tem dinheiro nem recursos suficientes!" << endl;
                return;
            }
            jogo->set_dinheiro(-precoEdf);
        }

        //bateria
        if(tipo_edf == "bat") {
            if(precoEdf > dinheiroDisponivel || precoEdf > quantidadeVigas) {
                cout << "[ERRO]: Nao tem dinheiro nem recursos suficientes!" << endl;
                return;
            }

            jogo->set_dinheiro(-precoEdf);
            jogo->chama_remove_recurso("vigas", precoEdf);
        }

        ilha.chama_adc_edf(linha - 1, coluna - 1, edf);
    }
}


void Comandos::muda_estado(string input, Ilha &ilha, bool estado) {
    stringstream cmd(input);
    int linha, coluna;

    //verifica linha, coluna e argumentos
    if (cmd >> input >> linha >> coluna) {
        if (!ilha.verifica_lin_col(linha, coluna)) {
            cout << "[ERRO]: Coordenada nao e valida! Insira outro valor" << endl;
            return;
        }
        //verifica se zona tem edificio
        if (ilha.chama_verifica_ocp_edf(linha - 1, coluna - 1)) {
            ilha.chama_muda_estado_edf(linha - 1, coluna - 1, estado);
        } else {
            cout << "[ERRO]: Zona nao tem edificio!" << endl;
        }

    } else {
        cout << "Argumentos insufucientes!" << endl;
        return;
    }

}


void Comandos::move(string input, Ilha &ilha) {

    stringstream cmd(input);
    string trab_id;
    int lin, col;

    //verifica linha, coluna e argumentos
    if (cmd >> input >> trab_id >> lin >> col) {
        //verifica se id trabalhador existe
        if (!ilha.move_trabalhador(trab_id, lin - 1, col - 1)) {
            cout << "ID nao e valido|" << endl;
        }
    } else {
        cout << "Argumentos insufucientes!" << endl;
    }

}


void Comandos::cont(string input, Ilha &ilha) {

    stringstream cmd(input);
    int trab;
    string tipo_trab;

    //verifica linha, coluna e argumentos
    if (cmd >> input >> tipo_trab) {
        //verifica se tipo de trabalhador existe
        trab = verifica_comando_trab(tipo_trab);
        if (trab == -1) {
            cout << "[ERRO]: Trabalhador nao existe!" << endl;
            return;
        }
        if ((jogo)->remove_custo_trab(trab)) {
            if ((jogo)->verifica_dinheiro("trab", trab)) {
                ilha.chama_adc_trab(trab);
                ilha.add_num_trab_cont();
                return;
            }
        } else {
            cout << "[ERRO]: Dinheiro insuficiente!" << endl;
            return;
        }

    } else {
        cout << "Argumentos insufucientes!" << endl;
    }
}

void Comandos::list(string input, Ilha &ilha) {

    int linha, coluna;
    stringstream cmd(input);

    if (cmd >> input >> linha >> coluna) {
        if (!ilha.verifica_lin_col(linha, coluna)) {
            cout << "[ERRO]: Coordenada nao e valida! Insira outro valor" << endl;
            return;
        }
        ilha.chama_lista_zona(linha - 1, coluna - 1);
    } else {
        cout << "Jogador tem " << jogo->get_dinheiro() << " de dinheiro" << endl;
        for(const string& recurso : (*jogo->get_recursos(0, 0))->get_tipo_recursos()) {
            cout << "Jogador tem " << jogo->chama_get_recurso(recurso) << " unidades do recurso " << recurso << endl;
        }
        ilha.list_ilha();
    }

}

void Comandos::next(Ilha &ilha) {

    ilha.anoitecer();

    ilha.muda_dia();

    ilha.amanhecer();

}

void Comandos::save(string input, Ilha &ilha) {
    std::stringstream cmd(input);
    std::string saveName;

    if (cmd >> input >> saveName) {
        int index = -1;
        for (int i = 0; i < saves.size(); i++) {
            if (saves[i]->get_nome() == saveName) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            std::cout << "[ERRO]: Ja existe um save com esse nome!" << std::endl;
            return;
        }
        Save *save = new Save(ilha, *jogo, saveName);
        saves.emplace_back(save);
    } else {
        std::cout << "[ERRO]: Argumentos Insuficientes!" << std::endl;
    }
}

void Comandos::load(string input, Ilha **ilha) {
    std::stringstream cmd(input);
    std::string saveName;

    if (cmd >> input >> saveName) {
        for (Save *save: saves) {
            if (save->get_nome() == saveName) {
                this->jogo = new Jogo(*save->get_jogo());
                *ilha = new Ilha(*save->get_ilha());
                return;
            }
        }
        std::cout << "[ERRO]: Nao existe nenhum save com esse nome!" << std::endl;
    } else {
        std::cout << "[ERRO]: Argumentos Insuficientes!" << std::endl;
    }


}

void Comandos::apaga(string input) {

    std::stringstream cmd(input);
    std::string saveName;

    if (cmd >> input >> saveName) {
        int index = -1;
        for (int i = 0; i < saves.size(); i++) {
            if (saves[i]->get_nome() == saveName) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            std::cout << "[ERRO]: Nao existe nenhum save com esse nome!" << std::endl;
            return;
        }
        saves.erase(saves.begin() + index - 1);
    } else {
        std::cout << "[ERRO]: Argumentos Insuficientes!" << std::endl;
    }

}


void Comandos::debcash(string input) {

    stringstream cmd(input);
    float quantidade;

    if (cmd >> input >> quantidade) {

        jogo->set_dinheiro(quantidade);

    } else {
        cout << "Argumentos insufucientes!" << endl;
    }

}

void Comandos::debed(string input, Ilha &ilha) {

    stringstream cmd(input);
    string tipo_edf;
    int edf;
    int linha = 0, coluna = 0;


    //verifica linha, coluna e argumentos
    if (cmd >> input >> tipo_edf >> linha >> coluna) {
        if (!ilha.verifica_lin_col(linha, coluna)) {
            cout << "[ERRO]: Coordenada nao e valida! Insira outro valor" << endl;
            return;
        }
    } else {
        cout << "Argumentos insufucientes!" << endl;
        return;
    }

    //verifica se tipo de edificio existe
    edf = verifica_comando_edf(tipo_edf);
    if (edf == -1) {
        cout << "[ERRO]: Edificio nao e existe!" << endl;
        return;
    }
    //verifica se zona tem edificio
    if (ilha.chama_verifica_ocp_edf(linha - 1, coluna - 1)) {
        cout << "[ERRO]: Zona ja tem edificio!" << endl;
        return;
    } else {
        ilha.chama_adc_edf(linha - 1, coluna - 1, edf);
    }

}

void Comandos::debkill(string input, Ilha &ilha) {
    string id;
    stringstream cmd(input);
    if (cmd >> input >> id) {
        if (ilha.remove_trab(id)) {
            return;
        } else
            cout << "Trabalhador nao existe" << endl;
    } else {
        cout << "Argumentos insufucientes!" << endl;
        return;
    }
}


void Comandos::upgrade(string input, Ilha &ilha) {

    stringstream cmd(input);
    string tipoEdf;
    int linha = 0, coluna = 0;


    //verifica linha, coluna e argumentos
    if (cmd >> input >> tipoEdf >> linha >> coluna) {
        if (!ilha.verifica_lin_col(linha, coluna)) {
            cout << "[ERRO]: Coordenada nao e valida! Insira outro valor" << endl;
            return;
        }
    } else {
        cout << "Argumentos insufucientes!" << endl;
        return;
    }

    //verifica se zona tem edificio
    if (!ilha.chama_verifica_ocp_edf(linha - 1, coluna - 1)) {
        cout << "[ERRO]: Zona nao tem edificio" << endl;
        return;
    } else {
        float dinheiroDisponivel = jogo->get_dinheiro();
        float quantidadeVigas = jogo->chama_get_recurso("vigas");

        // mina ferro
        if(tipoEdf == "mnF") {
            if(dinheiroDisponivel < 15.0f || quantidadeVigas < 1.0f) {
                cout << "[ERRO]: Nao tem dinheiro ou materiais suficientes!" << endl;
                return;
            }
            jogo->set_dinheiro(-15.0f);
            jogo->chama_remove_recurso("vigas", -1.0f);
        }

        // mian carvao
        if(tipoEdf == "mnC") {
            if(dinheiroDisponivel < 10.0f || quantidadeVigas < 1.0f) {
                cout << "[ERRO]: Nao tem dinheiro ou materiais suficientes!" << endl;
                return;
            }
            jogo->set_dinheiro(-10.0f);
            jogo->chama_remove_recurso("vigas", -1.0f);
        }

        //bateria

        if(tipoEdf == "bat") {
            if(ilha.get_nivel_edf(linha -1, coluna - 1) == 5) {
                cout << "[ERRO]: Este edificio ja esta no nivel maximo" << endl;
                return;
            }

            if(dinheiroDisponivel < 5.0f) {
                cout << "[ERRO]: Nao tem dinheiro ou materiais suficientes!" << endl;
                return;
            }
            jogo->set_dinheiro(-5.0f);
        }


        ilha.chama_upgrade(linha - 1, coluna - 1);
    }

}

void Comandos::vende(string input, Ilha &ilha) {
    stringstream cmd(input);
    std::string tipoOuLinha;
    int colunaOuQuantidade;

    if(cmd >> input >> tipoOuLinha >> colunaOuQuantidade){
        if(isNumber(tipoOuLinha)) {
            // vender edf
            istringstream iss(tipoOuLinha);
            int linha;
            iss >> linha;
            if (!ilha.verifica_lin_col(linha, colunaOuQuantidade)) {
                cout << "[ERRO]: Coordenada nao e valida! Insira outro valor" << endl;
                return;
            }
            if (!ilha.chama_verifica_ocp_edf(linha - 1, colunaOuQuantidade - 1)) {
                cout << "[ERRO]: Zona nao tem edificio" << endl;
                return;
            } else {
                string tipoEdf = ilha.get_edf(linha -1, colunaOuQuantidade -1);
                int posEdf = verifica_posicao_edf(tipoEdf);
                ilha.chama_remove_edf(linha - 1, colunaOuQuantidade - 1);
                Recursos *recursos = *jogo->get_recursos(linha - 1, colunaOuQuantidade - 1);

                float dinheiro = 0.0f;
                // vende tudo;
                dinheiro += static_cast<float>(jogo->getCustoEdif(posEdf));
                dinheiro += jogo->chama_vender_recurso("ferro", recursos->get_ferro());
                dinheiro += jogo->chama_vender_recurso("carvao", recursos->get_carvao());
                dinheiro += jogo->chama_vender_recurso("aco", recursos->get_aco());
                dinheiro += jogo->chama_vender_recurso("vigas", recursos->get_vigas());
                dinheiro += jogo->chama_vender_recurso("electricidade", recursos->get_eletricidade());
                jogo->set_dinheiro(dinheiro);
                return;
            }
        } else {
            // vender recursos


           if(!(*jogo->get_recursos(0, 0))->verifica_tipo_recursos(tipoOuLinha)) {
               cout << "[ERRO]: Um recurso com esse nome nao existe" << endl;
           }

           float quantidadeAtual = jogo->chama_get_recurso(tipoOuLinha);

           if(static_cast<float>(quantidadeAtual) > quantidadeAtual) {
               cout << "[ERRO]: Nao tem recursos suficentes para vender" << endl;
               return;
           }

           float dinheiro = jogo->chama_vender_recurso(tipoOuLinha, static_cast<float>(colunaOuQuantidade));
           jogo->set_dinheiro(dinheiro);
            return;
        }
    } else {
        cout << "[ERRO]: Argumentos Insuficientes!" << endl;
        return;
    }


}

int Comandos::verifica_posicao_edf(const string &edf) {
    for (int i = 0; i < tipos_edf.size(); i++) {
        if(tipos_edf[i] == edf) {
            return i;
        }
    }

    return -1;
}


