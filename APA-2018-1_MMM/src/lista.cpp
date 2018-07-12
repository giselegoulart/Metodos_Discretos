#include "lista.h"
#include "no.h"
#include "listaAresta.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <bits/stdc++.h>


/**
 * lista.cpp - Definicao das operacoes sobre um grafo por lista de adjacencia.
 *
 * Gisele Goulart - 201365089C
 * Guilherme Felix - 201365504B
 *
 * Universidade Federal de Juiz de Fora
 * Departamento de Ciencia da Computacao
 * DCC001 - Analise e projetos de Algoritmos
 */

// Listas e variaveis globais
listaAresta* candidatas = new listaAresta();
int conta_arestas = 0;
bool LEFT_TO_RIGHT = true;
bool RIGHT_TO_LEFT = false;

// Construtor
lista::lista(){
    raiz = NULL;
    ultimo = NULL;
    quantidadeNo = 0;
}

// Destrutor
lista::~lista(){
    no *p = raiz;
    while(p != NULL){
        no *t = p->getIrmao();
        delete p;
        p = t;
    }
    ultimo = NULL;
}

// Atribui um vertice como raiz (o primeiro vertice na lista de adjacencias)
void lista::setRaiz(no *x){raiz = x;}

// Retorna o no raiz
no* lista::getRaiz(){return this->raiz;}

// Define o ultimo no (o ultimo vertice na lista de adjacencias)
void lista::setUltimo(no* x){ultimo = x;}

// Retorna o ultimo no
no* lista::getUltimo(){return ultimo;}

// Atribui um vertice x como adjacente
void lista::setAdjacente(no* x){raiz->setIrmao(x);}

no *lista::getAdjacente(){return this->raiz->getIrmao();}

// Constroi um grafo a partir da leitura de um arquivo externo
void lista::inserir(string arq){
    if(arq[0] != '\0' && arq[0] == 'e'){
        char str[10];
        int j=0, l, valorNo, adjacente;
        for(l = 2; arq[l] != ' '; l++){ // Le o indice do primeiro no
            str[j] = arq[l];
            j++;
        }
        str[j] = '\0';
        valorNo = atoi(str);

        l++;
        j = 0;
        for(; arq[l] != '\0'; l++){ // Le o indice do segundo no
                str[j] = arq[l];
                j++;
        }
        str[j] = '\0';
        adjacente = atoi(str);

        // Inclusao de aresta em lista de arestas independente
        conta_arestas++;
        candidatas->criarAresta(valorNo, adjacente,conta_arestas);

        no* verifica1 = existeNo(valorNo);
        no* verifica2 = existeNo(adjacente);

        no* novo = new no(this->getQuantNo(),valorNo);
        if(verifica1 == NULL){
            this->incluirNo(novo);
        }
        else{delete novo;}

        no* adjac = new no(this->getQuantNo(),adjacente);
        if(verifica2 == NULL){
            this->incluirNo(adjac);
            }

        else{delete adjac;}

        if(verifica1==NULL && verifica2==NULL){ this->incluirAresta(novo, adjac, 0);}

        else if(verifica1==NULL && verifica2!=NULL){this->incluirAresta(novo, verifica2, 0);}

        else if(verifica1!=NULL && verifica2==NULL){this->incluirAresta(verifica1, adjac, 0);}

       else if(verifica1!=NULL && verifica2!=NULL){this->incluirAresta(verifica1, verifica2, 0);}

    }
    candidatas->setQtdArestas(conta_arestas);
}

void lista::incluirNo(no* novo){
    quantidadeNo++;
    if(this->raiz ==NULL){//se a lista está vazia
        this->raiz = novo;
        this->ultimo = novo;
    }
    else{
        this->ultimo->setIrmao(novo);//adiciona o novo nó no final da lista
        this->ultimo = novo; //seta o novo ultimo
    }

}

// Inclui uma aresta ligando os vertices x e y  no grafo
void lista::incluirAresta(no* x, no* y, float p){
    int verif = 0;      //inteiro usado para verificar se já inseriu a aresta nos dois nos
    no*i = new no(0,0);
for (no* i = this->raiz; i != NULL; i = i->getIrmao()){// percorre toda lista de nos irmaos

    if(i->getValor() == x->getValor()){                             //verifica se encontrou um dos nos incidentes na aresta e insere no inicio da lista
        i->setGrau(i->getGrau()+1);                                 //incremendtando o grau
        i->setSomatorioGrau(i->getSomatorioGrau() + y->getGrau());  //incrementando o somatório dos nós adjacentes a x
        i->setQuantAdjacente(i->getQuantAdjacente()+1);             //incrementado a quantidade de nos adjacente a x
        no* aux = new no(y->getIndex(), y->getValor());             //cria um no adjacente                                           //setando o peso da aresta
        aux->setAdjacente(i->getAdjacente());
        i->setAdjacente(aux);
        verif++;
        }



        else if(i->getValor() == y->getValor()){
         //i->setGrau(i->getGrau()+1);//incremendtando o grau
        no* aux = new no(x->getIndex(), x->getValor());             //cria um no adjacente
        aux->setAdjacente(i->getAdjacente());
        i->setAdjacente(aux);
        i->setGrau(i->getGrau()+1);                                 // aumentando o grau do no
        i->setSomatorioGrau(i->getSomatorioGrau() + x->getGrau());  //incrementando o somatório dos nós adjacentes a y
        i->setQuantAdjacente(i->getQuantAdjacente()+1);             //incrementado a quantidade de nos adjacente a y
        verif++;
        }

        if(verif == 2){break;}                                       //verifica se ja inseriu a arestas nos respectivos nos x e y
    }
    delete i;

}


// Exclui o no cujo Identificador = valor do grafo
void lista::excluirNo(int valor){

        no *antecessorIrmao = NULL;//criando o no auxiliar que vai armazenar o no antecessor do no "i" da lista de irmaos.
        no* i = raiz;

        while(i != NULL && i->getValor() != valor){//percorrendo a lista de irmaos
            antecessorIrmao = i;
            i = i->getIrmao();
        }

        if(i == NULL){return;}//nao achou i na lista

        if(antecessorIrmao == NULL){//se for o primeiro da lista

            no* aux = i->getAdjacente();

            while(i->getAdjacente() != NULL){
                no* antes = NULL;
                aux = i->getAdjacente();

                while(aux->getAdjacente() != NULL){
                antes = aux;
                aux= aux->getAdjacente();
            }

            if(antes == NULL){
                i->setAdjacente(NULL);
                no* p = aux;
                delete p;}

              else{
                no* p = aux;
                antes->setAdjacente(NULL);
                aux = antes;
                p->setIrmao(NULL);
                p->setAdjacente(NULL);
                delete p;}
            }

        this->raiz = i->getIrmao();
        }


    else{//se for do meio
            no* aux = i->getAdjacente();

            while(i->getAdjacente() != NULL){
                no* antes = NULL;
                aux = i->getAdjacente();

                while(aux->getAdjacente() != NULL){
                antes = aux;
                aux= aux->getAdjacente();
            }

            if(antes == NULL){
                i->setAdjacente(NULL);
                no* p = aux;
                delete p;}

              else{
                no* p = aux;
                antes->setAdjacente(NULL);
                aux = antes;
                p->setIrmao(NULL);
                p->setAdjacente(NULL);
                delete p;}
            }
             antecessorIrmao->setIrmao(i->getIrmao());
             i->setIrmao(NULL);
          }

        delete i;
        return;

}

// Exclui a aresta entre x e y do grafo
void lista::excluirAresta(no*x, no*y, float p){

    no* j;
    no* aux1;
    no* k;
    no* aux2;

for (no* i = this->raiz; i != NULL; i = i->getIrmao()){// percorre toda lista de nos irmaos

    if(i->getValor() == x->getValor()){ //verifica se encontrou um dos nos incidentes na aresta
        j = i;
        aux1 = i;
        while(j->getValor() != y->getValor() && j != NULL){ //percorre a lista de nos adjacentes
            aux1 = j;
            j = j->getAdjacente();
            }
            //sai do while com j->getValor() = y->getValor ou j = NULL
    }

    if(i->getValor() == y->getValor()){
        k = i;
        aux2 = i;
        while(k->getValor() != x->getValor() && k != NULL){ //percorre a lista de nos adjacentes
            aux2 = k;
            k = k->getAdjacente();
            }
         //sai do while com k->getValor() = x->getValor ou k = NULL
    }

   }

    //SAINDO DOS IF's//
        if(j->getValor() == y->getValor() && k->getValor() == x->getValor() ){// achou a aresta incidente aos nos "x" e "y"
            //excluindo o no y
            j->setGrau(j->getGrau() - 1);
            j->setSomatorioGrau(j->getSomatorioGrau() - x->getGrau());
            j->setQuantAdjacente(j->getQuantAdjacente() - 1);
            aux1->setAdjacente(j->getAdjacente());

            //exluindo o no x
            k->setGrau(k->getGrau() - 1);
            k->setSomatorioGrau(k->getSomatorioGrau() - y->getGrau());
            k->setQuantAdjacente(k->getQuantAdjacente() - 1);
            aux2->setAdjacente(k->getAdjacente());
            cout<<"EXCLUIU  a aresta incidente aos nos "<<x->getValor()<<" e "<<y->getValor()<<endl;

        }
        else
        cout<<"NAO EXISTE a aresta incidente aos nos "<<x->getValor()<<" e "<<y->getValor()<<endl;


}


bool lista::existeAresta(no* x, no* y){

    no* k;
    no* j;

for (no* i = this->raiz; i != NULL; i = i->getIrmao()){// percorre toda lista de nos irmaos

    if(i->getValor() == x->getValor()){ //verifica se encontrou um dos nos incidentes na aresta
        j = i;
        while(j->getValor() != y->getValor() && j != NULL){ //percorre a lista de nos adjacentes
            j = j->getAdjacente();
            }
            //sai do while com j->getValor() = y->getValor ou j = NULL
    }//saindo do primeiro if

    if(i->getValor() == y->getValor()){
        k = i;
        while(k->getValor() != x->getValor() && k != NULL){ //percorre a lista de nos adjacentes
            k = k->getAdjacente();
            }
         //sai do while com k->getValor() = x->getValor ou k = NULL
        }//saindo dosegundo if
   }//saindo do for

    //SAINDO DOS IF's//
        if(j->getValor() == y->getValor() && k->getValor() == x->getValor()){// achou a aresta incidente aos nos "x" e "y"
           return true;
        }
        else
        return false;
}

no* lista::existeNo(int valor){
    for (no* i = this->raiz; i != NULL; i = i->getIrmao()){// percorre toda lista de nos irmaos
     if(i->getValor() == valor) {
            return i;}
    }
    return NULL;
}

int lista::getQuantNo(){
    return quantidadeNo;
}

void lista::setQuantNo(int i){
    quantidadeNo = i;
}


// Funcao auxiliar para encontrar a
// posicao do maior inteiro movel em a[]
int lista::searchArr(int a[], int n, int mobile)
{
	for (int i = 0; i < n; i++)
		if (a[i] == mobile)
		return i + 1;
}

// Para realizar o passo 1 do algoritmo, ou seja
// para encontrar o maior inteiro movel
int lista::getMobile(int a[], bool dir[], int n)
{
	int mobile_prev = 0, mobile = 0;
	for (int i = 0; i < n; i++)
	{
		// direcao 0 representa RIGHT TO LEFT.
		if (dir[a[i]-1] == RIGHT_TO_LEFT && i!=0)
		{
			if (a[i] > a[i-1] && a[i] > mobile_prev)
			{
				mobile = a[i];
				mobile_prev = mobile;
			}
		}

		// direcao 1 representa LEFT TO RIGHT.
		if (dir[a[i]-1] == LEFT_TO_RIGHT && i!=n-1)
		{
			if (a[i] > a[i+1] && a[i] > mobile_prev)
			{
				mobile = a[i];
				mobile_prev = mobile;
			}
		}
	}

	if (mobile == 0 && mobile_prev == 0)
		return 0;
	else
		return mobile;
}


int* lista::onePerm(int *a, bool dir[], int n)
{
	int mobile = getMobile(a, dir, n);
	int pos = searchArr(a, n, mobile);

    // swap dos elementos de acordo com sua direcao
	if (dir[a[pos - 1] - 1] == RIGHT_TO_LEFT)
	swap(a[pos-1], a[pos-2]);

	else if (dir[a[pos - 1] - 1] == LEFT_TO_RIGHT)
	swap(a[pos], a[pos-1]);

	// mudanca da direcao dos elementos
    //maior que o maior número inteiro móvel.
	for (int i = 0; i < n; i++)
	{
		if (a[i] > mobile)
		{
			if (dir[a[i] - 1] == LEFT_TO_RIGHT)
				dir[a[i] - 1] = RIGHT_TO_LEFT;
			else if (dir[a[i] - 1] == RIGHT_TO_LEFT)
				dir[a[i] - 1] = LEFT_TO_RIGHT;
		}
	}
    return a;
}

// Funcao auxiliar que calcula o fatorial de n (numero de arestas).
int lista::fact(int n)
{
	int res = 1;
	for (int i = 1; i <= n; i++)
		res = res * i;
	return res;
}


// Funcao que, dada uma permutacao das arestas, gera uma lista de arestas com a ordem passada
// e procura um emparelhamneto nessas arestas. Salva uma solucao temporaria.
// Se o tamanho dessa solucao temporaria for menor do que o tamanho da solucao global,
// solucao glogal = solucao temporaria.
aresta* lista::matching(int *perm, listaAresta* solucao, listaAresta* candidatas){

    listaAresta* candidatas_perm = new listaAresta();
    listaAresta* solucao_global = new listaAresta();
    candidatas_perm->setArestaRaiz(candidatas->ordenaArestas(perm));

    for(aresta* a = solucao->getArestaRaiz(); a!=NULL; a = a->getProxAresta()){
        solucao_global->criarAresta(a->getNoA(), a->getNoB(), a->getId());
    }

    int nao_vizinhas = 0;
    listaAresta* candidatas_copia = new listaAresta();
    for(aresta* i = candidatas_perm->getArestaRaiz(); i != NULL; i = i->getProxAresta()){
        for(aresta* aux = candidatas_perm->getArestaRaiz(); aux!=NULL; aux = aux->getProxAresta()){
            candidatas_copia->criarAresta(aux->getNoA(), aux->getNoB(), aux->getId());
        }
        listaAresta* solucao_temp = new listaAresta();
        solucao_temp->criarAresta(i->getNoA(), i->getNoB(), i->getId());

        //retira aresta i de candidatas_copia, pois ela já esta na solucao temporaria
        candidatas_copia->excluiAresta(i->getId());

        for(aresta* j = candidatas_copia->getArestaRaiz(); j!=NULL; j = j->getProxAresta()){
            nao_vizinhas = 0;
            for (aresta* k = solucao_temp->getArestaRaiz(); k!=NULL; k = k->getProxAresta()){
                if(k->nao_vizinha(j->getId(), candidatas_copia->getArestaRaiz())==true){
                    nao_vizinhas++;
                }
                else
                    break;
            }
            if(nao_vizinhas == solucao_temp->getQtdArestas()){
                solucao_temp->criarAresta(j->getNoA(), j->getNoB(), j->getId());
            }
        }
        if(solucao_temp->getQtdArestas() < solucao_global->getQtdArestas()){
            delete solucao_global;
            listaAresta* solucao_global = new listaAresta();
            for(aresta* candidata = solucao_temp->getArestaRaiz(); candidata!=NULL; candidata = candidata->getProxAresta()){
                solucao_global->criarAresta(candidata->getNoA(), candidata->getNoB(), candidata->getId());
                cout<<"No "<<candidata->getNoA()<<" "<<"No "<<candidata->getNoB()<<" ID Aresta "<<candidata->getId()<<endl;
            }
            cout<<"Atualizacao da solucao global. Nova qtd de arestas na solucao: "<< solucao_global->getQtdArestas()<<endl;
        }

        delete solucao_temp;
    }
    return solucao_global->getArestaRaiz();
}

// Funcao forca bruta para encontrar o emparelhamento maximal minimo.
// A funcao gera todas as permutacoes das arestas, procurando um emparelhamento entre elas
// e a cada momento comecando de uma aresta diferente da lista de candidatas.
// Esse procedimento visa contemplar todas as combinacoes de arestas que possam formar um matching,
// e dessa forma salvar o menor.
void lista::MMMForcaBruta(){

	int n = candidatas->getQtdArestas();
	// guarda a permutacao corrente
	int a[n];
    int* perm;
    listaAresta* solucao = new listaAresta();
    aresta* raiz_solucao = new aresta(-1, -1, -1);
    for(aresta* candidata = candidatas->getArestaRaiz(); candidata!=NULL; candidata = candidata->getProxAresta()){
        solucao->criarAresta(candidata->getNoA(), candidata->getNoB(), candidata->getId());
    }
    //solucao->setArestaRaiz(candidatas->getArestaRaiz());
    cout<<"Qtd de arestas candidatas: "<<candidatas->getQtdArestas()<<endl;


	// Para armazenar as direcoes
	bool dir[n];

	// guardando os elemento de 1 a n
	for (int i = 0; i < n; i++)
	{
		a[i] = i + 1;
	}

	// inicialmente todas as direcoes sao
	// setadas com RIGHT TO LEFT
	for (int i = 0; i < n; i++)
		dir[i] = RIGHT_TO_LEFT;

	// geracao das permutacoes em ordem
	for (int i = 1; i < fact(n); i++){
		perm = onePerm(a, dir, n);
        raiz_solucao = matching(perm, solucao, candidatas);
        solucao->setArestaRaiz(raiz_solucao);
        int qtd_exata = 0;
        for(aresta* cont = raiz_solucao; cont!=NULL; cont = cont->getProxAresta()){
            qtd_exata++;
        }
        solucao->setQtdArestas(qtd_exata);
    }
    cout<< "\n Arestas na solucao final do Forca Bruta: "<<solucao->getQtdArestas()<<endl;

}

void lista::geraSAT(int k){
    stringstream buffer;
    int totalclausulas = 0;
    int clausulas;
    string retorno_clausulas = "";
    ofstream out;

    int variaveis = k*(candidatas->getQtdArestas());


    for (int i = 1; i<=k; i++){
        clausulas = 0;
        listaAresta* novosIdsArestas = new listaAresta();
        for (aresta* renomear = candidatas->getArestaRaiz(); renomear!=NULL; renomear = renomear->getProxAresta()){
            int novoId = (renomear->getId()-1)*k + i;
            novosIdsArestas->criarAresta(renomear->getNoA(), renomear->getNoB(), novoId);
        }
        //  primeira parte da formula
        atMostOne(novosIdsArestas, clausulas, buffer);

        totalclausulas+=clausulas;
        delete novosIdsArestas;
    }


    for (aresta* vizinha = candidatas->getArestaRaiz(); vizinha!=NULL; vizinha = vizinha->getProxAresta()){
        clausulas = 0;
        listaAresta* novosIdsArestas = new listaAresta();
        aresta* candidata = candidatas->getArestaRaiz();
        for (int i = 1; i<=k; i++){
            // comparando se estou no mesmo no da lista de arestas
            if(vizinha->getId()!=candidata->getId()){
                // preciso que as duas arestas sejam vizinhas
                if(vizinha->nao_vizinha(candidata->getId(), candidatas->getArestaRaiz())==false){
                    int novoIdcandidata = (candidata->getId()-1)*k + i;
                    int novoIdvizinha = (vizinha->getId()-1)*k + i;
                    novosIdsArestas->criarAresta(candidata->getNoA(), candidata->getNoB(), novoIdcandidata);
                    novosIdsArestas->criarAresta(vizinha->getNoA(), vizinha->getNoB(), novoIdvizinha);
                }
            }
            candidata = candidata->getProxAresta();
        }
        //segunda parte da formula
        atMostOne(novosIdsArestas, clausulas, buffer);
        totalclausulas+=clausulas;
        delete novosIdsArestas;
    }


   for (aresta* candidata = candidatas->getArestaRaiz(); candidata!=NULL; candidata = candidata->getProxAresta()){
        clausulas = 0;
        listaAresta* novosIdsArestas = new listaAresta();
        aresta* vizinha = candidatas->getArestaRaiz();
        for (int i = 1; i<=k; i++){
            int novoIdcandidata = (candidata->getId()-1)*k + i;
            novosIdsArestas->criarAresta(candidata->getNoA(), candidata->getNoB(), novoIdcandidata);
            if(vizinha->getId()!=candidata->getId()){
                // preciso que as duas arestas sejam vizinhas
                if(candidata->nao_vizinha(vizinha->getId(), candidatas->getArestaRaiz())==false){
                    int novoIdvizinha = (vizinha->getId()-1)*k + i;
                    novosIdsArestas->criarAresta(vizinha->getNoA(), vizinha->getNoB(), novoIdvizinha);
                }
            }
            vizinha = vizinha->getProxAresta();
        }
        // terceira parte da formula de transformacao para SAT
        atLeastOneAdap(novosIdsArestas, clausulas, buffer);
        totalclausulas+=clausulas;
        delete novosIdsArestas;
    }

    cout<<"\nGerou sat.in com K="<<k<<endl;
    std::ofstream of("sat.in", std::ofstream::out | std::ofstream::binary);
	of << "p cnf " << variaveis << " " << totalclausulas << std::endl;
	of << buffer.rdbuf();
	of.close();

}

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

void lista::atMostOne(listaAresta* novosIdsArestas, int& clausulas, stringstream &buffer){
    string retorno_temp="";
    if(novosIdsArestas->getQtdArestas()>0){
        aresta* aresta_j = novosIdsArestas->getArestaRaiz();
        for (int j = 2; j<=novosIdsArestas->getQtdArestas(); j++){
            aresta_j = aresta_j->getProxAresta();
            aresta* aresta_i = novosIdsArestas->getArestaRaiz();
            for (int i = 1; i<j; i++){
                buffer << -aresta_i->getId() << " " << -aresta_j->getId() << " 0" << std::endl;

                clausulas++;
            }
        }
    }
}

void lista::atLeastOneAdap(listaAresta* novosIdsArestas, int& clausulas, stringstream& buffer){
    string retorno_temp="";
    for (aresta* aux = novosIdsArestas->getArestaRaiz(); aux!=NULL; aux = aux->getProxAresta()){
        buffer<<aux->getId()<<" ";
    }
    for (aresta* aux = novosIdsArestas->getArestaRaiz(); aux!=NULL; aux = aux->getProxAresta()){
        buffer<<aux->getId()<<" ";
    }
    buffer<<"0"<<std::endl;
    clausulas=1;

}

int lista::getQtdArestas(){
    return candidatas->getQtdArestas();
}
