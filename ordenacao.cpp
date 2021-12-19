#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "No.h"
#include "databaseArquitetura.h"
#include <chrono>
#include <math.h>
#include "hashing.cpp"

using namespace std;
using namespace std::chrono;

SubNo *countingSort(SubNo vetorN[], int m, int tam, SubNo vetorResultado[], int maiordigitos)
{
    int max = 9;
    m = m + 1;
    int index[10];
    for (int a = 0; a < 10; a++)
    {
        index[a] = 0;
    }

    for (int i = 0; i < tam; i++) // olhar em todos structs do vetor
    {
        int digitoAnalisado = 0;
        int k = 0;
        while (1)
        {

            if (vetorN[i].upvotes[9 - k] == '\0')
            { // se o digito que estamos for nulo aumenta k
                k = k + 1;
            }
            else if (vetorN[i].upvotes[9 - k] != '\0')
            { // se o digito que estamos não for nulo aumenta o digito analisado
                digitoAnalisado = digitoAnalisado + 1;
            }

            if ((digitoAnalisado + k) > 10)
            {                            // se o digito analisado for maior que 10
                index[0] = index[0] + 1; // soma 1 no index[0]
                break;
            }

            if (digitoAnalisado == m)
            { // se o digito analisado for igual ao digito que estamos procurando
                index[((int)vetorN[i].upvotes[10 - (k + digitoAnalisado)] - 48)] = index[((int)vetorN[i].upvotes[10 - (k + digitoAnalisado)] - 48)] + 1;
                break;
            }
        }
    }

    for (int i = 1; i <= max; i++)
    {
        index[i] = index[i - 1] + index[i];
    }
    cout << endl;
    for (int i = max; i > 0; i--)
    {
        index[i] = index[i - 1];
    }
    index[0] = 0;

    for (int i = 0; i < tam; i++)
    { // para toda struct do vetor
        // cout<<"Entrando na Posicao "<<i<<" do vetor"<<endl;
        int k = 0;
        int digitoAnalisado = 0;
        while (1)
        {
            // cout<<"entra aqui"<<endl;

            if (vetorN[i].upvotes[9 - k] == '\0')
            { // se o digito que estamos for nulo aumenta k
                k = k + 1;
            }
            else if (vetorN[i].upvotes[9 - k] != '\0')
            { // se o digito que estamos não for nulo aumenta o digito analisado
                digitoAnalisado = digitoAnalisado + 1;
            }

            if ((digitoAnalisado + k) > 10)
            { // se o digito analisado for maior que 10
                vetorResultado[index[0]] = vetorN[i];
                index[0] = index[0] + 1;
                break;
            }

            if (digitoAnalisado == m)
            {
                int a = index[((int)vetorN[i].upvotes[10 - (k + digitoAnalisado)] - 48)];
                vetorResultado[a] = vetorN[i];
                index[((int)vetorN[i].upvotes[10 - (k + digitoAnalisado)] - 48)] = a + 1;
                break;
            }
        }
    }
    cout << "Digito: " << m << " de " << maiordigitos + 1 << endl;

    return vetorResultado;
}

SubNo *radix(int vetorId[], int tam, ifstream &arqBin)
{
    SubNo *vetorStruct = new SubNo[tam];
    No *aux = new No();
    cout << "Carregando upvotes dos registro" << endl;
    for (int i = 0; i < tam; i++)
    {
        arqBin.seekg((sizeof(No)) * (vetorId[i] - 1), ios_base::beg);
        while (arqBin.read((char *)aux, sizeof(No)))
        {
            if (aux->getId() == vetorId[i])
            {
                vetorStruct[i].setId(aux->getId());
                vetorStruct[i].setupvotes(aux->upvotes);
                break;
            }
        }
    }

    int maiorDigitos = 0;
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (vetorStruct[i].upvotes[j] != '\0')
            {
                if (maiorDigitos < j)
                {
                    maiorDigitos = j;
                }
            }
        }
    }
    int contador = 0;
    while (contador <= maiorDigitos)
    {
        SubNo *vetorResultado = new SubNo[tam];
        vetorStruct = countingSort(vetorStruct, contador, tam, vetorResultado, maiorDigitos);
        contador++;
    }
    return vetorStruct;
}

int *countingSortHash(int chaves[], int m, int tam,versao **tabelaHash,int resultado[])
{
    versao *aux=new versao;
    int max = 9;
    int index[10];
    for (int a = 0; a < 10; a++)
    {
        index[a] = 0;
    }

    for (int i = 0; i < tam; i++) // olhar em todos structs do vetor
    {
        int digitoAnalisado = 0;
        int k = 0;
        aux = busca(chaves[i],tabelaHash);
        int repeticao=aux->reps;
        repeticao = repeticao/pow(10,(m-1));
        repeticao = repeticao%10;

        index[repeticao]++;
        
    }

    for (int i = 1; i <= max; i++)
    {
        index[i] = index[i - 1] + index[i];
    }

    for (int i = max; i > 0; i--)
    {
        index[i] = index[i - 1];
    }
    index[0] = 0;



    

    for (int i = 0; i < tam; i++) // olhar em todos structs do vetor
    {
        int digitoAnalisado = 0;
        int k = 0;
        aux = busca(chaves[i],tabelaHash);
        int repeticao=aux->reps;
        repeticao = repeticao/pow(10,(m-1));
        repeticao = repeticao%10;

        resultado[index[repeticao]]=aux->chave;
        index[repeticao]++;

    }

    return resultado;


}

int *radix2(int chaves[], versao **tabelaHash, int tam)
{
    versao *aux=new versao;
    int maiorDigitos = 0;


    for (int i = 0; i < tam; i++)
    {
        int contaDigito=0;
        aux = busca(chaves[i],tabelaHash);
        int repeticao=aux->reps;
        do{
            repeticao=repeticao/10;
            contaDigito++;
        }while(repeticao != 0);

        if (maiorDigitos < contaDigito)
        {
            maiorDigitos = contaDigito;
        }
    }




    int contador = 1;
    while (contador <= maiorDigitos)
    {
        int *vetorResultado=new int[tam];
        chaves = countingSortHash(chaves, contador, tam,tabelaHash,vetorResultado);
        contador++;
    }

    return chaves;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//         |
//         |
// HEAPSORT V --------------------------------------------------------------------------------------------------------------------------------------------------------------------//
template <typename T>
void troca(T &a, T &b)
{
    T aux = a;
    a = b;
    b = aux;
}

void heapify(No *v, int i, int n)
{
    while (i < n)
    {
        int filho = 2 * i + 1;

        if (filho < n)
        {
            if (filho + 1 < n && atoi(v[filho + 1].upvotes) > atoi(v[filho].upvotes))
            {
                filho++;
            }
            if (atoi(v[filho].upvotes) > atoi(v[i].upvotes))
                troca(v[i], v[filho]);
        }
        i = filho;
    }
}

void constroiHeap(No *v, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(v, i, n);
    }
}

void heapSortRec(No *v, int n)
{
    constroiHeap(v, n);
    while (n > 0)
    {
        troca(v[0], v[n - 1]);
        heapify(v, 0, n - 1);
        n--;
    }
}

void heapSort(No *v, int n)
{
    high_resolution_clock::time_point inicio = high_resolution_clock::now(); // pega o tempo do inicio
    heapSortRec(v, n);
    high_resolution_clock::time_point fim = high_resolution_clock::now(); // pega o tempo do final
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << v[i].upvotes << " "; // printa o vetor de upvote em ordem crescente
    }
    cout << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl; // printa o tempo inicial - tempo final =  tempo levado
}

No *getVet(int vetorId[], int tam, ifstream &arqBin) // peguei a logica do radix pra ler o bin e salvar em struct
{
    int *v = new int[tam];
    No *vetorStruct = new No[tam];
    No *aux = new No();
    for (int i = 0; i < tam; i++)
    {
        arqBin.seekg(((sizeof(No)) * (vetorId[i] - 1)), ios_base::beg);
        while (arqBin.read((char *)aux, sizeof(No)))
        {

            if (aux->getId() == vetorId[i])
            {
                vetorStruct[i] = *aux;
                sscanf(vetorStruct[i].upvotes, "%d", &v[i]); // v[i] = (int)vetorStruct[i].upvotes --- transforma o vetor de char upvote em int pra salvar no vetor
                break;
            }
        }
    }
    // o *v agora salvou 'tam' upvotes de 0 a 'tam'
    for (int i = 0; i < tam; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    heapSort(vetorStruct, tam);

    return vetorStruct;
}
// FIM DO HEAPSORT-----------------------------------------------------------------------------------------------------------------------------------------------------------------//
// FIM DO HEAPSORT-----------------------------------------------------------------------------------------------------------------------------------------------------------------//

SubNo *criaVetSubNo(ifstream &arqBin, int vetorId[], int tam, SubNo *vetorStruct)
{
    No *aux = new No();
    cout << "Carregando upvotes dos registro" << endl;
    for (int i = 0; i < tam; i++)
    {
        arqBin.seekg((sizeof(No)) * (vetorId[i] - 1), ios_base::beg);
        while (arqBin.read((char *)aux, sizeof(No)))
        {
            if (aux->getId() == vetorId[i])
            {
                vetorStruct[i].setId(aux->getId());

                vetorStruct[i].setupvotes(aux->upvotes);
                sscanf(vetorStruct[i].upvotes, "%d", &vetorStruct[i].intUpvotes);
                break;
            }
        }
    }
    return vetorStruct;
}

int particao(SubNo *vetorStruct, int inicio, int fim)
{

    int i, j;
    SubNo v, temp;
    v = vetorStruct[inicio];
    i = inicio;
    j = fim + 1;

    do
    {
        do
        {
            i++;
        } while (vetorStruct[i].intUpvotes < v.intUpvotes && i <= fim);

        do
        {
            j--;
        } while (v.intUpvotes < vetorStruct[j].intUpvotes);

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
SubNo *quickSort(SubNo *vetorStruct, int inicio, int fim)
{

    int j, cont;
    cont = 0;
    if (inicio < fim)
    {
        j = particao(vetorStruct, inicio, fim);
        vetorStruct = quickSort(vetorStruct, inicio, j - 1);
        vetorStruct = quickSort(vetorStruct, j + 1, fim);
    }
    return vetorStruct;
}
