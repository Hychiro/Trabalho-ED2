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

using namespace std;

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

    //Ordenação do Vetor
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
    string arqNome = "tiktok_app_reviews.bin";
    ifstream arqBin;
    DatabaseArquitetura dbA;
    arqBin.open(arqNome, ios::in | ios_base::binary | ios_base::app);

    int tam = 1;
    ListaDigitos a;
    cout << "Digite o Numero 1 de reviews Sorteadas: " << endl;
    int *vetorId = new int[tam];
    vetorId = sorteia(1000, tam);
    cout << "aqui 1" << endl;
    a.ConstroiLista(arqBin, vetorId, tam);
    cout << "acaba de construir a lista" << endl;
    a.ImprimeLista();

    int nArvores = a.tamanhoLista;

    Digito *vet = new Digito[nArvores];

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

    p = &vet[0];
    while (p != nullptr)
    {
        cout << p->repeticoes << endl;
        p = p->proximo;
    }
    cout << "=======================================" << endl
         << endl
         << endl;

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

    primeiro->imprimeN();

    ofstream comprimido;
    comprimido.open("comprimido.bin", ios::binary | ios::trunc);

    ListaDigitos b;
    b.constroiArquivoComprimida(arqBin, comprimido, vetorId, tam, primeiro);
    comprimido.close();
    ifstream descomprimir;
    ofstream descomprimido;
    // ifstream arqBin;
    // arqBin.open(arqNome, ios_base::binary);

    descomprimir.open("comprimido.bin", ios::in | ios_base::binary | ios_base::app);
    descomprimido.open("descomprimido.txt", ios::out);

    //pega caracteres
    descomprimir.seekg(0, descomprimir.end);
    int tamanho = descomprimir.tellg();
    descomprimir.seekg(0, descomprimir.beg);
    char *buffer = new char[tamanho];
    descomprimir.read(buffer, tamanho);

    primeiro->descomprimir(buffer, tamanho, descomprimido);
    descomprimir.close();
    descomprimido.close();
    return 0;
}
