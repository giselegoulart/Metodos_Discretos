#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

/**
 * No.h - Definicao da estrutura que representa o vertice de um grafo
 *
 * Gisele Goulart  - 201365089C
 * Guilherme Felix - 201365504B
 *
 * Universidade Federal de Juiz de Fora
 * Departamento de Ciencia da Computacao
 * DCC001 - Analise e projetos de Algoritmos
 */

/* Classe que representa o No do grafo */

using namespace std;

class no {

public:
    no(int i, int valor);
    ~no();
    void setValor(int valor);
    void setIndex(int i);
    void setGrau(int g);
    void setIrmao(no* x);
    void setAdjacente(no* x);
    int getValor();
    int getIndex();
    int getGrau();
    no* getIrmao();
    no* getAdjacente();
    void setSomatorioGrau(int g);
    int getSomatorioGrau();
    void setQuantAdjacente(int g);
    int getQuantAdjacente();


private:
    int valorNo;
    int index;
    int grau;
    int somatorioGrau;      //guarda o somatorio dos graus dos nos adjacentes ao no em questao
    int quantAdjacentes;    //guarda a quantidade de nos adjacentes ao no em questao
    no *irmao;
    no *adjacente;

};

#endif // NO_H_INCLUDED

