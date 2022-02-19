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

void ListaDigitos::ConstroiLista(ifstream &arqBin, int vetorId[], int tam)
{
    No *aux = new No();
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
        novo->anterior = NULL;
        novo->proximo = NULL;
        novo->jaBuscado = false;
        this->inicio = novo;
    }
    else
    { // caso contrario
        novo->digito = a;
        novo->repeticoes = 1;
        novo->anterior = this->fim;
        novo->proximo = NULL;
        novo->jaBuscado = false;
        this->fim->proximo = novo;
    }
}

void ListaDigitos::AdicionaReview(char review[3000])
{
    Digito *aux = new Digito();
    for (int i = 0; i < 3000; i++) // para todo caractere da review
    {
        for (Digito *aux = this->inicio; aux != NULL; aux = aux->proximo) // percorrer toda a lista
        {

            if (aux->digito == review[i])
            {                                          // se achar um caractere igual na lista
                aux->repeticoes = aux->repeticoes + 1; // soma 1 nas reptições
                break;                                 // e para de percorrer a lista
            }

            if (aux->proximo == NULL)
            {                                          // se não achar um caractere igual na lista
                this->AdicionaFimDaLista(aux->digito); // adiciona no final da lista
            }
        }
    }
    delete aux;
}

Digito* ListaDigitos::BuscaMaisRepeticoes()
{
    Digito *aux = new Digito();
    Digito *Resultado;
    int maior=0;
    for (Digito *aux = this->inicio; aux != NULL; aux = aux->proximo) // percorrer toda a lista
    {
        if(aux->repeticoes>maior){
            Resultado=aux;
            maior=aux->repeticoes;
        }
    }
    delete aux;

    Resultado->jaBuscado=true;

    return Resultado;
}
