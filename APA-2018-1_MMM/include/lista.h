#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include "no.h"
#include "aresta.h"
#include "listaAresta.h"
#include <string>

using namespace std;

/**
 * lista.h - Definicao da estrutura que representa um grafo por lista de adjacencia.
 *
 * Gisele Goulart  - 201365089C
 * Guilherme Felix - 201365504B
 *
 * Universidade Federal de Juiz de Fora
 * Departamento de Ciencia da Computacao
 * DCC001 - Analise e projetos de Algoritmos
 */

class lista {

public:
    lista();
    ~lista();
    void setRaiz(no* x);
    no* getRaiz();
    void setUltimo(no* x);
    no* getUltimo();
    void setAdjacente(no* x);
    no* getAdjacente();
    int getQuantNo();
    void setQuantNo(int i);
    void incluirNo(no* novo);
    void excluirNo(int valor);
    void incluirAresta(no* x, no* y, float p);
    void excluirAresta(no*x, no*y, float p);
    bool existeAresta(no* x, no* y);
    no* existeNo(int valor);
    void inserir(string arq);
    aresta* ordenaArestas(int* perm);
    aresta* getArestaRaiz();
    int searchArr(int a[], int n, int mobile);
    int getMobile(int a[], bool dir[], int n);
    int* onePerm(int *a, bool dir[], int n);
    int fact(int n);
    aresta* matching(int *perm, listaAresta* solucao, listaAresta* candidatas);
    void MMMForcaBruta();
    void geraSAT(int k);
    void atMostOne(listaAresta* novosIdsArestas, int &clausuras, stringstream& buffer);
    void atLeastOneAdap(listaAresta* novosIdsArestas, int& clausuras, stringstream& buffer);
    int getQtdArestas();




private:
        no *raiz;
        no *ultimo;
        int quantidadeNo;
};


#endif // LISTA_H_INCLUDED

