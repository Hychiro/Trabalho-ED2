#include "DatabaseArquitetura.h"
#include "No.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;
DatabaseArquitetura::DatabaseArquitetura()
{
}

DatabaseArquitetura::~DatabaseArquitetura()
{
}

void DatabaseArquitetura::leituraArquivo(ifstream &input_file, ofstream &output_file)
{
    string linhaArqivo;
    string linhaReview = "";
    int repetidor = 1;
    getline(input_file, linhaArqivo, '\n');
    while (!input_file.eof())
    {
        if (repetidor == 1)
        {
            getline(input_file, linhaArqivo, '\n');
        }
        cout << repetidor << endl;

        No *p = new No();

        string review_id = "";
        string review_text = "";
        string upvotes = "";
        string app_version = "";
        string date = "";
        string hour = "";

        while (!input_file.eof())
        {
            int inicio = linhaArqivo.find("gp:AOqpTO");
            if (inicio != string::npos)
            {
                linhaReview = "";
                linhaReview = linhaArqivo;
            }
            else
            {
                linhaReview = linhaReview + linhaArqivo;
            }
            getline(input_file, linhaArqivo, '\n');
            inicio = linhaArqivo.find("gp:AOqpTO");
            if (inicio != string::npos)
            {
                break;
            }
        }

        for (int i = 0; i < 3000; i++)
        {

            p->review_text[i] = '\0';
        }

        for (int i = 0; i < 30; i++)
        {
            p->app_version[i] = '\0';
            p->date[i] = '\0';
            p->hour[i] = '\0';
        }
        for (int i = 0; i < 10; i++)
        {
            p->upvotes[i] = '\0';
        }
        for (int i = 0; i < 90; i++)
        {
            p->review_id[i] = '\0';
        }

        string::size_type position;
        int inicio = linhaReview.find("gp:AOqpTO");

        int separador1 = linhaReview.find_first_of(",");

        int separador4 = linhaReview.find_last_of(",");

        int separador3 = linhaReview.find_last_of(",", separador4 - 1);

        int separador2 = linhaReview.find_last_of(",", separador3 - 1);

        int separador5 = linhaReview.find_last_of(" ");

        if (inicio == string::npos || separador1 == string::npos || separador2 == string::npos || separador3 == string::npos || separador4 == string::npos)
        {
            cout << "ERRO NA LEITURA DO ARQUIVO EM TEXTO LINHA: " << repetidor << endl;
        }
        int j = 0;
        for (int i = inicio; i < separador1; i++)
        {
            p->review_id[j] = linhaReview[i];
            j++;
        }
        j = 0;
        for (int i = separador1 + 1; i < separador2; i++)
        {

            p->review_text[j] = linhaReview[i];
            j++;
        }
        j = 0;
        for (int i = separador2 + 1; i < separador3; i++)
        {
            p->upvotes[j] = linhaReview[i];
            j++;
        }
        j = 0;
        for (int i = separador3 + 1; i < separador4; i++)
        {
            p->app_version[j] = linhaReview[i];
            j++;
        }
        j = 0;
        for (int i = separador4 + 1; i < separador5; i++)
        {
            p->date[j] = linhaReview[i];
            j++;
        }
        j = 0;
        for (int i = separador5 + 1; i < linhaReview.size(); i++)
        {
            p->hour[j] = linhaReview[i];
            j++;
        }

        p->setId(repetidor);
        output_file.write((char *)p, sizeof(No));

        delete p;
        repetidor++;
    }
}

void DatabaseArquitetura::leArqBinarioEmArquivoTexto(ofstream &output_file, int iDparametro, ifstream &arqBin)
{
    No *aux = new No();
    //fstream arqBin("tiktok_app_reviews.bin", ios_base::in | ios_base::binary | ios_base::app);
    arqBin.seekg(0, ios_base::beg);
    while (arqBin.read((char *)aux, sizeof(No)))
    {

        if (aux->getId() == iDparametro)
        {
            output_file << aux->review_id << endl;
            output_file << endl;
            output_file << aux->review_text << endl;
            output_file << endl;
            output_file << aux->upvotes << endl;
            output_file << endl;
            output_file << aux->app_version << endl;
            output_file << endl;
            output_file << aux->date << endl;
            output_file << endl;
            output_file << aux->hour << endl;
            output_file << endl;
            break;
        }
    }
}

void DatabaseArquitetura::impressaoConsole(No parametro,ifstream& arqBin){
            cout << parametro.review_id << endl;
            cout << endl;
            cout << parametro.review_text << endl;
            cout << endl;
            cout << parametro.upvotes << endl;
            cout << endl;
            cout << parametro.app_version << endl;
            cout << endl;
            cout << parametro.date << endl;
            cout << endl;
            cout << parametro.hour << endl;
            cout << endl;
}

void DatabaseArquitetura::leituraBinarioConsole(int iDparametro,ifstream& arqBin)
{

    No *aux = new No();
    //fstream arq("tiktok_app_reviews.bin", ios_base::in | ios_base::binary | ios_base::app);
    arqBin.seekg(0, ios_base::beg);
    cout << "iDparametro" << iDparametro << endl;
    while (arqBin.read((char *)aux, sizeof(No)))
    {
        if (aux->getId() == iDparametro)
        {

            cout << aux->review_id << endl;
            cout << endl;
            cout << aux->review_text << endl;
            cout << endl;
            cout << aux->upvotes << endl;
            cout << endl;
            cout << aux->app_version << endl;
            cout << endl;
            cout << aux->date << endl;
            cout << endl;
            cout << aux->hour << endl;
            cout << endl;
            break;
        }
    }
}
int DatabaseArquitetura::getIdUltimaPosicao(ifstream &arqBin)
{
    No *aux = new No();
    arqBin.seekg(-(sizeof(No)), ios::end);
    arqBin.read((char *)aux, sizeof(No));

    return aux->getId();
}