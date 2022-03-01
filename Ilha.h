//
// POO 2021-2022
// Tiago Garcia Quintas 2019128044
//Bruno Paulo 2018017477
//
#ifndef TRABALHO_POO_META_2_ILHA_H
#define TRABALHO_POO_META_2_ILHA_H
#include <vector>
#include "utils.h"
#include "Jogo.h"
#include "Zonas/Zona.h"
#include "Zonas/Deserto.h"
#include "Zonas/Floresta.h"
#include "Zonas/Montanha.h"
#include "Zonas/Pantano.h"
#include "Zonas/Pastagem.h"
#include "Zonas/Zona_x.h"

class Ilha {
private:
    const vector<string> tipo_zonas = {"Deserto", "Floresta", "Montanha", "Pantano", "Pastagem", "Praia"};
    const vector<string> tipo_zonas_abbrev = {"dsr", "flr", "mnt", "pnt", "pas", "znX"};

    const vector<string> tipo_edfs = {"Bateria", "Central", "Fundicao", "Mina Carvao", "Mina Ferro", "Serracao"};
    const vector<string> tipo_edfs_abbrev = {"bat", "elec", "fun", "mnF", "mnC", "edX"};

    int dia = 1;
    int num_trab_cont = 1;
    Zona* **zonas = nullptr;
    static int const MIN_LIN = 3, MAX_LIN = 8, MIN_COL = 3, MAX_COL = 16;
    int linhas = -1, colunas = -1;
    bool verifica_ocupacao_zona(const int &lin, const int &col);
    void adiciona_zona(int lin_rand, int col_rand,int i, Recursos &recursos);
    void ilha_manda_prod(const int& lin, const int& col);

public:
    Ilha() = default;
    ~Ilha();
    Ilha(Ilha &old_ilha, vector<vector <Recursos*>>* recursos);
    int get_linhas() const;
    int get_colunas() const;

    static bool verifica_dim_lin(const int &input_lin);
    static bool verifica_dim_col(const int &input_col);
    void set_dimensao(const int &linhas,const int &colunas);
    void preenche_ilha(vector<vector<Recursos*>> &recursos);
    bool verifica_lin_col(const int &lin, const int &col) const;

    void chama_lista_zona(const int &lin, const int &col);
    Zona* get_zona(const int &lin, const int &col) const;
    string get_tipo_zona(const int &lin, const int &col) const;

    int get_dia() const;
    void muda_dia();

    bool chama_verifica_ocp_edf(const int &lin, const int &col);
    void chama_adc_edf(const int &lin,const int &col, const int &tipo);
    void chama_muda_estado_edf(const int &lin,const int &col,const bool &estado);
    void chama_remove_edf(const int &lin,const int &col);
    string get_edf(const int &lin, const int &col) const;
    void chama_upgrade(const int &lin, const int &col);
    vector<Zona *> devolve_adj(const int &lin, const int &col);

    void chama_adc_trab(const int &tipo);
    int get_num_trab(const int &lin, const int &col) const;
    bool move_trabalhador(string &id,const int &lin,const int &col);
    void add_num_trab_cont();
    int get_num_trab_cont() const;
    int get_nivel_edf(const int &lin, const int &col) const;
    string get_tipo_trab(const int &lin, const int &col, const int &pos) const;

    void list_ilha();

    bool remove_trab(const string& id);

    void amanhecer();

    void anoitecer();


};

#endif //TRABALHO_POO_META_2_ILHA_H
