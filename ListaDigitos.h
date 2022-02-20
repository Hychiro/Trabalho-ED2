#ifndef LISTADIGITOS_H
#define LISTADIGITOS_H
#include <iostream>
#include <string>
#include "Digito.h"
#include <fstream>
#include <sstream>
#include "SubDigito.h"

using namespace std;

class ListaDigitos
{
public:
    ListaDigitos();
    Digito *inicio = new Digito();
    Digito *fim = new Digito();
    int tamanhoLista;

    void ConstroiLista(ofstream &constroiConsultaReview, ifstream &arqBin, int vetorId[], int tam);
    void AdicionaReview(char review[3000]);
    Digito *BuscaMaisRepeticoes();
    void AdicionaFimDaLista(char a);
    void ImprimeLista();

    void apagaDaLista(Digito *a, Digito *b);

    void constroiArquivoComprimida(ifstream &arqBin, ofstream &comprimido, SubDigito *vetorDigitos, int tam);
    void adicionaCodigoDigitoComprimido(SubDigito *vetorDigitos, Digito *raiz, int tam);
};

#endif // LISTADIGITO_HS