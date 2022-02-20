#include <sstream>
#include <string>
#include "DatabaseArquitetura.h"
#include <ctime>
#include <chrono>
#include <random>
#include <iostream>
#include "ListaDigitos.h"
#include "Digito.h"

using namespace std;
using namespace std::chrono;

double mediaTempo = 0;
int mediaComp = 0;

int particao(int vetor[], int inicio, int fim, int imp)
{

    int i, j;
    int v, temp;
    v = vetor[inicio];
    i = inicio;
    j = fim + 1;
    if (j >= imp)
    {
        j = imp;
    }

    do
    {
        do
        {
            i++;
        } while (vetor[i] < v && i <= fim);

        do
        {
            j--;
        } while (v < vetor[j]);

        if (i < j)
        {
            temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
        }

    } while (i < j);

    vetor[inicio] = vetor[j];
    vetor[j] = v;

    return j;
}
void quickSort(int vetor[], int inicio, int fim, int imp)
{
    int j;
    if (inicio < fim)
    {
        j = particao(vetor, inicio, fim, imp);
        quickSort(vetor, inicio, j - 1, imp);
        quickSort(vetor, j + 1, fim, imp);
    }
}
int *sorteia(int max, int n)
{

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
        numeroSorteado = ((rand() * rand()) % max) + 1;
        vetorN[qtdSorteados] = numeroSorteado;
        qtdSorteados++;
    }

    // Ordenação do Vetor
    cout << "ordenando" << endl;
    quickSort(vetorN, 0, n, n);

    return vetorN;
}

void funcCompDecomp(int tam, int numMaxReviews, ofstream &consultaReview, ifstream &arqBin)
{
    double tempo;
    high_resolution_clock::time_point inicio1 = high_resolution_clock::now();

    /// Primeira Parte
    ListaDigitos a;
    SubDigito *vetorDigitos;
    int *vetorId = new int[tam];

    vetorId = sorteia(numMaxReviews, tam);

    a.ConstroiLista(consultaReview, arqBin, vetorId, tam);

    vetorDigitos = a.criaVetDigitos();

    consultaReview.close();
    /// Primeira Parte

    high_resolution_clock::time_point fim1 = high_resolution_clock::now();
    tempo = duration_cast<duration<double>>(fim1 - inicio1).count();
    cout << "Tempo de criacao da lista: " << tempo << endl;

    high_resolution_clock::time_point inicio2 = high_resolution_clock::now();

    /// Segunda Parte
    int tamanhoVetDigitos = a.tamanhoLista;
    Digito *primeiro = a.ordenaListaDigitos();
    Digito *raiz = a.criaArvoreNaLista(primeiro);
    /// Segunda Parte

    high_resolution_clock::time_point fim2 = high_resolution_clock::now();
    tempo = duration_cast<duration<double>>(fim2 - inicio2).count();
    cout << "Tempo de criacao da arvore e ordenacao da lista: " << tempo << endl;

    high_resolution_clock::time_point inicio3 = high_resolution_clock::now();

    /// Terceira Parte
    ofstream comprimido;
    ifstream consultaReview2;
    cout << "Comprimindo" << endl;
    comprimido.open("comprimido.bin", ios::binary | ios::trunc);
    consultaReview2.open("arqConsulta.bin", ios::in | ios_base::binary | ios_base::app);

    a.adicionaCodigoDigitoComprimido(vetorDigitos, raiz, tamanhoVetDigitos);
    a.constroiArquivoComprimida(consultaReview2, comprimido, vetorDigitos, tamanhoVetDigitos);

    comprimido.close();
    cout << "Comprimido com sucesso" << endl;
    /// Terceira Parte

    high_resolution_clock::time_point fim3 = high_resolution_clock::now();
    tempo = duration_cast<duration<double>>(fim3 - inicio3).count();
    cout << "Tempo de compressao: " << tempo << endl;

    high_resolution_clock::time_point inicio4 = high_resolution_clock::now();

    /// Quarta Parte
    cout << "Descomprimindo" << endl;
    ifstream descomprimir;
    ofstream descomprimido;

    descomprimir.open("comprimido.bin", ios::in | ios_base::binary | ios_base::app);
    descomprimido.open("descomprimido.txt", ios::out);

    ///////////////////////////////////
    ////func pega caracteres
    descomprimir.seekg(0, descomprimir.end);
    int tamanho = descomprimir.tellg();
    descomprimir.seekg(0, descomprimir.beg);
    char *buffer = new char[tamanho];
    descomprimir.read(buffer, tamanho);
    ////func pega caracteres
    ///////////////////////////////////

    raiz->descomprimir(buffer, tamanho, descomprimido);

    descomprimir.close();
    descomprimido.close();
    cout << "Descomprimido com sucesso" << endl;
    /// Quarta Parte

    high_resolution_clock::time_point fim4 = high_resolution_clock::now();
    tempo = duration_cast<duration<double>>(fim4 - inicio4).count();
    cout << "Tempo de descompressao: " << tempo << endl;
}

void modTest(int tam, int numMaxReviews, ofstream &consultaReview, ifstream &arqBin, ofstream &saida)
{
    double tempo;
    double taxaCompressao=0;
    int numComparacoes=0;
    for (int i = 0; i < 3; i++)
    {
        cout<<"Para "<<tam<<" repeticao "<<i<<endl;
        high_resolution_clock::time_point inicio1 = high_resolution_clock::now();

        /// Primeira Parte
        ListaDigitos a;
        SubDigito *vetorDigitos;
        int *vetorId = new int[tam];

        vetorId = sorteia(numMaxReviews, tam);

        a.ConstroiLista(consultaReview, arqBin, vetorId, tam);

        vetorDigitos = a.criaVetDigitos();

        consultaReview.close();

        /// Primeira Parte

        high_resolution_clock::time_point fim1 = high_resolution_clock::now();
        tempo = duration_cast<duration<double>>(fim1 - inicio1).count();
        mediaTempo = tempo + mediaTempo;

        high_resolution_clock::time_point inicio2 = high_resolution_clock::now();

        /// Segunda Parte
        int tamanhoVetDigitos = a.tamanhoLista;
        Digito *primeiro = a.ordenaListaDigitos();
        Digito *raiz = a.criaArvoreNaLista(primeiro);
        /// Segunda Parte

        numComparacoes = a.getNumComps();

        high_resolution_clock::time_point fim2 = high_resolution_clock::now();
        tempo = duration_cast<duration<double>>(fim2 - inicio2).count();
        mediaTempo = tempo + mediaTempo;

        high_resolution_clock::time_point inicio3 = high_resolution_clock::now();
        cout << "Comprimindo" << endl;
        /// Terceira Parte
        ofstream comprimido;
        ifstream consultaReview2;

        comprimido.open("comprimido.bin", ios::binary | ios::trunc);
        consultaReview2.open("arqConsulta.bin", ios::in | ios_base::binary | ios_base::app);

        a.adicionaCodigoDigitoComprimido(vetorDigitos, raiz, tamanhoVetDigitos);

        double tamOriginal = 0;
        double tamNovo = 0;
        for (int k = 0; k < tamanhoVetDigitos; k++)
        {
            if(vetorDigitos[k].getDigito()!='\0'){
            tamOriginal = (double)tamOriginal + ((double)vetorDigitos[k].getNumReps());
            tamNovo = (double)tamNovo + ((double)vetorDigitos[k].getNumReps() * (double)vetorDigitos[k].getTamCodigo());
            }
        }
        
        if(((int)tamNovo%8)==0){
            tamNovo=tamNovo/8;
        }else{
            tamNovo=(int)((tamNovo/8)+1);
        }

        taxaCompressao = taxaCompressao+(double)((tamOriginal-tamNovo)/tamOriginal);

        a.constroiArquivoComprimida(consultaReview2, comprimido, vetorDigitos, tamanhoVetDigitos);

        comprimido.close();
        cout << "Comprimido com sucesso" << endl;
        /// Terceira Parte

        high_resolution_clock::time_point fim3 = high_resolution_clock::now();
        tempo = duration_cast<duration<double>>(fim3 - inicio3).count();
        mediaTempo = tempo + mediaTempo;

        high_resolution_clock::time_point inicio4 = high_resolution_clock::now();
        cout << "Descomprimindo" << endl;
        /// Quarta Parte
        ifstream descomprimir;
        ofstream descomprimido;

        descomprimir.open("comprimido.bin", ios::in | ios_base::binary | ios_base::app);
        descomprimido.open("descomprimido.txt", ios::out);

        ///////////////////////////////////
        ////func pega caracteres
        descomprimir.seekg(0, descomprimir.end);
        int tamanho = descomprimir.tellg();
        descomprimir.seekg(0, descomprimir.beg);
        char *buffer = new char[tamanho];
        descomprimir.read(buffer, tamanho);
        ////func pega caracteres
        ///////////////////////////////////

        raiz->descomprimir(buffer, tamanho, descomprimido);

        descomprimir.close();
        descomprimido.close();
        /// Quarta Parte
        cout << "Descomprimido com sucesso" << endl;
        high_resolution_clock::time_point fim4 = high_resolution_clock::now();
        tempo = duration_cast<duration<double>>(fim4 - inicio4).count();
        mediaTempo = tempo + mediaTempo;
    }
    saida << "Tempo medio de execucao total para " << tam << ": " << mediaTempo / 3 << endl;
    saida << "Taxa de compressao media para " << tam << ": " << (double)((taxaCompressao*100)/3)<<"%" << endl;
    saida << "Numero de comparacoes media para " << tam << ": " << numComparacoes/3 << endl;
    mediaTempo = 0;
    taxaCompressao=0;
    numComparacoes=0;
}

int menu(DatabaseArquitetura dbA, ifstream &arqBin)
{
    ofstream consultaReview;
    int numMaxReviews = dbA.getIdUltimaPosicao(arqBin);
    int chaveAcesso = -1;
    while (chaveAcesso == -1)
    {
        cout << " Digite o numero respectivo do sitema utilizado:" << endl;
        cout << " Compressao/Descompressao - (1)" << endl;
        cout << " Modulo de Teste - (2)" << endl;
        cout << " Limpar Tela - (3)" << endl;
        cout << " Sair - (0)" << endl;

        cin >> chaveAcesso;
        if (chaveAcesso == 1)
        {
            // usuario digita n numeros de reviews
            int n;
            cout << "Digite o numero N de reviews sorteadas sabendo que existem no maximo ";
            cout << numMaxReviews << " reviews: " << endl;
            cin >> n;
            consultaReview.open("arqConsulta.bin", ios::out | ios_base::binary);
            funcCompDecomp(n, numMaxReviews, consultaReview, arqBin);
        }
        else if (chaveAcesso == 2)
        {
            ofstream saida;
            int valor1 = 10000;
            int valor2 = 100000;
            int valor3 = 1000000;
            saida.open("SaidaParte4.Txt", ios::out | ios_base::binary);
            consultaReview.open("arqConsulta.bin", ios::out | ios_base::binary);
            modTest(valor1, numMaxReviews, consultaReview, arqBin, saida);
            modTest(valor2, numMaxReviews, consultaReview, arqBin, saida);
            modTest(valor3, numMaxReviews, consultaReview, arqBin, saida);
        }
        else if (chaveAcesso == 3)
        {
        }
        else if (chaveAcesso == 0)
        {
        }
        else
        {
            cout << " Valor invalido! " << endl;
            chaveAcesso = -1;
        }
    }
    return chaveAcesso;
}

int main(int argc, char const *argv[])
{

    if (argc != 2)
    {

        cout << "ERROR: Expecting: ./<program_name> <input_file> " << endl;
        return 1;
    }
    int chaveSistema = -1;
    while (chaveSistema == -1)
    {
        cout << " Digite o numero respectivo do sitema utilizado:" << endl;
        cout << " Windows - (1)" << endl;
        cout << " Linux - (2)" << endl;
        cin >> chaveSistema;

        if (chaveSistema != 1 && chaveSistema != 2)
        {
            cout << " Valor invalido! Digite o numero respectivo do sitema utilizado:" << endl;
            cout << " Windows - (1)" << endl;
            cout << " Linux - (2)" << endl;
            chaveSistema = -1;
        }
    }

    string arqNome = "tiktok_app_reviews.bin";
    ifstream arqBin;
    DatabaseArquitetura dbA;
    bool entrada = true;

    arqBin.open(arqNome, ios::in | ios_base::binary);

    if (arqBin.is_open())
    {
        int selecao = 1;
        while (selecao != 0)
        {

            if (selecao == 3)
            {
                if (chaveSistema == 2)
                {
                    system("clear");
                }
                else
                {
                    system("cls");
                }
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

        arqBin.open(arqNome, ios::in | ios_base::binary | ios_base::app);
        int selecao = 1;
        while (selecao != 0)
        {

            if (selecao == 3)
            {
                if (chaveSistema == 2)
                {
                    system("clear");
                }
                else
                {
                    system("cls");
                }
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

    arqBin.close();
    return 0;
}