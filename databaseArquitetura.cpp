#include "DatabaseArquitetura.h"
#include "No.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

DatabaseArquitetura::DatabaseArquitetura()
{

}

DatabaseArquitetura::~DatabaseArquitetura()
{

}

void DatabaseArquitetura::setReview(ifstream &input_file, ofstream& output_file)
{

    string line;
    int inicialPos = 90;
    int position = 0;
    getline(input_file, line, '\n');
    //setar novo no
    No *p = new No() ;
    int quantos = 10;
    int h = 1;
    while (!input_file.eof())
    { 
        
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
        quantos--;
        output_file.write((char *)p, sizeof(No));
        h++;
    }
    this->idUltimo = h-1;
    input_file.close();
    delete p;
}
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
            output_file << aux->upvote << endl;
            output_file << endl;
            output_file << aux->version << endl;
            output_file << endl;
            output_file << aux->posted_data << endl;
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
            cout << aux->upvote << endl;
            cout << endl;
            cout << aux->version << endl;
            cout << endl;
            cout << aux->posted_data << endl;
            cout << endl;
            break;
        }
    }
}
int DatabaseArquitetura::getIdUltimaPosicao()
{
    return idUltimo;
}