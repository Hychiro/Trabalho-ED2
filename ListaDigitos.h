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
    int comparacoes;
public:
    ListaDigitos();
    Digito *inicio = new Digito();
    Digito *fim = new Digito();
    int tamanhoLista;

    void ConstroiLista(ofstream &constroiConsultaReview, ifstream &arqBin, int vetorId[], int tam);
    void AdicionaReview(char review[3000]);
    Digito *BuscaMaisRepeticoes();

    void AdicionaFimDaLista(char a);
    void AdicionaPrimeiroElemento(char a);
    void ImprimeLista();

    void apagaDaLista(Digito *a, Digito *b);

    void constroiArquivoComprimida(ifstream &arqBin, ofstream &comprimido, SubDigito *vetorDigitos, int tam);
    void adicionaCodigoDigitoComprimido(SubDigito *vetorDigitos, Digito *raiz, int tam);

    SubDigito *criaVetDigitos();

    Digito *ordenaListaDigitos();
    Digito *criaArvoreNaLista(Digito *primeiro);

    int getNumComps() { return comparacoes; };
    void setNumComps(int i) { comparacoes = i; };
};

#endif // LISTADIGITO_HS