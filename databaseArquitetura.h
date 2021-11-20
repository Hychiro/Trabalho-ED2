
#ifndef DATABASEARQUITETURA_H
#define DATABASEARQUITETURA_H
#include <iostream>
#include <string>
#include "No.h"

using namespace std;

class DatabaseArquitetura
{
    public:
        DatabaseArquitetura();
        ~DatabaseArquitetura();
        void setReview(ifstream& input_file);
        void imprimir();
        void pegaValor(int a);
        void escreveArqBin(ofstream &output_file);
        void leArqBinario();
        void leituraBinarioConsole(int iDparametro);
        void leArqBinarioEmArquivoTexto(ofstream &output_file, int iDparametro);
        int getIdUltimaPosicao();
    private:
        No *primeiro;
        No *ultimo;
};


#endif // DATABASEARQUITETURA_H