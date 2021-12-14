#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "No.h"
#include "databaseArquitetura.h"

using namespace std;

No* countingSort(No vetorN[], int m, int tam){
    int max=9;
    m=m+1;
    int index[10];
    for (int a=0;a<10;a++){
        index[a]=0;
    }

    cout<<"Digito "<<m<<endl;

    for(int i=0;i<tam;i++)//olhar em todos structs do vetor
	{
        //for(int j=0;j<=max;j++)//olhar todos os digitos
        //{

            int digitoAnalisado =0;
            int k=0;
            while(1){

                 if(vetorN[i].upvotes[9-k] == '\0'){//se o digito que estamos for nulo aumenta k
                k=k+1;
            }else if(vetorN[i].upvotes[9-k] != '\0'){//se o digito que estamos não for nulo aumenta o digito analisado
                digitoAnalisado = digitoAnalisado+1;
            }

            if((digitoAnalisado+k)>10){//se o digito analisado for maior que 10
                index[0]=index[0]+1;//soma 1 no index[0]
                break;
            }

            if(digitoAnalisado==m){//se o digito analisado for igual ao digito que estamos procurando
                index[((int)vetorN[i].upvotes[10-(k+digitoAnalisado)]-48)]=index[((int)vetorN[i].upvotes[10-(k+digitoAnalisado)]-48)]+1;
            break;
            }

            }
        //}
    }

    for(int i=1;i<=max;i++)
	{
    index[i]=index[i-1]+index[i];
	}
    cout<<endl;
    for(int i=max;i>0;i--)
	{
    index[i]=index[i-1];
	}
    index[0]=0;
    for(int i=0;i<=max;i++)
	{
    cout<<"index "<<i<<" = "<<index[i]<<endl;
	}
    


    //ATÉ AQUI VERIFIQUEI TUDO

    No *vetorResultado=new No[tam];

    for(int i=0;i<tam;i++){//para toda struct do vetor
        //cout<<"Entrando na Posicao "<<i<<" do vetor"<<endl;
        int k=0;
        int digitoAnalisado =0;
        while(1){
            //cout<<"entra aqui"<<endl;
            
            if(vetorN[i].upvotes[9-k] == '\0'){//se o digito que estamos for nulo aumenta k
                k=k+1;
            }else if(vetorN[i].upvotes[9-k] != '\0'){//se o digito que estamos não for nulo aumenta o digito analisado
                digitoAnalisado = digitoAnalisado+1;
            }

            if((digitoAnalisado+k)>10){//se o digito analisado for maior que 10
                vetorResultado[index[0]] = vetorN[i];
                index[0]=index[0]+1;
                break;
            }

            if(digitoAnalisado==m){
                //cout<<"entra 2"<<endl;
                //cout<<index[((int)vetorN[i].upvotes[9-k]-48)]<<endl;
                //cout<<(int)(vetorN[i].upvotes[10-k])<<endl;
                int a = index[((int)vetorN[i].upvotes[10-(k+digitoAnalisado)]-48)];
                vetorResultado[a] = vetorN[i];
                //cout<<"Adicionando valor: "<<vetorN[i].upvotes<<" na pos "<<a<<endl;
                index[((int)vetorN[i].upvotes[10-(k+digitoAnalisado)]-48)]=a+1;
                //cout<<"sai 2"<<endl;
                break;
            }
        }
    }

    
    for (int a=0;a<tam;a++){
        cout<<"posicao "<<a<<" do vetor Resultado ="<<vetorResultado[a].upvotes<<endl;
    }

    return vetorResultado;
}

No* radix(int vetorId[],int tam,ifstream& arqBin){

        No *vetorStruct=new No[tam];
        No *aux = new No();
        for(int i=0;i<tam;i++){
            arqBin.seekg(((sizeof(No))*(vetorId[i]-1)), ios_base::beg);
            while (arqBin.read((char *)aux, sizeof(No)))
            {
                cout<<"loop"<<endl;
                if (aux->getId() == vetorId[i])
                {
                    vetorStruct[i]=*aux;
                    cout<<"No "<<i<<" upvotes: "<<vetorStruct[i].upvotes<<endl;
                    break;
                }
            }
        }

        int maiorDigitos=0;
cout<<endl<<endl<<endl;
        for(int i=0;i<tam;i++){
            for (int j=0;j<10;j++){
                if(vetorStruct[i].upvotes[j]!='\0'){
                    if (maiorDigitos<j){
                        maiorDigitos=j;
                    }
                }
            }
        }
        int contador =0;
        while(contador<=maiorDigitos){
            vetorStruct=countingSort(vetorStruct,contador,tam);
            contador++;
        }
        return vetorStruct;
}

/* void quickSort (int a[], int inicio, int fim)
{
    int j;
    if(inicio < fim)
    {
        j = particao(a, inicio, fim);
        quickSort(a, inicio, fim - 1);
        quickSort(a, inicio + 1, fim);
    }
}

int particao(int a[], int inicio, int fim)
{
    int v, i, j, temp;
    v = a[inicio];
    i = inicio;
    j = fim + 1;

    do
    {
        do
        {
            i++;
        }while(a[i] < v && i <= fim);
        
        do
        {
            j--;
        }while(v < a[j]);

        if(i < j)
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }

    } while(i < j);

    a[inicio] = a[j];
    a[j] = v;

    return j;
} */