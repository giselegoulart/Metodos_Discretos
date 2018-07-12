#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

/**
 * aresta.h - Definicao da estrutura que representa a aresta de um grafo
 * Uma aresta possui dois extremos, os vértices a e b.
 * Essa estrutura representa um grafo nao direcionado, portanto a e b
 * sao apenas nomes para os extremos da aresta.
 *
 * Gisele Goulart  - 201365089C
 * Guilherme Felix - 201365504B
 *
 * Universidade Federal de Juiz de Fora
 * Departamento de Ciencia da Computacao
 * DCC001 - Analise e projetos de Algoritmos
 */

using namespace std;


class aresta{

public:
   aresta(int rotulo_a, int rotulo_b, int num_aresta);
   ~aresta();
   void setProxAresta(aresta* x);
   aresta* getProxAresta();
   int getId();
   int getNoA();
   int getNoB();
   bool nao_vizinha(int k, aresta* arestas_candidatas);


private:
    int id;
    int rotulo_a;
    int rotulo_b;
    aresta *proxAresta;
};

#endif // ARESTA_H_INCLUDED
