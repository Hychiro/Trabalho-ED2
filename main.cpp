#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "databaseArquitetura.cpp"
#include "databaseArquitetura.h"
#include <ctime>

using namespace std;

void getInfo(){
    ifstream db;
    db.open("tiktok_app_reviews.csv");

    string line;
    getline(db,line,'\n');

    getline(db,line,',');
    getline(db,line,'\n');

    int v[3];
    int n=0;

    for(int i=0; i < line.size(); i++){
        if(line[i] == ','){
            v[n%3]=i;
            n++;
        }
    }
    for(int i=0; i < v[(n-3)%3];i++){
        cout << line[i];
    }
}

int* sorteia(int max, int n){


    srand((unsigned)time(0));

    int *vetorN = new int[n];
    for(int i=0;i<n;i++){
       vetorN[i]=0; 
    }

    if((max/2)<n){
        printf("entra aqui");
        int vetorInverso[max-n];
        int qtdSorteados = 0;

        while(qtdSorteados!= (max-n))
        {
            bool libera = true;
            int numeroSorteado;

            while (libera)
            {
                libera =false;
                
                numeroSorteado = rand()%(max) + 1;

                for(int i=0;i>n;i++){
                if(vetorN[i]=numeroSorteado){
                        libera = true;
                    } 
                }
            }

        vetorInverso[qtdSorteados]=numeroSorteado;

        qtdSorteados++;
            
        }

        for(int j=0;j<qtdSorteados;j++){
            printf("Valor %d: %d\n", j,vetorInverso[j] );
        }
        int contador=0;
        while(contador!=n){
        for(int j=0;j<max;j++){
        bool pertence=true;
        int valorComparacao=j+1;
        for(int k=0;k<qtdSorteados;k++) 
            {
                if(valorComparacao==vetorInverso[k])
                    {
                    pertence=false;
                    break;
                    }
            }
        if(pertence)
            {
                vetorN[contador]=valorComparacao;
                contador++;
            }
        }
    }
        return vetorN;

    }
    else if((max/2)>=n){

        int qtdSorteados = 0;

        while(qtdSorteados!=n)
        {
            bool libera = true;
            int numeroSorteado;

            while (libera)
            {
                libera =false;
                
                numeroSorteado = rand()%(max) + 1;
                for(int o=0;o<n;o++){ 
                if(vetorN[o]==numeroSorteado){
                        libera = true;
                    } 
                }
            }

        vetorN[qtdSorteados]=numeroSorteado;

        qtdSorteados++;
            
        }

        for(int i=0;i<n;i++){
    }

        return vetorN;
    }
}


void menu(){
    printf("Digite a Operacao Desejada\n");
    printf("(1) acessaRegistro(i)\n");
    printf("(2) testeImportacao(N)\n");
    printf("(3) Fechar Programa\n");
    int entrada;
    scanf("%d", entrada);
    if(entrada==1){

    }else if (entrada==2){
        printf("Digite o Numero de Registros N que deve ser importado\n");
        int imp;
        scanf("%d", imp);
        printf("Digite (1) Para Saida em Console\n");
        printf("Digite (2) Para Saida em Arquivo\n");
        int aux;
        scanf("%d", aux);
        if(aux==1){

        } else if(aux==2){

        }else{
        printf("Digite uma Opcao valida\n");
        menu();
        }
    }else if (entrada==3){
        exit(0);
    }else{
        printf("Digite uma Opcao valida\n");
        menu();
    }
}



int main() {

    //databaseArquitetura dbA("tiktok_app_reviews.csv");

    //dbA.setReview();

    //dbA.imprimir();

    //dbA.pegaValor(7);

    int *p=sorteia(400,350);

    printf("\n\n\n\n\n");

    for(int i=0;i<350;i++){
       printf("Valor %d: %d\n", i,p[i] );
    }

    return 0;
}