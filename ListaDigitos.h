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
Digito* inicio;
Digito* fim;
int tamanhoLista;

void ConstroiLista(ifstream &arqBin,int vetorId[],int tam);
void AdicionaReview(char review[3000]);
Digito* BuscaMaisRepeticoes();
void AdicionaFimDaLista(char a);
};

#endif // LISTADIGITO_HS