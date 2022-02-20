#include <sstream>
#include <string>
#include "DatabaseArquitetura.h"
#include <ctime>
#include <chrono>
#include <random>
#include <iostream>
#include "Arvoreb.h"
#include "NoB.h"
#include "TreeNode.h"
#include "ArvoreVP.h"
#include "ListaDigitos.h"
#include "Digito.h"
#include "SubDigito.h"

using namespace std;
using namespace std::chrono;

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1);     // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
                                            at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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
    quickSort(vetorN, 0, n);

    return vetorN;
}

int particao(Digito *vetorStruct, int inicio, int fim, int imp)
{

    int i, j;
    Digito v, temp;
    v = vetorStruct[inicio];
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
        } while (vetorStruct[i].repeticoes < v.repeticoes && i <= fim);

        do
        {
            j--;
        } while (v.repeticoes < vetorStruct[j].repeticoes);

        if (i < j)
        {
            temp = vetorStruct[i];
            vetorStruct[i] = vetorStruct[j];
            vetorStruct[j] = temp;
        }

    } while (i < j);

    vetorStruct[inicio] = vetorStruct[j];
    vetorStruct[j] = v;

    return j;
}
void quickSort2(Digito *vetorStruct, int inicio, int fim, int imp)
{
    int j;
    if (inicio < fim)
    {
        j = particao(vetorStruct, inicio, fim, imp);
        quickSort2(vetorStruct, inicio, j - 1, imp);
        quickSort2(vetorStruct, j + 1, fim, imp);
    }
}

int main()
{
    double tempoBusca;

    string arqNome = "tiktok_app_reviews.bin";
    ifstream arqBin;
    ofstream consultaReview;
    DatabaseArquitetura dbA;
    arqBin.open(arqNome, ios::in | ios_base::binary | ios_base::app);
    consultaReview.open("arqConsulta.bin", ios::out | ios_base::binary);

    int tam = 100000;
    ListaDigitos a;

    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    cout << "Digite o Numero 1 de reviews Sorteadas: " << endl;
    int *vetorId = new int[tam];
    vetorId = sorteia(3500000, tam);

    a.ConstroiLista(consultaReview, arqBin, vetorId, tam);
    consultaReview.close();

    cout << "acaba de construir a lista" << endl;

    SubDigito *vetDigitos = new SubDigito[a.tamanhoLista];
    int tamanhoVetDigitos = a.tamanhoLista;
    int l = a.tamanhoLista - 1;
    for (Digito *g = a.inicio; g != nullptr; g = g->proximo)
    {
        SubDigito *caractere = new SubDigito();
        caractere->setCodigo("");
        caractere->setDigito(g->digito);
        vetDigitos[l] = *caractere;
        delete caractere;
        l--;
    }

    // a.ImprimeLista();
    //  for (int k = 0; k < a.tamanhoLista; k++)
    //  {
    //      cout << "Posicao " << k << " ;Digito " << vetDigitos[k].getDigito() << endl;
    //  }
    int nArvores = a.tamanhoLista;

    Digito *vet = new Digito[nArvores];

    ///////////////////////////////////////////////////////////////
    ///  func ordena lista Digitos
    Digito *p = a.inicio;
    int i = 0;
    while (p != nullptr)
    {
        vet[i] = *p;
        i++;
        p = p->proximo;
    }

    quickSort2(vet, 0, nArvores, nArvores);

    for (int j = 0; j < nArvores; j++)
    {
        if (j == 0)
        {
            vet[j].proximo = &vet[j + 1];
            vet[j].anterior = nullptr;
        }
        if (j == (nArvores - 1))
        {
            vet[j].proximo = nullptr;
            vet[j].anterior = &vet[j - 1];
        }
        else
        {
            vet[j].proximo = &vet[j + 1];
            vet[j].anterior = &vet[j - 1];
        }
    }
    /// func ordena lista digitos
    ///////////////////////////////////////////////////////////////

    // p = &vet[0];
    // while (p != nullptr)
    // {
    //     cout << p->repeticoes << endl;
    //     p = p->proximo;
    // }
    // cout << "=======================================" << endl
    //      << endl
    //      << endl;

    ////////////////////////////////////////////////////////
    ////func constroi arv
    Digito *primeiro = &vet[0];
    Digito *newPrimeiro;
    while (nArvores > 1)
    {
        Digito *aux = new Digito(primeiro, primeiro->proximo);
        p = primeiro;
        while (p != nullptr)
        {
            if (p->repeticoes >= aux->repeticoes)
            {
                Digito *ant = p->anterior;

                ant->proximo = aux;
                aux->anterior = ant;

                aux->proximo = p;
                p->anterior = aux;
                break;
            }
            else if (p->proximo == nullptr)
            {
                p->proximo = aux;
                aux->anterior = p;
                aux->proximo = nullptr;
                break;
            }
            p = p->proximo;
        }

        Digito *teste = primeiro->proximo;
        newPrimeiro = teste->proximo;
        cout << newPrimeiro->repeticoes << endl;

        a.apagaDaLista(primeiro, primeiro->proximo);
        nArvores--;

        primeiro = newPrimeiro;
    }
    cout << "FINAL: " << primeiro->repeticoes << endl;

    ////func constroi arv
    ////////////////////////////////////////////////////////
    high_resolution_clock::time_point fim = high_resolution_clock::now(); // termina o cronometro
    tempoBusca = duration_cast<duration<double>>(fim - inicio).count();

    cout << "Tempo: " << tempoBusca << endl;

    // primeiro->imprimeN();
    high_resolution_clock::time_point inicio2 = high_resolution_clock::now();
    a.adicionaCodigoDigitoComprimido(vetDigitos, primeiro, tamanhoVetDigitos);

    // for (int o = 0; o < a.tamanhoLista; o++)
    // {
    //     cout << "Posicao: " << o << " ; Digito: " << vetDigitos[o].getDigito() << " ; Codigo: " << vetDigitos[o].getCodigo() << endl;
    // }

    ofstream comprimido;
    comprimido.open("comprimido.bin", ios::binary | ios::trunc);
    ifstream consultaReview2;
    consultaReview2.open("arqConsulta.bin", ios::in | ios_base::binary | ios_base::app);

    ListaDigitos b;
    b.constroiArquivoComprimida(consultaReview2, comprimido, vetDigitos, tamanhoVetDigitos);
    comprimido.close();

    high_resolution_clock::time_point fim2 = high_resolution_clock::now(); // termina o cronometro
    tempoBusca = duration_cast<duration<double>>(fim2 - inicio2).count();

    cout << "Tempo: " << tempoBusca << endl;

    high_resolution_clock::time_point inicio3 = high_resolution_clock::now();
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

    primeiro->descomprimir(buffer, tamanho, descomprimido);
    high_resolution_clock::time_point fim3 = high_resolution_clock::now(); // termina o cronometro
    tempoBusca = duration_cast<duration<double>>(fim3 - inicio3).count();

    cout << "Tempo: " << tempoBusca << endl;
    descomprimir.close();
    descomprimido.close();
    return 0;
}
