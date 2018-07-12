 /**
 * Universidade Federal de Juiz de Fora
 * Departamento de Ciencia da Computacao
 * DCC001 - Analise e projetos de Algoritmos - Trabalho Pratico
 *
 * main.cpp - Programa Principal
 *      Le um grafo a partir de um arquivo .txt 
 *      Preenche a estrutura grafo
 *      Executa o algoritmo forca bruta para obter a solucao do Emparelhamento Maximal Minimo (MMM)
 *      Executa o algoritmo que escreve as clausulas na FNC para entrada do miniSAT
 *      Executa o miniSat passando o arquivo de entrada e o de saida (no qual o miniSAT ira escrever)
 *
 * INSTRUCOES PARA A EXECUCAO DO CODIGO
 * Primeiramente, escreva o caminho onde o minisat esta instalado em sua maquina na variavel MINISAT, na linha 38
 * Dentro da pasta .../Emparelhamento-final execute no terminal o comando "make"
 * Execute o programa digitando no terminal: ./main <arquivo_contendo_grafo.txt>
 * As instancias usadas para teste sao: teste1_wiki.txt , teste2_wiki.txt, teste3_wiki.txt, teste4.txt, teste_10.txt, teste_30.txt
 *
 * Gisele Goulart - 201365089C
 * Guilherme Felix - 201365504B
 *
 *
 */

#include <iostream>
#include <stdlib.h>
#include "no.h"
#include "lista.h"
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <time.h>

#define myrand (float)(random())/(float)(RAND_MAX)

// COLOQUE AQUI O CAMINHO COMPLETO PARA O MINISAT
string MINISAT = "~/Documentos/minisat/core";

using namespace std;

// Funcao que escreve o grafo em arquivo
void escreveGrafo(lista* grafo, char arqSaida[]){
    int tam = grafo->getQuantNo();
    int visitados[tam];
    ofstream out;
    //out.open(arqSaida.c_str());
    out.open(arqSaida);

    for(int i=0; i<tam; i++){
        visitados[i]=0;
    }
    out<<grafo->getQuantNo();
    out<<"\n";

    no* atual = grafo->getRaiz();
    while(atual!=NULL){
       no* visitado = atual->getAdjacente();

       while(visitado != NULL){
          if(visitados[visitado->getIndex()-1]==0){
             out<<atual->getIndex();
             out<<" ";
             out<<visitado->getIndex();
             out<<" ";
             out<<"\n";
          }
          visitado = visitado->getAdjacente();
          visitados[atual->getIndex()-1] = 1;
       }
       atual = atual->getIrmao();
    }
    out.close();
}

// Funcao para realizar a impressao do grafo na tela
void imprimeGrafo (no* raiz)
{
    cout<<"Imprimindo Grafo "<<endl;

    for (no* vertice = raiz; vertice != NULL; vertice = vertice->getIrmao()) //percorrendo a lista de nos irmaos
    {
        //IMPRIMINDO lista de nos do grafo
        cout<<"Index= "<<vertice->getIndex() << " Valor= "<<vertice->getValor()<<endl;
        //Imprimindo adjacentes
        if(vertice->getAdjacente() != NULL)
        {
            cout<<"Nos adjacentes ao no "<<vertice->getValor()<<":"<<endl;
            no* i = vertice->getAdjacente();
            while(i!= NULL)
            {
                cout<<i->getValor()<< "\t";
                i = i->getAdjacente();
            }

            cout<<endl;
        }

    }
    return ;
}


int main(int argc, char* argv[])
{
    lista* grafo = new lista();
    string arq; //string para armazenar entradas do arquivo

    ifstream arqEntrada(argv[1]);
    while(!arqEntrada.eof()) //continua a inserção dos dados do arquivo até que o mesmo chegue ao fim
    {
        getline(arqEntrada,arq);
        grafo->inserir(arq);
    }

    cout << "Numero de nos inseridos : " << grafo->getQuantNo() << endl;
	// Para rodar o SAT com instancias maiores que 10 e necessario comentar a chamada do forca bruta abaixo
    grafo->MMMForcaBruta();

    for(int k=1; k<=grafo->getQtdArestas(); k++){
        grafo->geraSAT(k);
        // No lugar de /home/gisele/Instalacoes/minisat/core/minisat
        // e necessario incluir o diretorio onde o minisat foi instalado
        //int saida = system("/home/gisele/Instalacoes/minisat/core/minisat sat.in sat.out");
        int ret_val = system(MINISAT.c_str());
        ifstream sat("sat.out");
        string s;
        getline(sat,s);

        if(s[0]=='S'){
            cout<<"\n SAT retornou instancia satisfativel com K="<<k<<endl;
            break;
        }
    }


    delete grafo;

    arqEntrada.close();
    return 0;
}
