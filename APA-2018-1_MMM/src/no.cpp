#include "no.h"
#include <iostream>

/**
 * No.h - Definicao das operacoes sobre o vertice de um grafo
 *
 * Gisele Goulart  - 201365089C
 * Guilherme Felix - 201365504B
 *
 * Universidade Federal de Juiz de Fora
 * Departamento de Ciencia da Computacao
 * DCC001 - Analise e projetos de Algoritmos
 */

no::no(int i, int valor){
// criando um novo no
    index = i;
    valorNo = valor;
    grau  = 0;
    somatorioGrau = 0;
    quantAdjacentes = 0;
    irmao = NULL;
    adjacente = NULL;
};

no::~no(){}

void no::setValor(int valor){valorNo = valor;}

void no::setIndex(int i){index = i;}

void no::setGrau(int g){grau = g;}

void no::setIrmao(no* x){irmao = x;}

void no::setAdjacente(no* x){adjacente = x;}

int no::getValor(){return valorNo;}

int no::getIndex(){return index;}

int no::getGrau(){return grau;}

no* no::getIrmao(){return irmao;}

no* no::getAdjacente(){return adjacente;}

void no::setSomatorioGrau(int g){somatorioGrau = g;}

int no::getSomatorioGrau(){return somatorioGrau;}

void no::setQuantAdjacente(int g){quantAdjacentes = g;}

int no::getQuantAdjacente(){return quantAdjacentes;}

