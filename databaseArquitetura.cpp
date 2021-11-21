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
    string linha;
    int repetidor = 1;
    getline(input_file, linha, '\n');
    while (repetidor != 10)
    {
        getline(input_file, linha, '\n');
        cout << repetidor << endl;

        No *p = new No();

        string review_id = "";
        string review_text = "";
        string upvotes = "";
        string app_version = "";
        string date = "";
        string hour = "";
        
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
        int inicio = linha.find("gp:AOqpTO");

        int separador1 = linha.find_first_of(",");

        int separador4 = linha.find_last_of(",");

        int separador3 = linha.find_last_of(",", separador4 - 1);

        int separador2 = linha.find_last_of(",", separador3 - 1);

        int separador5 = linha.find_last_of(" ");

        if (inicio == string::npos || separador1 == string::npos || separador2 == string::npos || separador3 == string::npos || separador4 == string::npos)
        {
            cout << "ERRO NA LEITURA DO ARQUIVO EM TEXTO LINHA: " << repetidor << endl;
        }
        int j = 0;
        for (int i = inicio; i < separador1; i++)
        {
            p->review_id[j] = linha[i];
            j++;
        }
        j = 0;
        for (int i = separador1 + 1; i < separador2; i++)
        {

            p->review_text[j] = linha[i];
            j++;
        }
        j = 0;
        for (int i = separador2 + 1; i < separador3; i++)
        {
            p->upvotes[j] = linha[i];
            j++;
        }
        j = 0;
        for (int i = separador3 + 1; i < separador4; i++)
        {
            p->app_version[j] = linha[i];
            j++;
        }
        j = 0;
        for (int i = separador4 + 1; i < separador5; i++)
        {
            p->date[j] = linha[i];
            j++;
        }
        j = 0;
        for (int i = separador5 + 1; i < linha.size(); i++)
        {
            p->hour[j] = linha[i];
            j++;
        }

        p->setId(repetidor);
        output_file.write((char *)p, sizeof(No));

        delete p;
        repetidor++;
    }
}

/*void DatabaseArquitetura::setReview(ifstream &input_file, ofstream& output_file)
{

    string line;
    int inicialPos = 90;
    int position = 0;
    getline(input_file, line, '\n');
    //setar novo no
    int h = 1;
    while (!input_file.eof())
    { 
        No *p = new No() ;
        cout << h << endl;

        p->setId(h);

        getline(input_file, line, '\n');

        position = line.size();
        for (int i = 0; i < 89; i++)
        {
            p->review_id[i] = line[i];
        }
        p->review_id[90] = '\n';

        int v[3];
        int n = 0;

        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == ',')
            {
                v[n % 3] = i;
                n++;
            }
        }
        int vMenor = 10000;
        for (int i = 0; i < 3; i++)
        {
            if (v[i] < vMenor)
                vMenor = v[i];
        }

        int rev_text_index = 0;
        int lengthAux = position - vMenor;
        for (int i = 90; i < position - lengthAux; i++)
        {
            p->review_text[rev_text_index] = line[i];
            rev_text_index++;
        }
        int controlador = 0;
        string str = "";
        for (int i = v[(n - 3) % 3] + 1; i <= line.size(); i++)
        {
            str = str + line[i];
            if (line[i] == ',' || line[i] == '\n' || i == line.size())
            {
                if (controlador == 0)
                {
                    stringstream ss;
                    ss << str;
                    ss >> p->upvote;
                    str = "";
                }
                else if (controlador == 1)
                {
                    for (int j = 0; j < str.length() - 1; j++) //<-- POSSIVEL ERRO NO LENGTH
                    {
                        p->version[j] = str[j];
                    }
                    str = "";
                }
                else if (controlador == 2)
                {
                    for (int j = 0; j < str.length() - 1; j++) //<-- POSSIVEL ERRO NO LENGTH
                    {
                        p->posted_data[j] = str[j];
                    }
                }
                controlador++;
            }
        }
        output_file.write((char *)p, sizeof(No));
        delete p;
        h++;
    }
    this->idUltimo = h-1;
    input_file.close();
}*/

/*
void DatabaseArquitetura::imprimir()
{
    cout << "upvote do primeiro: ";
    cout << primeiro->upvote << endl;
    cout << "upvote do ultimo: ";
    cout << ultimo->upvote << endl;
    cout << "pegar o segundo valor usando o proximo do primeiro: ";
    cout << primeiro->proximo->upvote << endl;
    cout << "pegar o segundo valor usando o anterior do ultimo: ";
    cout << ultimo->anterior->upvote << endl;
}
*/
/*void DatabaseArquitetura::pegaValor(int a)
{
    int aux = 0;
    No *p = primeiro;
    while (aux < a - 1)
    {
        p = p->proximo;

        aux++;
    }
    cout << "Upvotes do no " << a << " eh: " << p->upvote << endl;
}*/

void DatabaseArquitetura::leArqBinarioEmArquivoTexto(ofstream &output_file, int iDparametro)
{
    No *aux = new No();
    fstream arq("tiktok_app_reviews.bin", ios_base::in | ios_base::binary | ios_base::app);
    arq.seekg(0, ios_base::beg);
    cout << "parametro " << iDparametro << endl;
    while (arq.read((char *)aux, sizeof(No)))
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

void DatabaseArquitetura::leituraBinarioConsole(int iDparametro)
{

    No *aux = new No();
    fstream arq("tiktok_app_reviews.bin", ios_base::in | ios_base::binary | ios_base::app);
    arq.seekg(0, ios_base::beg);
    cout << "parametro " << iDparametro << endl;
    while (arq.read((char *)aux, sizeof(No)))
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
int DatabaseArquitetura::getIdUltimaPosicao()
{
    return idUltimo;
}