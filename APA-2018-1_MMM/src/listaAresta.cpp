#include "listaAresta.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

/**
 * listaAresta.cpp - Definicao das operacoes sobre uma lista de arestas.
 *
 * Gisele Goulart - 201365089C
 * Guilherme Felix - 201365504B
 *
 * Universidade Federal de Juiz de Fora
 * Departamento de Ciencia da Computacao
 * DCC001 - Analise e projetos de Algoritmos
 */


// Construtor
listaAresta::listaAresta(){
    arestaRaiz = NULL;
    ultimaAresta = NULL;
    qtdArestas = 0;
}


// Destrutor
listaAresta::~listaAresta(){
    aresta *p = arestaRaiz;
    while(p != NULL){
        aresta *t = p->getProxAresta();
        delete p;
        p = t;
    }
    ultimaAresta = NULL;
}

// Insere uma aresta na lista
void listaAresta::criarAresta(int rotulo_a, int rotulo_b, int num_aresta){
    aresta* nova = new aresta(rotulo_a, rotulo_b, num_aresta);
    qtdArestas++;
    if(this->arestaRaiz ==NULL){                    //se a lista está vazia
        this->arestaRaiz = nova;
        this->ultimaAresta = nova;
    }
    else{
        this->ultimaAresta->setProxAresta(nova);    //adiciona o novo nó no final da lista
        this->ultimaAresta = nova;                  //seta o novo ultimo
    }
}

// Retorna o numero de arestas na lista
int listaAresta::getQtdArestas(){return qtdArestas;}

// Define a quantidade de arestas na lista
void listaAresta::setQtdArestas(int qtd){qtdArestas = qtd;}

// Retorna a primeira aresta da lista
aresta* listaAresta::getArestaRaiz(){return this->arestaRaiz;}

// Define qual e a primeira aresta da lista
void listaAresta::setArestaRaiz(aresta* raiz){this->arestaRaiz = raiz;}

// Cria uma lista ordenada de acordo com os identificadores em perm.
// Exemplo: Suponha que perm = [7, 4, 3, 2, 5, 1], essa funcao retorna
// uma lista com as arestas ordenadas exatamente dessa forma.
aresta* listaAresta::ordenaArestas(int* perm){
    aresta* i = NULL;
    listaAresta* candidatas_ordenadas = new listaAresta();

    for (int k = 0; k<this->getQtdArestas(); k++){
       i = this->getArestaRaiz();
       //cout<<"Ordenacao das arestas: "<<perm[k]<<endl;
       while(i->getId() != perm[k]){
       //cout<<"Encontrei: "<<i->getId()<<endl;
        i = i->getProxAresta();
       }
       candidatas_ordenadas->criarAresta(i->getNoA(), i->getNoB(), i->getId());
    }
    return candidatas_ordenadas->getArestaRaiz();
}

// Deleta da lista de arestas a aresta com o id passado
void listaAresta::excluiAresta(int id){
    aresta* ex = this->getArestaRaiz();
    aresta* anterior = this->getArestaRaiz();
    // Se a aresta a ser apagada eh a primeira
    //cout<<"Aresta que tento excluir: "<<id<<endl;
    if(ex->getId()==id){
        this->setArestaRaiz(ex->getProxAresta());
    }
    else{
        while(ex->getId()!=id){
        //cout<<"Atual aresta: "<<ex->getId()<<endl;
        anterior = ex;
        ex = ex->getProxAresta();
        }
        //cout<<"Procurava "<<id<<" Exclui "<< ex->getId()<<endl;
        this->qtdArestas--;
        anterior->setProxAresta(ex->getProxAresta());
    }

    ex->setProxAresta(NULL);
    delete ex;
}
