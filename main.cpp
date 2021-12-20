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
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(1, max);

    cout << "Sorteando" << endl;

    int *vetorN = new int[n];
    for (int i = 0; i < n; i++)
    {
        vetorN[i] = 0;
    }
    int qtdSorteados = 0;
    while (qtdSorteados != n)
    {
        int numeroSorteado;
        numeroSorteado = distribution(generator);
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
        // le do .bin
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
        cout << "Digite (3) para QuickSort" << endl;
        int type;
        cin >> type;
        while (type != 1 && type != 2 && type != 3)
        {
            cout << "Digite uma Opcao valida!" << endl;
            cout << "Digite (1) para RadixSort" << endl;
            cout << "Digite (2) para HeapSort" << endl;
            cout << "Digite (3) para QuickSort" << endl;
            cin >> type;
        }

        cout << "Digite o Numero de Registros N que deve ser importado" << endl;
        int imp;
        cin >> imp;
        int *vetValSorteados = new int[imp];
        vetValSorteados = sorteia(dbA.getIdUltimaPosicao(arqBin), imp);
        if (aux == 1)
        {
            // Selecionar tipo de ordenação _INICIO
            srand(time(nullptr));
            high_resolution_clock::time_point inicio = high_resolution_clock::now();
            SubNo *vetOrdenados = new SubNo[imp];
            if (type == 1)
                vetOrdenados = radix(vetValSorteados, imp, arqBin);
            if (type == 2)
                vetOrdenados = getVet(vetValSorteados, imp, arqBin);
            if (type == 3)
            {
                vetOrdenados = criaVetSubNo(arqBin, vetValSorteados, imp, vetOrdenados);
                // vetOrdenados = quickSort(vetOrdenados, 0, imp);
                recursiveQsort(vetOrdenados, 0, imp);
                // for (int k = 0; k < imp; k++)
                // {
                //     cout << "vetorStruct[k]: " << vetOrdenados[k].getId() << vetOrdenados[k].intUpvotes << " -- " << vetOrdenados[k].upvotes << endl;
                // }
            }
            // Selecionar tipo de ordenação _FIM
            int tempo = 0;
            high_resolution_clock::time_point fim = high_resolution_clock::now();
            tempo = duration_cast<duration<double>>(fim - inicio).count();
            cout<<"Tempo  de ordenação: "<<tempo<< " segundos"<<endl;
            // Impressão
            dbA.impressaoConsole(vetOrdenados, arqBin, imp);

            delete[] vetValSorteados;
            delete[] vetOrdenados;
        }
        if (aux == 2)
        {
            SubNo *vetOrdenados = new SubNo[imp];

            srand(time(nullptr));
            high_resolution_clock::time_point inicio = high_resolution_clock::now();
            if (type == 1)
                vetOrdenados = radix(vetValSorteados, imp, arqBin);
            if (type == 2)
                vetOrdenados = getVet(vetValSorteados, imp, arqBin);
            if (type == 3)
            {
                vetOrdenados = criaVetSubNo(arqBin, vetValSorteados, imp, vetOrdenados);
                // vetOrdenados = quickSort(vetOrdenados, 0, imp);
                recursiveQsort(vetOrdenados, 0, imp);
            }
            double tempo = 0;
            high_resolution_clock::time_point fim = high_resolution_clock::now();
            tempo = duration_cast<duration<double>>(fim - inicio).count();
            cout<<"Tempo  de ordenação: "<<tempo<< " segundos"<<endl;
            if (arqSaida.is_open())
            {
                // le do .bin em um arquivo de saida de final a escolha (recomendo que seja .txt)

                if (type == 1 || type == 2)
                    dbA.leArqBinarioEmArquivoTexto(arqSaida, vetOrdenados, arqBin, imp);
                if (type == 3)
                    dbA.leArqBinarioEmArquivoTexto2(arqSaida, vetOrdenados, arqBin, imp);

            delete[] vetValSorteados;
            delete[] vetOrdenados;
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
        // imprimeTabela(tabela, 1087);

        int m = 1087;
        int chaves[m * 2];
        for (int i = 0; i < (m * 2); i++)
        {
            chaves[i] = -1;
        }

        int next = 0;
        for (int j = 0; j < m; j++)
        {
            if (tabela[j] != NULL)
            {
                if (tabela[j]->prox != NULL)
                {
                    for (versao *p = tabela[j]; p != NULL; p = p->prox)
                    {
                        chaves[next] = p->chave;
                        next++;
                    }
                }
                else
                {
                    chaves[next] = tabela[j]->chave;
                    next++;
                }
            }
        }

        int nulos = 0;
        for (int i = 0; i < (m * 2); i++)
        {
            if (chaves[i] == -1)
            {
                nulos++;
            }
        }
        int tam = ((m * 2) - nulos);
        int *resultado = new int[tam];
        for (int i = 0; i < tam; i++)
        {
            resultado[i] = chaves[i];
        }
        resultado = radix2(resultado, tabela, tam);

        int quantidade;
        cout << "sabendo que existem " << tam << " versoes, de uma quantidade de versoes: " << endl;
        cin >> quantidade;

        for (int i = tam - 1; i >= tam - quantidade; i--)
        {
            cout << "Versao : " << busca(resultado[i], tabela)->versao_app << "      Repeticoes : " << busca(resultado[i], tabela)->reps << endl;
        }

        return entrada;
    }
    if (entrada == 4)
    {
        string nome;
        ofstream arqSaida;

        cout << "De um nome ao arquivo de saida: " << endl;
        cin >> nome;
        arqSaida.open(nome, ios::out);

        int imp = 100;
        int *vetValSorteados = new int[imp];
        vetValSorteados = sorteia(dbA.getIdUltimaPosicao(arqBin), imp);

        SubNo *vetOrdenados = new SubNo[imp];
        SubNo *vetOrdenados2 = new SubNo[imp];
        SubNo *vetOrdenados3 = new SubNo[imp];


        arqSaida<<"Radix"<<endl;
        ///radix
        vetOrdenados = radix(vetValSorteados, imp, arqBin);

        dbA.leArqBinarioEmArquivoTexto(arqSaida, vetOrdenados, arqBin, imp);
        delete[] vetOrdenados;
        arqSaida<<endl<<endl;
        arqSaida<<"HeapSort"<<endl;
        ///heap
        vetOrdenados2 = getVet(vetValSorteados, imp, arqBin);

        dbA.leArqBinarioEmArquivoTexto(arqSaida, vetOrdenados2, arqBin, imp);
        delete[] vetOrdenados2;
        arqSaida<<endl<<endl;
        arqSaida<<"QuickSort"<<endl;
        ///quick
        vetOrdenados3 = criaVetSubNo(arqBin, vetValSorteados, imp, vetOrdenados3);
        // vetOrdenados3 = quickSort(vetOrdenados3, 0, imp);
        recursiveQsort(vetOrdenados, 0, imp);

        dbA.leArqBinarioEmArquivoTexto(arqSaida, vetOrdenados3, arqBin, imp);
        delete[] vetOrdenados3;
        arqSaida<<endl<<endl;
        arqSaida<<"Hashing"<<endl;
        ///hash
        versao **tabela = criaTabela(arqBin, imp, vetValSorteados);
        // imprimeTabela(tabela, 1087);
        int m = 1087;
        int chaves[m * 2];
        for (int i = 0; i < (m * 2); i++)
        {
            chaves[i] = -1;
        }

        int next = 0;
        for (int j = 0; j < m; j++)
        {
            if (tabela[j] != NULL)
            {
                if (tabela[j]->prox != NULL)
                {
                    for (versao *p = tabela[j]; p != NULL; p = p->prox)
                    {
                        chaves[next] = p->chave;
                        next++;
                    }
                }
                else
                {
                    chaves[next] = tabela[j]->chave;
                    next++;
                }
            }
        }

        int nulos = 0;
        for (int i = 0; i < (m * 2); i++)
        {
            if (chaves[i] == -1)
            {
                nulos++;
            }
        }
        int tam = ((m * 2) - nulos);
        int *resultado = new int[tam];
        for (int i = 0; i < tam; i++)
        {
            resultado[i] = chaves[i];
        }
        resultado = radix2(resultado, tabela, tam);

        for (int i = tam - 1; i >= 0; i--)
        {
            arqSaida << "Versao : " << busca(resultado[i], tabela)->versao_app << " --- Repeticoes : " << busca(resultado[i], tabela)->reps << endl;
        }

        delete[] vetValSorteados;
        arqSaida.close();
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
        // Fechando arquivo de entrada
        // Fechando arquivo de saída
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