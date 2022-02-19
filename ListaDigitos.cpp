#include "Digito.h"
#include "ListaDigitos.h"
#include "No.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

ListaDigitos::ListaDigitos()
{
    this->inicio = NULL;
    this->fim = NULL;
    this->tamanhoLista = 0;
}

void ListaDigitos::ConstroiLista(ifstream &arqBin, int vetorId[], int tam)
{
    cout<<"erro que as vezes acontece e n faz sentido 1"<<endl;
    No *aux = new No();
    cout<<"erro que as vezes acontece e n faz sentido 2"<<endl;
    arqBin.seekg(0, ios_base::beg);
    int i = 0;
    while (arqBin.read((char *)aux, sizeof(No)))
    {
        while (vetorId[i + 1] == aux->getId())
        {
            this->AdicionaReview(aux->review_text);
            i++;
        }
        if (aux->getId() == vetorId[i])
        {
            this->AdicionaReview(aux->review_text);
            i++;
            if (i >= tam)
            {
                cout << "ACABOU" << endl;
                break;
            }
        }
    }
    delete aux;
}

void ListaDigitos::AdicionaFimDaLista(char a)
{
    Digito *novo = new Digito();
    if (this->inicio == NULL)
    { // caso ele seja o primeiro elemento da lista
        novo->digito = a;
        novo->repeticoes = 1;
        novo->jaBuscado = false;
        novo->filhoDir=NULL;
        novo->filhoEsq=NULL;

        novo->anterior=NULL;
        novo->proximo = NULL;
        this->inicio = novo;
        this->fim = novo;


        this->tamanhoLista++;
    }
    else
    { // caso contrario
        novo->digito = a;
        novo->repeticoes = 1;
        novo->jaBuscado = false;
        novo->filhoDir=NULL;
        novo->filhoEsq=NULL;

        novo->anterior=this->fim;
        this->fim->proximo = novo;
        novo->proximo = NULL;
        this->fim=novo;
        



        this->tamanhoLista++;
    }
}

void ListaDigitos::AdicionaReview(char review[3000])
{
    Digito *aux = new Digito();
    for (int i = 0; i < 3000; i++) // para todo caractere da review
    {
        if (this->inicio == NULL)
        {
            AdicionaFimDaLista(review[i]);
        }
        else
        {
            for (Digito *aux = this->inicio; aux != NULL; aux = aux->proximo) // percorrer toda a lista
            {
                if (aux->digito == review[i])
                { // se achar um caractere igual na lista
                    aux->repeticoes = aux->repeticoes + 1;      // soma 1 nas reptições
                    break;                                      // e para de percorrer a lista
                }else if (aux->proximo == NULL)
                {// se não achar um caractere igual na lista
                    this->AdicionaFimDaLista(review[i]);
                    break;          // adiciona no final da lista
                }
            }
        }
    }
    delete aux;
}

Digito *ListaDigitos::BuscaMaisRepeticoes()
{
    Digito *aux = new Digito();
    Digito *Resultado;
    int maior = 0;
    for (Digito *aux = this->inicio; aux != NULL; aux = aux->proximo) // percorrer toda a lista
    {
        if (aux->repeticoes > maior)
        {
            Resultado = aux;
            maior = aux->repeticoes;
        }
    }
    delete aux;

    Resultado->jaBuscado = true;

    return Resultado;
}

void ListaDigitos::ImprimeLista()
{
    Digito *aux = new Digito();
    aux = this->inicio;
    for (Digito *aux = this->inicio; aux != NULL; aux = aux->proximo) // percorrer toda a lista
    {
        cout << "Caractere: " << aux->digito << endl;
        cout << "Repeticoes: " << aux->repeticoes << endl;
    }
}
