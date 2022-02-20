#include "Digito.h"
#include "ListaDigitos.h"
#include "No.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include "SubDigito.h"

using namespace std;

ListaDigitos::ListaDigitos()
{
    this->inicio = NULL;
    this->fim = NULL;
    this->tamanhoLista = 0;
}

void ListaDigitos::ConstroiLista(ofstream &constroiConsultaReview, ifstream &arqBin, int vetorId[], int tam)
{
    cout << "erro que as vezes acontece e n faz sentido 1" << endl;
    No *aux = new No();
    cout << "erro que as vezes acontece e n faz sentido 2" << endl;
    arqBin.seekg(0, ios_base::beg);
    int i = 0;
    while (arqBin.read((char *)aux, sizeof(No)))
    {
        while (vetorId[i + 1] == aux->getId())
        {
            this->AdicionaReview(aux->review_text);
            constroiConsultaReview<<aux->review_text;
            i++;
        }
        if (aux->getId() == vetorId[i])
        {
            this->AdicionaReview(aux->review_text);
            constroiConsultaReview<<aux->review_text;
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
        novo->dir = NULL;
        novo->esq = NULL;

        novo->anterior = NULL;
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
        novo->dir = NULL;
        novo->esq = NULL;

        novo->anterior = this->fim;
        this->fim->proximo = novo;
        novo->proximo = NULL;
        this->fim = novo;

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
                {                                          // se achar um caractere igual na lista
                    aux->repeticoes = aux->repeticoes + 1; // soma 1 nas reptições
                    break;                                 // e para de percorrer a lista
                }
                else if (aux->proximo == NULL)
                { // se não achar um caractere igual na lista
                    this->AdicionaFimDaLista(review[i]);
                    break; // adiciona no final da lista
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

void ListaDigitos::apagaDaLista(Digito *a, Digito *b) // botar na struct da lista
{
    Digito *auxAnt;
    Digito *auxProx;

    if (a->anterior == nullptr && b->proximo == nullptr)
    {
        // chegamos ao fim
        a->proximo = nullptr;
        b->anterior = nullptr;
        return;
    }
    else if (b->anterior == nullptr && a->proximo == nullptr)
    {
        b->proximo = nullptr;
        a->anterior = nullptr;
        return;
    }

    if (a->proximo != b && b->proximo != a)
    {
        // retira A
        auxAnt = a->anterior;
        auxProx = a->proximo;

        if (auxAnt != nullptr && auxProx != nullptr)
        {
            auxAnt->proximo = auxProx;
            auxProx->anterior = auxAnt;
        }
        else if (auxAnt == nullptr)
        {
            auxProx->anterior = auxAnt;
        }
        else if (auxProx == nullptr)
        {
            auxAnt->proximo = auxProx;
        }

        a->anterior = nullptr;
        a->proximo = nullptr;

        // retira B
        auxAnt = b->anterior;
        auxProx = b->proximo;

        if (auxAnt != nullptr && auxProx != nullptr)
        {
            auxAnt->proximo = auxProx;
            auxProx->anterior = auxAnt;
        }
        else if (auxAnt == nullptr)
        {
            auxProx->anterior = auxAnt;
        }
        else if (auxProx == nullptr)
        {
            auxAnt->proximo = auxProx;
        }

        b->anterior = nullptr;
        b->proximo = nullptr;
    }
    else
    {

        if (a->proximo == b)
        {

            auxAnt = a->anterior;
            auxProx = b->proximo;
            if (auxAnt != nullptr && auxProx != nullptr)
            {
                auxAnt->proximo = auxProx;
                auxProx->anterior = auxAnt;
            }
            else if (auxAnt == nullptr)
            {
                auxProx->anterior = auxAnt;
            }
            else if (auxProx == nullptr)
            {
                auxAnt->proximo = auxProx;
            }

            a->anterior = nullptr;
            a->proximo = nullptr;

            b->anterior = nullptr;
            b->proximo = nullptr;
        }
        else if (b->proximo == a)
        {
            auxAnt = b->anterior;
            auxProx = a->proximo;

            if (auxAnt != nullptr && auxProx != nullptr)
            {
                auxAnt->proximo = auxProx;
                auxProx->anterior = auxAnt;
            }
            else if (auxAnt == nullptr)
            {
                auxProx->anterior = auxAnt;
            }
            else if (auxProx == nullptr)
            {
                auxAnt->proximo = auxProx;
            }

            a->anterior = nullptr;
            a->proximo = nullptr;

            b->anterior = nullptr;
            b->proximo = nullptr;
        }
    }
}

void ListaDigitos::constroiArquivoComprimida(ifstream &arqBin, ofstream &comprimido, SubDigito *vetorDigitos, int tam)
{
   
    arqBin.seekg(0, arqBin.end);
    int tamanho = arqBin.tellg();
    arqBin.seekg(0, arqBin.beg);
    char *buffer = new char[tamanho];
    arqBin.read(buffer, tamanho);
    
    int i = 0;

    while (i < tamanho)
    {
        for (int k = 0; k < tam; k++)
        {
            if (buffer[i] == vetorDigitos[k].getDigito())
            {
                comprimido << vetorDigitos[k].getCodigo();
                //break;
            }
        }
        i++;
    }
    
}

void ListaDigitos::adicionaCodigoDigitoComprimido(SubDigito *vetorDigitos, Digito *raiz, int tam)
{

    for (int i = 0; i < tam; i++) // para todo caractere da review
    {
        raiz->comprime(&vetorDigitos[i]);
    }
}