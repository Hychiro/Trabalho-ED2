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
    cout << "Contruindo Lista" << endl;
    No *aux = new No();
    arqBin.seekg(0, ios_base::beg);
    int i = 0;
    while (arqBin.read((char *)aux, sizeof(No)))
    {
        while (vetorId[i + 1] == aux->getId())
        {
            this->AdicionaReview(aux->review_text);
            constroiConsultaReview << aux->review_text;
            i++;
        }
        if (aux->getId() == vetorId[i])
        {
            this->AdicionaReview(aux->review_text);
            constroiConsultaReview << aux->review_text;
            i++;
            if (i >= tam)
            {
                cout << "Lista Contruida!" << endl;
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
                // break;
            }
        }
        i++;
    }
}

void ListaDigitos::adicionaCodigoDigitoComprimido(SubDigito *vetorDigitos, Digito *raiz, int tam)
{
    int compara = 0;
    for (int i = 0; i < tam; i++) // para todo caractere da review
    {
        raiz->comprime(&vetorDigitos[i], &compara);
    }
    this->comparacoes = compara;
}

SubDigito *ListaDigitos::criaVetDigitos()
{
    int tamanhoVetDigitos = this->tamanhoLista;
    int l = tamanhoVetDigitos - 1;
    SubDigito *vetDigitos = new SubDigito[tamanhoVetDigitos];

    for (Digito *g = this->inicio; g != nullptr; g = g->proximo)
    {
        SubDigito *caractere = new SubDigito();
        caractere->setCodigo("");
        caractere->setDigito(g->digito);
        caractere->setNumReps(g->repeticoes);
        vetDigitos[l] = *caractere;
        delete caractere;
        l--;
    }
    return vetDigitos;
}

int particao(Digito *vetorStruct, int inicio, int fim, int imp)
{

    int i, j;
    Digito v, temp;
    v = vetorStruct[inicio];
    i = inicio;
    j = fim + 1;
    if (j >= imp)
    {
        j = imp;
    }

    do
    {
        do
        {
            i++;
        } while (vetorStruct[i].repeticoes < v.repeticoes && i <= fim);

        do
        {
            j--;
        } while (v.repeticoes < vetorStruct[j].repeticoes);

        if (i < j)
        {
            temp = vetorStruct[i];
            vetorStruct[i] = vetorStruct[j];
            vetorStruct[j] = temp;
        }

    } while (i < j);

    vetorStruct[inicio] = vetorStruct[j];
    vetorStruct[j] = v;

    return j;
}
void quickSort2(Digito *vetorStruct, int inicio, int fim, int imp)
{
    int j;
    if (inicio < fim)
    {
        j = particao(vetorStruct, inicio, fim, imp);
        quickSort2(vetorStruct, inicio, j - 1, imp);
        quickSort2(vetorStruct, j + 1, fim, imp);
    }
}

Digito *ListaDigitos::ordenaListaDigitos()
{
    int tam = this->tamanhoLista;
    Digito *vet = new Digito[tam];
    Digito *p = this->inicio;
    int i = 0;
    while (p != nullptr)
    {
        vet[i] = *p;
        i++;
        p = p->proximo;
    }

    quickSort2(vet, 0, tam, tam);

    for (int j = 0; j < tam; j++)
    {
        if (j == 0)
        {
            vet[j].proximo = &vet[j + 1];
            vet[j].anterior = nullptr;
        }
        if (j == (tam - 1))
        {
            vet[j].proximo = nullptr;
            vet[j].anterior = &vet[j - 1];
        }
        else
        {
            vet[j].proximo = &vet[j + 1];
            vet[j].anterior = &vet[j - 1];
        }
    }
    Digito *primeiro = &vet[0];
    return primeiro;
}

Digito *ListaDigitos::criaArvoreNaLista(Digito *primeiro)
{

    int tam = this->tamanhoLista;
    Digito *newPrimeiro;
    Digito *p;
    while (tam > 1)
    {
        Digito *aux = new Digito(primeiro, primeiro->proximo);
        p = primeiro;
        while (p != nullptr)
        {
            if (p->repeticoes >= aux->repeticoes)
            {
                Digito *ant = p->anterior;

                ant->proximo = aux;
                aux->anterior = ant;

                aux->proximo = p;
                p->anterior = aux;
                break;
            }
            else if (p->proximo == nullptr)
            {
                p->proximo = aux;
                aux->anterior = p;
                aux->proximo = nullptr;
                break;
            }
            p = p->proximo;
        }

        Digito *teste = primeiro->proximo;
        newPrimeiro = teste->proximo;
        this->apagaDaLista(primeiro, primeiro->proximo);
        tam--;

        primeiro = newPrimeiro;
    }
    return primeiro;
}