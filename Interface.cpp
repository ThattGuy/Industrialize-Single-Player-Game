//
// POO 2021-2022
// Tiago Garcia Quintas 2019128044
//Bruno Paulo 2018017477
//
#include "Interface.h"


Interface::Interface() = default;

int Interface::interface_main(Ilha **ilha, Jogo *jogo, Comandos &c) {

    Interface::interface_dim(**ilha);

    (*ilha)->preenche_ilha(*(jogo)->get_vector_recursos());

    bool flag;
    do{
        Interface::mostra_ilha(**ilha);
        flag = Interface::interface_comandos(ilha, c);
    } while (!flag);

    return 0;
}

int Interface::interface_dim(Ilha &ilha) {

    bool flag;
    string input;
    int linhas, colunas;

    do {
        cout << "Insira o numero de linhas (um numero entre 3 e 8):" << endl;
        getline(cin,input);
        stringstream s_lin(input);
        s_lin >> linhas;

        flag = Ilha::verifica_dim_lin(linhas);

    } while (!flag);

    flag = false;

    do {
        cout << "Insira o numero de Colunas (um numero entre 3 e 16):" << endl;
        getline(cin,input);
        stringstream s_col(input);
        s_col >> colunas;

        flag = Ilha::verifica_dim_col(colunas);

    } while (!flag);

    ilha.set_dimensao(linhas,colunas);

    return 0;
}


int Interface::interface_comandos(Ilha **ilha, Comandos &c) {

    bool flag;

    do {
        string input;

        cout << "Insira o comando:" << endl;
        getline(cin,input);

        flag = c.verifica_comandos(input);

        if (!flag) cout << "[ERRO]: Comando Invalido! " << endl;

        if (flag) c.executa_comando(input, ilha);

    } while (!flag);
    return 0;
}

void Interface::mostra_ilha(Ilha &ilha) {

    int lin = ilha.get_linhas();
    int col = ilha.get_colunas();


    cout << endl;
    for (int i = 0; i < lin; ++i)
    {
        for (int j = 0; j < col; ++j) //divisor de linha
        {
            cout << "+-----";
            if (j == col - 1)
                cout << "+";
        }
        cout << endl;

        for (int p = 0; p <= 3; ++p)
        { //conteudo das zonas
            for (int k = 0; k < col; ++k)
            {
                switch (p)
                {
                    case 0:
                        cout << "|" << ilha.get_tipo_zona(i,k) << "  ";
                        break;

                    case 1:
                        if (ilha.get_edf(i, k) == "elec")
                            cout << "|" << ilha.get_edf(i, k)  << " ";
                        else
                            cout << "|" << ilha.get_edf(i, k)  << "  ";
                        break;

                    case 2:
                        Interface::mostra_trab(i, k, ilha);
                        break;

                    case 3:
                        if (ilha.get_num_trab(i, k) != 0)
                        {
                            cout << "|" << ilha.get_num_trab(i, k) << "    ";
                        }
                        else
                            cout << "|     ";

                        break;
                    default:
                        break;
                }
                if (k == col - 1)
                    cout << "|";
            }
            cout << endl;
        }

        if (i == lin - 1)
        { //divisor de linha Final
            for (int j = 0; j < col; ++j)
            {
                cout << "+-----";
                if (j == col - 1)
                    cout << "*";
            }
        }
    }
    cout << endl;
}

void Interface::mostra_trab(const int &lin, const int &col, Ilha &ilha) {

    int tam = ilha.get_num_trab(lin, col);
    int pos = (tam - 1);
    if (tam > 0)
    {
        cout << "|";
        switch (tam)
        {
            case 1:
                cout << ilha.get_tipo_trab(lin, col, pos).at(0) << "    ";
                break;
            case 2:
                for (int i = 0; i < 2; ++i)
                {
                    cout << ilha.get_tipo_trab(lin, col, pos).at(0);
                    pos--;
                }
                cout << "   ";
                break;
            case 3:
                for (int i = 0; i < 3; ++i)
                {
                    cout << ilha.get_tipo_trab(lin, col, pos).at(0);
                    pos--;
                }
                cout << "  ";
                break;
            case 4:
                for (int i = 0; i < 4; ++i)
                {
                    cout << ilha.get_tipo_trab(lin, col, pos).at(0);
                    pos--;
                }
                cout << " ";
                break;
            default:
                for (int i = 0; i < 4; ++i)
                {
                    cout << ilha.get_tipo_trab(lin, col, pos).at(0);
                    pos--;
                }
                cout << " ";
                break;
        }
    }
    else
        cout << "|     ";

}


