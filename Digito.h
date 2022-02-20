#ifndef DIGITO_H
#define DIGITO_H
#include <iostream>
#include <string>

using namespace std;

class Digito
{
public:
    Digito(Digito *a, Digito *b);
    Digito();
    ~Digito();

    char digito;
    int repeticoes;
    bool jaBuscado;
    Digito *proximo;
    Digito *anterior;
    Digito *esq;
    Digito *dir;

    void imprime();
    void imprimeN();
    void imprimePorNivel(Digito *p, int nivel);

    void comprime(char dig, ofstream &comprimido);
    void auxComprime(Digito *p, char dig, string text, bool *encontrou, ofstream &comprimido);
    void descomprimir(char *buffer, int tamanho, ofstream &descomprimido);
    void auxDescomprimir(Digito *p, char *buffer, int* i, ofstream &descomprimido);
};

#endif // DIGITO_HS