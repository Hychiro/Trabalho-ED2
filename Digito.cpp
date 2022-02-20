#include "Digito.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

Digito::Digito(Digito *a, Digito *b)
{
    int maior;
    int menor;
    if (a->repeticoes >= b->repeticoes)
    {
        maior = a->repeticoes;
        menor = b->repeticoes;
        this->esq = b;
        this->dir = a;
    }
    else
    {
        maior = b->repeticoes;
        menor = a->repeticoes;
        this->esq = a;
        this->dir = b;
    }
    this->repeticoes = maior + menor;
    this->digito = '\0';

    // a->jaBuscado = true;
    // b->jaBuscado = true;
    //nArvores--;
}
Digito::Digito()
{
}

Digito::~Digito()
{
    //dtor
}

void Digito::imprime()
{
    if (this->dir != nullptr)
        cout << "DIREITA: " << this->dir->repeticoes << endl;
    else
        cout << "DIREITA: NULL" << endl;
    if (this->esq != nullptr)
        cout << "ESQUERDA: " << this->esq->repeticoes << endl;
    else
        cout << "ESQUERDA: NULL" << endl;
    cout << "SOMA: " << this->repeticoes << endl;
}

void Digito::imprimeN()
{
    imprimePorNivel(this, 0);
}

void Digito::imprimePorNivel(Digito *p, int nivel)
{
    if (p != NULL)
    {
        cout << "(" << nivel << ")";
        for (int i = 1; i <= nivel; i++)
            cout << "--";
        if(p->digito!='\0')
            cout << p->digito << endl;
        else{
            cout << "null" << endl;
        }
        imprimePorNivel(p->esq, nivel + 1);
        imprimePorNivel(p->dir, nivel + 1);
    }
}

void Digito::comprime(char dig, ofstream &comprimido)
{
    bool encontrou = false;
    string text = "";
    auxComprime(this, dig, text, &encontrou, comprimido);
}

void Digito::auxComprime(Digito *p, char dig, string text, bool *encontrou, ofstream &comprimido)
{
    if (p != NULL)
    {
        if (p->digito == dig)
        {
            *encontrou = true;
            comprimido << text;
            return;
        }

        text = text + '0';
        if (!*encontrou)
        {
            auxComprime(p->esq, dig, text, encontrou, comprimido);
            text.pop_back();
        }
        text = text + '1';
        if (!*encontrou)
        {
            auxComprime(p->dir, dig, text, encontrou, comprimido);
            text.pop_back();
        }
    }
}

void Digito::descomprimir(char *buffer, int tamanho, ofstream &descomprimido)
{
    int i = 0;

    Digito *p = this;
    //cout << p->repeticoes << endl;
    //cout << p->esq->repeticoes << endl;
    cout << tamanho << endl;
    while (i < tamanho)
    {
        auxDescomprimir(p, buffer, &i, descomprimido);
    }
    cout << i << endl;
}

void Digito::auxDescomprimir(Digito *p, char* buffer, int *i, ofstream &descomprimido)
{
    Digito *aux;
    if (p != NULL)
    {
        // cout<<this->repeticoes<<endl;
        if (p->esq == nullptr && p->dir == nullptr)
        {
            //cout << p->digito;
            descomprimido << p->digito;
            return;
        }

        if (buffer[*i] == '0')
        {
            // cout<<"esq"<<endl;
            *i = 1 + *i;
            aux = p->esq;

            auxDescomprimir(aux, buffer, i, descomprimido);
         
        }

        if (buffer[*i] == '1')
        {
            // cout<<"dir"<<endl;
            *i = 1 + *i;
            aux = p->dir;

            auxDescomprimir(aux, buffer, i++, descomprimido);
          
        }
    }
}