#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include "aresta.h"

/**
 * aresta.cpp - Definicao das operacoes sobre arestas de um grafo
 *
 * Gisele Goulart  - 201365089C
 * Guilherme Felix - 201365504B
 *
 * Universidade Federal de Juiz de Fora
 * Departamento de Ciencia da Computacao
 * DCC001 - Analise e projetos de Algoritmos
 */

 // Construtor
aresta::aresta(int rotulo1, int rotulo2, int num_aresta){

  id = num_aresta;
  rotulo_a = rotulo1;
  rotulo_b = rotulo2;
  proxAresta = NULL;

}

// Destrutor
aresta::~aresta(){}

// Atribui a próxima aresta
void aresta::setProxAresta(aresta* x){proxAresta = x;}

// Retorna a proxima aresta
aresta* aresta::getProxAresta(){return proxAresta;}

// Retorna o Identificador da aresta
int aresta::getId(){return id;}

// Retorna o Identificador do vértices A
int aresta::getNoA(){return rotulo_a;}

// Retorna o Identificador do vértices B
int aresta::getNoB(){return rotulo_b;}

// Verifica se a aresta de identificador k é vizinha da aresta atual
// Retorna verdadeiro, se  não for vizinha ou falso, caso contrário
bool aresta::nao_vizinha(int k, aresta* arestas_candidatas){
    aresta* v = arestas_candidatas;
    while( v->getId() != k){
         v = v->getProxAresta();
    }
    if((this->getNoA() != v->getNoA()) && (this->getNoB() != v->getNoB())){
        if((this->getNoA() != v->getNoB()) && (this->getNoB() != v->getNoA())){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

