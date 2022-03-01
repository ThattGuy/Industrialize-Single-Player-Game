//
// POO 2021-2022
// Tiago Garcia Quintas 2019128044
//Bruno Paulo 2018017477
//
#include "Ilha.h"


Ilha::~Ilha() {

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            delete zonas[i][j];
        }
    }

    delete zonas;

}

Ilha::Ilha(Ilha &old_ilha, vector<vector<Recursos *>> *recursos) {
    this->dia = old_ilha.get_dia();
    this->num_trab_cont = old_ilha.get_num_trab_cont();
    this->linhas = old_ilha.get_linhas();
    this->colunas = old_ilha.get_colunas();
    this->zonas = nullptr;

    this->set_dimensao(linhas, colunas);

    //copiar zonas
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            Zona *zona = old_ilha.get_zona(i, j);
            std::string tipoZona = zona->get_tipo();
            Recursos *recurso = (*recursos)[i][j];
            if (tipoZona == "dsr") {
                zonas[i][j] = new Deserto(*dynamic_cast<Deserto *>(zona), *recurso);
            }
            if (tipoZona == "flr") {
                zonas[i][j] = new Floresta(*dynamic_cast<Floresta *>(zona), *recurso);
            }
            if (tipoZona == "mnt") {
                zonas[i][j] = new Montanha(*dynamic_cast<Montanha *>(zona), *recurso);
            }
            if (tipoZona == "pnt") {
                zonas[i][j] = new Pantano(*dynamic_cast<Pantano *>(zona), *recurso);
            }
            if (tipoZona == "pas") {
                zonas[i][j] = new Pastagem(*dynamic_cast<Pastagem *>(zona), *recurso);
            }
            if (tipoZona == "znX") {
                zonas[i][j] = new Zona_x(*dynamic_cast<Zona_x *>(zona), *recurso);
            }
        }
    }
}

int Ilha::get_linhas() const{
    return linhas;
}

int Ilha::get_colunas() const {
    return colunas;
}

Zona *Ilha::get_zona(const int &lin, const int &col) const {
    return zonas[lin][col];
}


bool Ilha::verifica_dim_lin(const int &input_lin){

    if (input_lin < MIN_LIN || input_lin > MAX_LIN) {
        return false;
    }
    return true;
}


bool Ilha::verifica_dim_col(const int &input_col){

    if (input_col < MIN_COL || input_col > MAX_COL) {
        return false;
    }
    return true;
}


void Ilha::set_dimensao(const int &lins, const int &cols) {

    this->linhas = lins;
    this->colunas = cols;

    zonas = new Zona **[linhas * colunas];
    for (int i = 0; i < linhas; ++i)
        zonas[i] = new Zona *[colunas];

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            zonas[i][j] = new Zona;
        }
    }
}

bool Ilha::verifica_ocupacao_zona(const int &lin, const int &col) {

    if (zonas[lin][col]->get_tipo() == "zona") {
        return true;
    } else return false;

}

void Ilha::adiciona_zona(int lin_rand, int col_rand, int i, Recursos &recursos) {
    switch (i) {

        case 0:
            zonas[lin_rand][col_rand] = new Deserto(recursos);

            break;

        case 1:
            zonas[lin_rand][col_rand] = new Floresta(recursos);

            break;

        case 2:
            zonas[lin_rand][col_rand] = new Montanha(recursos);

            break;

        case 3:
            zonas[lin_rand][col_rand] = new Pantano(recursos);

            break;

        case 4:
            zonas[lin_rand][col_rand] = new Pastagem(recursos);

            break;

        case 5:
            zonas[lin_rand][col_rand] = new Zona_x(recursos);

            break;
        default:
            break;
    }
}


void Ilha::preenche_ilha(vector<vector<Recursos *>> &recursos) {

    for (int i = 0; i < linhas; ++i) {
        vector<Recursos *> recursos_lin;
        for (int j = 0; j < colunas; ++j) {
            auto* recursos1 = new Recursos;
            recursos_lin.push_back(recursos1);
        }
        recursos.push_back(recursos_lin);
    }

    for (int i = 0; i < 6; ++i) {
        int lin_rand, col_rand;
        bool flag;

        do {
            lin_rand = random(0, linhas - 1);
            col_rand = random(0, colunas - 1);

            flag = verifica_ocupacao_zona(lin_rand, col_rand);
        } while (!flag);

        delete zonas[lin_rand][col_rand];

        adiciona_zona(lin_rand, col_rand, i, *recursos[lin_rand][col_rand]);


    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (verifica_ocupacao_zona(i, j)) {
                delete zonas[i][j];
                adiciona_zona(i, j, random(0, 5), *recursos[i][j]);
            }
        }
    }

}


string Ilha::get_tipo_zona(const int &lin, const int &col) const {
    return zonas[lin][col]->get_tipo();
}

bool Ilha::verifica_lin_col(const int &lin, const int &col) const {

    if (lin > 0 && lin <= linhas) {
        if (col > 0 && col <= colunas)
            return true;
    }
    return false;
}

bool Ilha::chama_verifica_ocp_edf(const int &lin, const int &col) {

    if (zonas[lin][col]->get_ocup_edf()) {
        return true;
    }
    return false;
}

void Ilha::chama_adc_edf(const int &lin, const int &col, const int &tipo) {

    zonas[lin][col]->adiciona_edf(tipo, dia);

}

void Ilha::chama_adc_trab(const int &tipo) {

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (zonas[i][j]->get_tipo() == "pas") {
                zonas[i][j]->adiciona_trab(tipo, num_trab_cont, dia);
                return;
            }
        }
    }
}

void Ilha::chama_muda_estado_edf(const int &lin, const int &col, const bool &estado) {

    zonas[lin][col]->muda_estado_edf(estado);

}

string Ilha::get_edf(const int &lin, const int &col) const {

    if (zonas[lin][col]->get_ocup_edf()) {
        return zonas[lin][col]->get_tipo_edf();
    }

    return "   ";

}

int Ilha::get_num_trab(const int &lin, const int &col) const {
    return zonas[lin][col]->get_num_trab();
}

string Ilha::get_tipo_trab(const int &lin, const int &col, const int &pos) const {
    return zonas[lin][col]->get_tipo_trab(pos);
}

void Ilha::chama_lista_zona(const int &lin, const int &col) {

    zonas[lin][col]->lista_zona();

}

void Ilha::muda_dia() {

    dia++;

}

int Ilha::get_dia() const {

    return dia;

}

void Ilha::add_num_trab_cont() {
    num_trab_cont++;
}

int Ilha::get_num_trab_cont() const {
    return num_trab_cont;
}

bool Ilha::move_trabalhador(string &id, const int &lin, const int &col) {

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (zonas[i][j]->get_num_trab() > 0) {
                if (zonas[i][j]->verifica_trab_id(id)) {
                    Trabalhador *trabalhador = zonas[i][j]->copia_trab(id);
                    zonas[lin][col]->move_trab(trabalhador);
                    zonas[i][j]->remove_trab(id);
                    return true;
                }
            }
        }
    }
    return false;
}

vector<Zona *> Ilha::devolve_adj(const int &lin, const int &col) {


    vector<Zona*> zonas_adj = vector<Zona*>();

    for (int i = 0; i < 4; i++) {
        int colAPesquisar = lin;
        int linAPesquisar = col;
        switch (i) {
            case 0:
                colAPesquisar -= 1;
                break;
            case 2:
                linAPesquisar -= 1;
                break;
            case 3:
                colAPesquisar += 1;
                break;
            case 4:
                linAPesquisar += 1;
                break;
            default:
                break;
        }

        if ((colAPesquisar < 0 || colAPesquisar > this->colunas - 1) ||
            (linAPesquisar < 0 || linAPesquisar > this->linhas - 1)) {
            //posicao invalida
            continue;
        }

        zonas_adj.push_back(zonas[linAPesquisar][colAPesquisar]);
    }

    return zonas_adj;
}

void Ilha::chama_upgrade(const int &lin, const int &col) {

    zonas[lin][col]->upgrade();

}

void Ilha::ilha_manda_prod(const int& lin, const int& col) {

    vector <Zona*> zonas_adj = this->devolve_adj(lin, col);

    if (zonas[lin][col]->get_ocup_edf()) {
        zonas[lin][col]->manda_produzir(zonas_adj);
    }

}

bool Ilha::remove_trab(const string& id) {

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (zonas[i][j]->get_num_trab() > 0) {
                if (zonas[i][j]->verifica_trab_id(id)) {
                    zonas[i][j]->remove_trab(id);
                    return true;
                }
            }
        }
    }

    return false;
}

void Ilha::amanhecer() {

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {

            zonas[i][j]->efeito_zona(dia);

            zonas[i][j]->desaba_edf();

            zonas[i][j]->chama_despede(dia);

        }
    }
}

void Ilha::anoitecer() {

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            ilha_manda_prod(i,j);
        }
    }

}

void Ilha::chama_remove_edf(const int &lin, const int &col) {
    zonas[lin][col]->destroi_edf();
}

int Ilha::get_nivel_edf(const int &lin, const int &col) const {
    return zonas[lin][col]->get_nivel_edf();
}

void Ilha::list_ilha() {
    int n_edf = 0;
    int n_edfs_ligados = 0;
    for (int i = 0; i < linhas; ++i)
    {
        for (int j = 0; j < colunas; ++j)
        {
            if (zonas[i][j]->get_ocup_edf()) {
                n_edf++;
                if(zonas[i][j]->get_estado_edf()){
                    n_edfs_ligados++;
                }
            }

        }
    }

    cout << "\nNumero de zonas na ilha " << linhas * colunas << endl;

    for (int i = 0; i < tipo_zonas_abbrev.size(); i++)
    {
        const string &tipoZonaAbbrev =tipo_zonas_abbrev[i];
        int cont = 0;
        for (int j = 0; j < linhas; ++j)
        {
            for (int k = 0; k < colunas; ++k)
            {
                if (tipoZonaAbbrev == zonas[j][k]->get_tipo())
                    cont++;
            }
        }
        cout << cont << " zonas do tipo " << tipo_zonas[i] << "." << endl;
    }

    cout << "Numero de edf na ilha " << n_edf << endl;
    for (int i = 0; i < tipo_edfs_abbrev.size(); i++)
    {
        const string &tipoEdfabbrev =tipo_edfs_abbrev[i];
        int cont = 0;
        for (int j = 0; j < linhas; ++j)
        {
            for (int k = 0; k < colunas; ++k)
            {
                if (tipoEdfabbrev == zonas[j][k]->get_tipo_edf())
                    cont++;
            }
        }
        cout << cont << " edfs do tipo " << tipo_edfs[i] << "." << endl;
    }

    cout << "Numero de edf ligados na ilha " << n_edfs_ligados << endl;
    cout << "Numero de trabalhadores na ilha " << num_trab_cont << endl;

}
