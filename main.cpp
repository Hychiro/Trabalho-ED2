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
#include "hashing.cpp"

using namespace std;

int *sorteia(int max, int n)
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(0,max);

    cout<<"Sorteando"<<endl;

    int *vetorN = new int[n];
    for (int i = 0; i < n; i++)
    {
        vetorN[i] = 0;
    }
        int qtdSorteados = 0;
        while (qtdSorteados != n)
        {
            int numeroSorteado;
            bool libera = true;
            while (libera)
            {
                libera = false;

                numeroSorteado = distribution(generator);
                for (int o = 0; o < qtdSorteados; o++)
                {
                    if (vetorN[o] == numeroSorteado)
                    {
                        libera = true;
                    }
                }
            }
            vetorN[qtdSorteados] = numeroSorteado;
            qtdSorteados++;
        }

    return vetorN;
}

int menu(DatabaseArquitetura dbA, ifstream &arqBin)
{
    cout << "Digite a Operacao Desejada" << endl;
    cout << "(1) acessaRegistro(i)" << endl;
    cout << "(2) Ordenacao" << endl;
    cout << "(3) Hash" << endl;
    cout << "(4) Modulo de Teste" << endl;
    cout << "(5) Limpar o console" << endl;
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
        cout << "Digite (1) Para Saida em Console" << endl;
        cout << "Digite (2) Para Saida em Arquivo" << endl;
        int aux;
        cin >> aux;
        string nome;
        ofstream arqSaida;

        while (aux != 1 && aux != 2)
        {
            cout << "Digite uma Opcao valida!" << endl;
            cout << "Digite (1) Para Saida em Console" << endl;
            cout << "Digite (2) Para Saida em Arquivo" << endl;
            cin >> aux;
        }
        if (aux == 2)
        {
            cout << "De um nome ao arquivo de saida: " << endl;
            cin >> nome;
            arqSaida.open(nome, ios::out);
        }
        cout << "Qual tipo de Sort usar?" << endl;
        cout << "Digite (1) para RadixSort" << endl;
        cout << "Digite (2) para HeapSort" << endl;
        int type;
        cin >> type;
        while (type != 1 && type != 2)
        {
            cout << "Digite uma Opcao valida!" << endl;
            cout << "Digite (1) para RadixSort" << endl;
            cout << "Digite (2) para HeapSort" << endl;
            cin >> type;
        }

        cout << "Digite o Numero de Registros N que deve ser importado" << endl;
        int imp;
        cin >> imp;
        int *vetValSorteados = new int[imp];
        vetValSorteados = sorteia(dbA.getIdUltimaPosicao(arqBin), imp);
        if (aux == 1)
        {
            //Selecionar tipo de ordenação _INICIO
            srand(time(nullptr));
            high_resolution_clock::time_point inicio = high_resolution_clock::now();
            SubNo *vetOrdenados = new SubNo[imp];
            No *vetOrdenados2 = new No[imp];
            if (type == 1)
                vetOrdenados = radix(vetValSorteados, imp, arqBin);
            if (type == 2)
                vetOrdenados2 = getVet(vetValSorteados, imp, arqBin);
            //Selecionar tipo de ordenação _FIM
            int tempo = 0;
            high_resolution_clock::time_point fim = high_resolution_clock::now();
            tempo = duration_cast<duration<double>>(fim - inicio).count();
            //Impressão
            dbA.impressaoConsole(vetOrdenados, arqBin, imp);
            delete[] vetValSorteados;
            delete[] vetOrdenados;
            delete[] vetOrdenados2;
        }
        if (aux == 2)
        {
            SubNo *vetOrdenados = new SubNo[imp];
            No *vetOrdenados2 = new No[imp];
            srand(time(nullptr));
            high_resolution_clock::time_point inicio = high_resolution_clock::now();
            if (type == 1)
                vetOrdenados = radix(vetValSorteados, imp, arqBin);
            if (type == 2)
                vetOrdenados2 = getVet(vetValSorteados, imp, arqBin);
            int tempo = 0;
            high_resolution_clock::time_point fim = high_resolution_clock::now();
            tempo = duration_cast<duration<double>>(fim - inicio).count();
            if (arqSaida.is_open())
            {
                //le do .bin em um arquivo de saida de final a escolha (recomendo que seja .txt)
                dbA.leArqBinarioEmArquivoTexto(arqSaida, vetOrdenados, arqBin, imp);
            }
            else
            {
                cout << "ERRO NA ESCRITA EM ARQUIVO" << endl;
            }
        }

        return entrada;
    }
    if (entrada == 3)
    {
        cout << "Digite o Numero de Registros N que deve ser importado" << endl;
        int imp;
        cin >> imp;
        int *vetValSorteados = new int[imp];
        vetValSorteados = sorteia(dbA.getIdUltimaPosicao(arqBin), imp);

        versao **tabela = criaTabela(arqBin, imp, vetValSorteados); 

        imprimeTabela(tabela, 1087);
          

        return entrada;
    }
    if (entrada == 4)
    {
        return entrada;
    }
    if (entrada == 5)
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

    arqBin.open(arqNome, ios_base::binary);
    if (arqBin.is_open())
    {
        int selecao = 1;
        while (selecao != 0)
        {

            if (selecao == 5)
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