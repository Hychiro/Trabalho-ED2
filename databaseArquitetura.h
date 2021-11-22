
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
        void setReview(ifstream& input_file,ofstream& output_file);
        void leituraArquivo(ifstream &input_file, ofstream& output_file);
        void imprimir();
        void pegaValor(int a);
        void leArqBinario();
        void leituraBinarioConsole(int iDparametro,ifstream& arqBin);
        void leArqBinarioEmArquivoTexto(ofstream &output_file, int iDparametro,ifstream& arqBin);
        int getIdUltimaPosicao(ifstream& arqBin);
};


#endif // DATABASEARQUITETURA_H