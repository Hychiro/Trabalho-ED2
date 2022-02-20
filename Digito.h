#ifndef DIGITO_H
#define DIGITO_H
#include <iostream>
#include <string>
#include "SubDigito.h"

using namespace std;

class Digito
{
public:
    Digito(Digito *a, Digito *b);
    Digito();
    ~Digito();

    char digito;
    int repeticoes;
    Digito *proximo;
    Digito *anterior;
    Digito *esq;
    Digito *dir;

    void imprime();
    void imprimeN();
    void imprimePorNivel(Digito *p, int nivel);

    void comprime(SubDigito* subDigito, int* compara);
    void auxComprime(Digito *p, char dig, string text, bool *encontrou, SubDigito* subDigito, int *compara);


    void descomprimir(char *buffer, int tamanho, ofstream &descomprimido);
    void auxDescomprimir(Digito *p, char *buffer, int* i, ofstream &descomprimido);
};


#endif // DIGITO_H