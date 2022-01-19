
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
        void impressaoConsole(SubNo parametro[],ifstream& arqBin,int imp);
        void impressaoConsole(No parametro[],ifstream& arqBin,int imp);
        void setReview(ifstream& input_file,ofstream& output_file);
        void leituraArquivo(ifstream &input_file, ofstream& output_file);
        void imprimir();
        void pegaValor(int a);
        void leArqBinario();
        void leituraBinarioConsole(int iDparametro,ifstream& arqBin);
        void leArqBinarioEmArquivoTexto(ofstream &output_file, SubNo parametro[], ifstream &arqBin, int imp);
        void leArqBinarioEmArquivoTexto(ofstream &output_file, No parametro[], ifstream &arqBin, int imp);
        int getIdUltimaPosicao(ifstream& arqBin);
};


#endif // DATABASEARQUITETURA_H
