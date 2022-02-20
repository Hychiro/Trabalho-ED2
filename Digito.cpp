#include "Digito.h"
#include <iostream>

using namespace std;

Digito::Digito(Digito *a, Digito *b)
{
    int maior;
    int menor;
    if (a->repeticoes >= b->repeticoes)
    {
        maior = a->repeticoes;
        menor = b->repeticoes;
        this->esq /*esq*/ = b;
        this->dir /*dir*/ = a;
    }
    else
    {
        maior = b->repeticoes;
        menor = a->repeticoes;
        this->esq /*esq*/ = a;
        this->dir /*dir*/ = b;
    }
    this->repeticoes = maior + menor;
    this->digito = '\0';
    Digito *auxAnt;
    Digito *auxProx;

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

    // a->jaBuscado = true;
    // b->jaBuscado = true;
    //nArvores--;
    ////
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
    cout << "DIREITA: " << this->proximo->repeticoes << endl;
    cout << "ESQUERDA: " << this->anterior->repeticoes << endl;
    cout << "SOMA: " << this->repeticoes << endl;
}