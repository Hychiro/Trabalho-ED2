#ifndef LISTADIGITOS_H
#define LISTADIGITOS_H
#include <iostream>
#include <string>
#include "Digito.h"
#include <fstream>
#include <sstream>

using namespace std;

class ListaDigitos
{
public:
    ListaDigitos();
    Digito* inicio= new Digito();
    Digito* fim= new Digito();
    int tamanhoLista;

    void ConstroiLista(ofstream &consultaReview, ifstream &arqBin,int vetorId[],int tam);
    void AdicionaReview(char review[3000],ofstream &consultaReview);
    Digito* BuscaMaisRepeticoes();
    void AdicionaFimDaLista(char a);
    void ImprimeLista();

    void apagaDaLista(Digito *a, Digito *b);

    void constroiArquivoComprimida(ifstream &arqBin, ofstream &comprimido, int vetorId[], int tam, Digito *raiz);
    void adicionaReviewComprimido(char review[3000], ofstream &comprimido, Digito *raiz);
};

#endif // LISTADIGITO_HS