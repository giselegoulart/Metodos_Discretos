#ifndef LISTAARESTA_H_INCLUDED
#define LISTAARESTA_H_INCLUDED
#include "aresta.h"

using namespace std;

/**
 * listaAresta.h - Definicao da estrutura que representa uma lista de arestas.
 *
 * Gisele Goulart - 201365089C
 * Guilherme Felix - 201365504B
 *
 * Universidade Federal de Juiz de Fora
 * Departamento de Ciencia da Computacao
 * DCC001 - Analise e projetos de Algoritmos
 */


class listaAresta{

public:
    listaAresta();
    ~listaAresta();
    void criarAresta(int rotulo1, int rotulo2, int num_aresta);
    aresta* getArestaRaiz();
    void setArestaRaiz(aresta* raiz);
    aresta* ordenaArestas(int* perm);
    int getQtdArestas();
    void excluiAresta(int id);
    void setQtdArestas(int qtd);

private:
    aresta *arestaRaiz;
    aresta *ultimaAresta;
    int qtdArestas;
};

#endif // LISTAARESTA_H_INCLUDED
