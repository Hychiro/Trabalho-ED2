#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "DatabaseArquitetura.cpp"
#include "DatabaseArquitetura.h"
#include <ctime>
#include "ordenacao.cpp"
#include <random>
#include <iostream>

using namespace std;



int *sorteia(int max, int n)
{
    //default_random_engine generator;
    //uniform_int_distribution<int> distribution(0, max);

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(0,max);

    srand((unsigned)time(0));

    int *vetorN = new int[n];
    for (int i = 0; i < n; i++)
    {
        vetorN[i] = 0;
    }

    if ((max / 2) < n)
    {

        int vetorInverso[max - n];
        int qtdSorteados = 0;

        while (qtdSorteados != (max - n))
        {
            cout<<"Sorteando :"<<qtdSorteados<<endl;
            bool libera = true;
            int numeroSorteado;
            while (libera)
            {
                libera = false;

                numeroSorteado = distribution(generator);

                /*for (int i = 0; i < qtdSorteados; i++)
                {
                    if (vetorInverso[i] == numeroSorteado)
                    {
                        libera = true;
                    }
                }*/
            }

            vetorInverso[qtdSorteados] = numeroSorteado;

            qtdSorteados++;
        }

        int contador = 0;

        while (contador != n)
        {
            for (int j = 0; j < max; j++)
            {
                bool pertence = true;
                int valorComparacao = j + 1;
                for (int k = 0; k < qtdSorteados; k++)
                {
                    if (valorComparacao == vetorInverso[k])
                    {
                        pertence = false;
                        break;
                    }
                }
                if (pertence)
                {
                    vetorN[contador] = valorComparacao;
                    contador++;
                }
            }
        }

        return vetorN;
    }
    else if ((max / 2) >= n)
    {

        int qtdSorteados = 0;

        while (qtdSorteados != n)
        {
            cout<<"Sorteando :"<<qtdSorteados<<endl;
            bool libera = true;
            int numeroSorteado;

            while (libera)
            {
                libera = false;

                numeroSorteado = distribution(generator);
                /*for (int o = 0; o < qtdSorteados; o++)
                {
                    if (vetorN[o] == numeroSorteado)
                    {
                        libera = true;
                    }
                }*/
            }

            vetorN[qtdSorteados] = numeroSorteado;

            qtdSorteados++;
        }

        return vetorN;
    }
    return vetorN;
}



int menu(DatabaseArquitetura dbA, ifstream& arqBin)
{
    cout << "Digite a Operacao Desejada" << endl;
    cout << "(1) acessaRegistro(i)" << endl;
    cout << "(2) testeImportacao(N)" << endl;
    cout << "(3) Limpar o console" << endl;
    cout << "(0) Fechar Programa" << endl;
    int entrada;
    cin >> entrada;
    if (entrada == 1)
    {
        cout << "Digite o i-esimo registro desejado: " << endl;
        int i;
        cin >> i;
        //le do .bin
        dbA.leituraBinarioConsole(i, arqBin);
    }

    if (entrada == 2)
    {
        cout << "Digite o Numero de Registros N que deve ser importado" << endl;
        int imp;
        cin >> imp;
        cout << "Digite (1) Para Saida em Console" << endl;
        cout << "Digite (2) Para Saida em Arquivo" << endl;
        int aux;
        cin >> aux;
        while (aux != 1 && aux != 2)
        {
            cout << "Digite uma Opcao valida!" << endl;
            cout << "Digite (1) Para Saida em Console" << endl;
            cout << "Digite (2) Para Saida em Arquivo" << endl;
            cin >> aux;
        }
        int *vetValSorteados = new int[imp];
        vetValSorteados = sorteia(dbA.getIdUltimaPosicao(arqBin), imp);
        //vetValSorteados = sorteia(200000, imp);
        SubNo *vetOrdenados = new SubNo[imp];
        vetOrdenados = radix(vetValSorteados,imp, arqBin);
        int j = 0;
        if (aux == 1)
        {
            while (j < imp)
            {
                //le do .bin
                dbA.impressaoConsole(vetOrdenados[j], arqBin);
                j++;
            }
        }
        if (aux == 2)
        {
            string nome;
            cout << "De um nome ao arquivo de saida: " << endl;
            cin >> nome;
            ofstream arqSaida;
            arqSaida.open(nome, ios::out);
            if (arqSaida.is_open())
            {
                while (j < imp)
                {
                    //le do .bin em um arquivo de saida de final a escolha (recomendo que seja .txt)
                    dbA.leArqBinarioEmArquivoTexto(arqSaida, vetValSorteados[j], arqBin);
                    j++;
                }
            }
        }

        return entrada;

    }
    if (entrada == 3)
    {
        return entrada;
    }
    if (entrada == 0)
    {
        return entrada;
    }
    return entrada;
}

int main(int argc, char const *argv[])
{

    if (argc != 2)
    {

        cout << "ERROR: Expecting: ./<program_name> <input_file> " << endl;
        return 1;
    }

    string arqNome = "tiktok_app_reviews.bin";
    ifstream arqBin;
    DatabaseArquitetura dbA;
    bool entrada = true;

    arqBin.open(arqNome, ios_base::binary );
    if (arqBin.is_open())
    {
        int selecao = 1;
        while (selecao != 0)
        {

            if (selecao == 3)
            {
                system("cls");
            }
            if (selecao == -1)
            {
                cout << "ERRO: Digite uma das opcoes dadas" << endl;
            }
            if (arqBin.is_open())
            {
                selecao = menu(dbA, arqBin);
            }
            else
            {
                cout << "ERRO: Nao foi possivel abrir" << endl;
                selecao = 0;
            }
        }
    }
   else
    {
        ofstream output_file;
        ifstream input_file;
        input_file.open(argv[1], ios::in);

        if (input_file)
        {
            output_file.open(arqNome, ios::binary | ios::trunc);
            // faz escrita do .csv para o .bin
            dbA.leituraArquivo(input_file, output_file);
        }
        else
        {
            cout << "Não foi possivel abrir" << argv[1];
            entrada = false;
        }
        //Fechando arquivo de entrada
        //Fechando arquivo de saída
        input_file.close();
        output_file.close();
        if (entrada)
        {
            arqBin.open(arqNome, ios::in | ios_base::binary | ios_base::app);
            int selecao = 1;
            while (selecao != 0)
            {

                if (selecao == 3)
                {
                    system("cls");
                }
                if (selecao == -1)
                {
                    cout << "ERRO: Digite uma das opcoes dadas" << endl;
                }
                if (arqBin.is_open())
                {
                    selecao = menu(dbA, arqBin);
                }
                else
                {
                    cout << "ERRO: Nao foi possivel abrir" << endl;
                    selecao = 0;
                }
            }
        }
    }

    arqBin.close();
    return 0;
}