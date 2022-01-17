#include <sstream>
#include <string>
#include "DatabaseArquitetura.h"
#include <ctime>
#include <chrono>
#include <random>
#include <iostream>
#include "Arvoreb.h"
#include "TreeNode.h"
#include "ArvoreVP.h"

using namespace std;
using namespace std::chrono;

double mediaTempo = 0;
int mediaComp = 0;

int *sorteia(int max, int n)
{
    srand(time(NULL));

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
        bool repete;
        //do
        //{
        //repete = false;
        //int igual = 0;
        numeroSorteado = ((rand() * rand()) % max) + 1;
        //for (int i = 0; i < qtdSorteados; i++)
        //{
        //if (numeroSorteado == vetorN[i])
        //{
        //    igual++;
        //}
        //}
        //if (igual > 0)
        //{
        //    repete = true;
        //}
        //} while (repete);
        vetorN[qtdSorteados] = numeroSorteado;
        qtdSorteados++;
    }

    return vetorN;
}

void metodosArvoreb(Arvoreb *arv, double tempo, int comparacoes, DatabaseArquitetura dbA, ifstream &arqBin)
{
    mediaTempo = mediaTempo + tempo;
    mediaComp = mediaComp + comparacoes;
    while (1)
    {
        /* code */

        cout << "Escolha o que deseja fazer NESSA Repeticao!" << endl;
        cout << "1. Modo de analise" << endl;
        cout << "2. Modo de teste" << endl;
        cout << "3. Sair" << endl;
        cout << "OBS: Ao escolher 3. Sair, a proxima repeticao sera inicializada!" << endl;
        int x;
        cin >> x;
        if (x == 1)
        {
            cout << endl;
            cout << "=========================================================================================================================" << endl;
            cout << "Relatorio:" << endl;
            cout << "Numero de comparacoes de chaves na insercao: ";
            cout << comparacoes << endl;
            cout << "Tempo decorrido para insercao: ";
            cout << tempo << endl;
            int comp = 0;
            int imp;
            imp = 100;
            int *vetValSorteados = new int[imp];
            vetValSorteados = sorteia(dbA.getIdUltimaPosicao(arqBin), imp);
            high_resolution_clock::time_point inicio = high_resolution_clock::now();
            cout << "Carregando upvotes dos registro para busca" << endl;
            int enc = 0;
            int Nenc = 0;
            for (int i = 0; i < imp; i++)
            {
                No *aux2 = new No();
                arqBin.seekg((sizeof(No)) * (vetValSorteados[i] - 1), ios_base::beg);
                while (arqBin.read((char *)aux2, sizeof(No)))
                {
                    if (aux2->getId() == vetValSorteados[i])
                    {
                        //cout << "buscando pelo id: " << aux2->review_id << "naArvore//Pos = " << aux2->getId() << endl;
                        if (arv->search(aux2->review_id, &comp) != NULL)
                        {
                            //cout << "id encontrado" << endl;
                            enc++;
                        }
                        else
                        {
                            //cout << "id nao encontrado" << endl;
                            Nenc++;
                        }
                        delete aux2;
                        break;
                    }
                }
            }
            high_resolution_clock::time_point fim = high_resolution_clock::now(); // termina o cronometro
            double tempoBusca;
            tempoBusca = duration_cast<duration<double>>(fim - inicio).count();
            cout << "Total Encontrado = " << enc << endl;
            cout << "Total Nao Encontrado = " << Nenc << endl;
            cout << "Total Comparacoes de Busca = " << comp << endl;
            cout << "Tempo de Busca = " << tempoBusca << endl;
            cout << "=========================================================================================================================" << endl;
            cout << endl;
        }
        else if (x == 2)
        {
            char a[90];
            int comparacao = 0;
            cout << "Digite o id Para Busca: " << endl;
            cout << "Exemplo de id: gp:AOqpTOEDQ9__FJihY_0V4iwqy4P2OK8tGVR1tFBixYbnsY3FmxNyewvxi4Yjd-ZCiyecVPB8MKH-DpWG5QLLnA" << endl;
            cin >> a;
            // nessa parte, provavelmente sera inserido o id de um review, entao todo o esquema feito pra definir o id na
            // hora de inserir sera igual
            // id vai precisar do tratamento para pegar pos 9+n do char id
            if (arv->search(a, &comparacao) != NULL)
            {
                cout << endl;
                cout << "=========================================================================================================================" << endl;
                cout << endl;
                cout << "id encontrado" << endl;
                cout << endl;
                cout << "=========================================================================================================================" << endl;
                cout << endl;
            }
            else
            {
                cout << endl;
                cout << "=========================================================================================================================" << endl;
                cout << endl;
                cout << "id nao encontrado" << endl;
                cout << endl;
                cout << "=========================================================================================================================" << endl;
                cout << endl;
            }
        }
        else if (x == 3)
        {
            return;
        }
        else
        {
            cout << "valor invalido" << endl;
        }
    }
}

void InsereNosArvoreb(Arvoreb *arv, DatabaseArquitetura dbA, ifstream &arqBin)
{
    cout << "ultima pos = " << dbA.getIdUltimaPosicao(arqBin) << endl;
    int imp = 1000000; //<---- tem q ser 1MILHAO ======================
    //cin >> imp;
    int *vetValSorteados = new int[imp];

    vetValSorteados = sorteia(dbA.getIdUltimaPosicao(arqBin), imp);          // precisa ser feito
    high_resolution_clock::time_point inicio = high_resolution_clock::now(); // começa o cronometro
    int comparacoes = 0;

    cout << "Carregando upvotes dos registro" << endl;
    for (int i = 0; i < imp; i++)
    {
        No *aux = new No();
        arqBin.seekg((sizeof(No)) * (vetValSorteados[i] - 1), ios_base::beg);
        while (arqBin.read((char *)aux, sizeof(No)))
        {
            if (aux->getId() == vetValSorteados[i])
            {
                No p = *aux;
                //cout << "id: " << i << " -- " << p.review_id << endl;

                arv->insert(p.review_id, p, &comparacoes);

                delete aux;
                break;
            }
        }
    }

    high_resolution_clock::time_point fim = high_resolution_clock::now(); // termina o cronometro
    double tempo;
    tempo = duration_cast<duration<double>>(fim - inicio).count();
    metodosArvoreb(arv, tempo, comparacoes, dbA, arqBin);
}

void menuArvoreb(DatabaseArquitetura dbA, ifstream &arqBin)
{
    int ordem;
    int escolha = 0;
    cout << "Escolha o que deseja fazer" << endl;
    cout << "1. Modo de Ordem 20" << endl;
    cout << "2. Modo de Ordem 200" << endl;
    cout << "3. Sair" << endl;
    cin >> escolha;
    while (escolha != 3)
    {
        if (escolha == 1)
        {
            ordem = 20;

            for (int i = 0; i < 3; i++)
            {
                cout << "================================ Arvore de ordem 20 ===== Repeticao " << i + 1 << " ================================" << endl;
                Arvoreb *arv = new Arvoreb(ordem);  // cria a arvore B com a ordem passada
                InsereNosArvoreb(arv, dbA, arqBin); // monta a arvore a partir da leitura do arquivo
                delete arv;
                cout << "=============================================================================================" << endl;
            }
            cout << "Media de tempo: " <<mediaTempo/3 << endl;
            cout << "Media de comparacoes: " <<mediaComp/3 << endl;
        }
        else if (escolha == 2)
        {
            ordem = 200;
            for (int i = 0; i < 3; i++)
            {
                cout << "=============================== Arvore de ordem 200 ===== Repeticao " << i + 1 << " ===============================" << endl;
                Arvoreb *arv = new Arvoreb(ordem);  // cria a arvore B com a ordem passada
                InsereNosArvoreb(arv, dbA, arqBin); // monta a arvore a partir da leitura do arquivo
                delete arv;
                cout << "=============================================================================================" << endl;
            }
            cout << "Media de tempo: " <<mediaTempo/3 << endl;
            cout << "Media de comparacoes: " <<mediaComp/3 << endl;
        }
        else
        {
            cout << "Digite uma alternativa valida! " << endl;
        }
        mediaComp = 0;
        mediaTempo = 0;
        cout << "Escolha o que deseja fazer" << endl;
        cout << "1. Modo de Ordem 20" << endl;
        cout << "2. Modo de Ordem 200" << endl;
        cout << "3. Sair" << endl;
        cin >> escolha;
    }
    return;
}

void menuArvoreVP2(DatabaseArquitetura dbA, ifstream &arqBin)
{
    cout << "ultima pos = " << dbA.getIdUltimaPosicao(arqBin) << endl;
    cout << "Digite o Numero de Registros N que deve ser importado" << endl;
    int imp;
    cin >> imp;
    int *vetValSorteados = new int[imp];
    vetValSorteados = sorteia(dbA.getIdUltimaPosicao(arqBin), imp);

    ArvoreVP *vp = new ArvoreVP;
    vp->criaArvore(vetValSorteados, imp, arqBin);

    cout << "Arvore VP Criada com Sucesso" << endl;
    cout << endl;
    cout << "Digite (1) Para Realizar uma busca" << endl;
    cout << "Digite Qualquer Outro Numero Para Sair e Apagar a Arvore" << endl;

    int imp2;
    cin >> imp2;

    while (imp2 == 1)
    {
        char a[90];
        cout << "Digite o id Para Busca: " << endl;
        cout << "Exemplo de id: gp:AOqpTOEDQ9__FJihY_0V4iwqy4P2OK8tGVR1tFBixYbnsY3FmxNyewvxi4Yjd-ZCiyecVPB8MKH-DpWG5QLLnA" << endl;
        cin >> a;
        if (vp->buscaPorId(a) != -1)
        {
            cout << "id encontrado" << endl;
        }
        else
        {
            cout << "id nao encontrado" << endl;
        }

        cout << "Digite (1) Para Realizar uma busca" << endl;
        cout << "Digite Qualquer Outro Numero Para Sair e Apagar a Arvore" << endl;
        cin >> imp2;
    }
    delete vp;
    return;
}

void menuArvoreVP(DatabaseArquitetura dbA, ifstream &arqBin)
{
    for (int i = 0; i < 3; i++)
    {
        cout << "==========================================================================" << endl;
        cout << "ultima pos = " << dbA.getIdUltimaPosicao(arqBin) << endl;
        int imp = 1000000;
        int *vetValSorteados = new int[imp];
        vetValSorteados = sorteia(dbA.getIdUltimaPosicao(arqBin), imp);
        ArvoreVP *vp = new ArvoreVP;

        high_resolution_clock::time_point inicio = high_resolution_clock::now();
        vp->criaArvore(vetValSorteados, imp, arqBin);
        high_resolution_clock::time_point fim = high_resolution_clock::now(); // termina o cronometro
        double tempo;
        tempo = duration_cast<duration<double>>(fim - inicio).count();

        cout << "Tempo de insercao: " << tempo << endl;

        cout << "Total de comparacao ao Inserir: " << vp->comparacaoIns << endl;
        imp = 100;
        int *vetValSorteados2 = new int[imp];
        vetValSorteados2 = sorteia(dbA.getIdUltimaPosicao(arqBin), imp);
        high_resolution_clock::time_point inicio2 = high_resolution_clock::now();
        vp->MetodoBusca(vetValSorteados2, imp, arqBin);
        high_resolution_clock::time_point fim2 = high_resolution_clock::now(); // termina o cronometro
        tempo = duration_cast<duration<double>>(fim2 - inicio2).count();
        cout << "Tempo de Busca: " << tempo << endl;
        cout << "Total de comparacao ao Buscar: " << vp->comparacaoBus << endl;
        delete vp;
    }
}

int menuArvores(DatabaseArquitetura dbA, ifstream &arqBin)
{

    cout << "Escolha qual metodo usar" << endl;
    cout << "1. Arvore Vermelho-Preto" << endl;
    cout << "2. Arvore B" << endl;
    cout << "3. Limpar a tela" << endl;
    cout << "4. Sair" << endl;
    int x, y;
    cin >> x;
    switch (x)
    {
    case 1:

        cout << "Escolha entre o modo" << endl;
        cout << "1. Modo de analise" << endl;
        cout << "2. Modo de teste" << endl;
        cout << "3. Sair" << endl;
        cin >> y;
        while (y != 3)
        {
            if (y == 1)
            {
                menuArvoreVP(dbA, arqBin);
            }
            if (y == 2)
            {
                menuArvoreVP2(dbA, arqBin);
                
            }else{
                 cout << "Valor Invalido!" << endl;
            }

            cout << "Escolha entre o modo" << endl;
            cout << "1. Modo de analise" << endl;
            cout << "2. Modo de teste" << endl;
            cout << "3. Sair" << endl;
            cin >> y;
        }

        break;
    case 2:
        menuArvoreb(dbA, arqBin);
        break;
    case 3:
        break;
    case 4:
        return 0;
        break;
    }
    if (x < 1 || x > 4)
    {
        cout << "Valor Invalido!" << endl;
        return -1;
    }
    return x;
}

// int menu(DatabaseArquitetura dbA, ifstream &arqBin)
// {
//     cout << "Digite a Operacao Desejada" << endl;
//     cout << "(1) acessaRegistro(i)" << endl;
//     cout << "(2) Ordenacao" << endl;
//     cout << "(3) Hash" << endl;
//     cout << "(4) Modulo de Teste" << endl;
//     cout << "(5) ArvoreVP" << endl;
//     cout << "(6) ArvoreB" << endl;
//     cout << "(7) Limpar o console" << endl;
//     cout << "(0) Fechar Programa" << endl;
//     int entrada;
//     cin >> entrada;
//     if (entrada == 1)
//     {
//         cout << "Digite o i-esimo registro desejado: " << endl;
//         int i;
//         cin >> i;
//         // le do .bin
//         dbA.leituraBinarioConsole(i, arqBin);
//     }

//     if (entrada == 2)
//     {
//         cout << "Digite (1) Para Saida em Console" << endl;
//         cout << "Digite (2) Para Saida em Arquivo" << endl;
//         int aux;
//         cin >> aux;
//         string nome;
//         ofstream arqSaida;

//         while (aux != 1 && aux != 2)
//         {
//             cout << "Digite uma Opcao valida!" << endl;
//             cout << "Digite (1) Para Saida em Console" << endl;
//             cout << "Digite (2) Para Saida em Arquivo" << endl;
//             cin >> aux;
//         }
//         if (aux == 2)
//         {
//             cout << "De um nome ao arquivo de saida: " << endl;
//             cin >> nome;
//             arqSaida.open(nome, ios::out);
//         }
//         cout << "Qual tipo de Sort usar?" << endl;
//         cout << "Digite (1) para RadixSort" << endl;
//         cout << "Digite (2) para HeapSort" << endl;
//         cout << "Digite (3) para QuickSort" << endl;
//         int type;
//         cin >> type;
//         while (type != 1 && type != 2 && type != 3)
//         {
//             cout << "Digite uma Opcao valida!" << endl;
//             cout << "Digite (1) para RadixSort" << endl;
//             cout << "Digite (2) para HeapSort" << endl;
//             cout << "Digite (3) para QuickSort" << endl;
//             cin >> type;
//         }

//         cout << "Digite o Numero de Registros N que deve ser importado" << endl;
//         int imp;
//         cin >> imp;
//         int *vetValSorteados = new int[imp];
//         vetValSorteados = sorteia(dbA.getIdUltimaPosicao(arqBin), imp);
//         if (aux == 1)
//         {

//             // Selecionar tipo de ordenação _INICIO
//             SubNo *vetOrdenados = new SubNo[imp];
//             if (type == 1)
//                 vetOrdenados = radix(vetValSorteados, imp, arqBin);
//             if (type == 2)
//                 vetOrdenados = getVet(vetValSorteados, imp, arqBin);
//             if (type == 3)
//             {
//                 vetOrdenados = criaVetSubNo(arqBin, vetValSorteados, imp, vetOrdenados);
//                 high_resolution_clock::time_point inicio = high_resolution_clock::now();
//                 quickSort(vetOrdenados, 0, imp, imp);
//                 int tempo = 0;
//                 high_resolution_clock::time_point fim = high_resolution_clock::now();
//                 tempo = duration_cast<duration<double>>(fim - inicio).count();
//                 cout << "Tempo  de ordenação: " << tempo << " segundos" << endl;
//             }
//             // Selecionar tipo de ordenação _FIM
//             // Impressão
//             dbA.impressaoConsole(vetOrdenados, arqBin, imp);

//             delete[] vetValSorteados;
//             delete[] vetOrdenados;
//         }
//         if (aux == 2)
//         {
//             SubNo *vetOrdenados = new SubNo[imp];

//             if (type == 1)
//                 vetOrdenados = radix(vetValSorteados, imp, arqBin);
//             if (type == 2)
//                 vetOrdenados = getVet(vetValSorteados, imp, arqBin);
//             if (type == 3)
//             {
//                 vetOrdenados = criaVetSubNo(arqBin, vetValSorteados, imp, vetOrdenados);
//                 high_resolution_clock::time_point inicio = high_resolution_clock::now();
//                 quickSort(vetOrdenados, 0, imp, imp);
//                 double tempo = 0;
//                 high_resolution_clock::time_point fim = high_resolution_clock::now();
//                 tempo = duration_cast<duration<double>>(fim - inicio).count();
//                 cout << "Tempo  de ordenação: " << tempo << " segundos" << endl;
//                 imprimeTC();
//             }
//             if (arqSaida.is_open())
//             {
//                 // le do .bin em um arquivo de saida de final a escolha (recomendo que seja .txt)

//                 dbA.leArqBinarioEmArquivoTexto(arqSaida, vetOrdenados, arqBin, imp);

//                 delete[] vetValSorteados;
//                 delete[] vetOrdenados;
//             }
//             else
//             {
//                 cout << "ERRO NA ESCRITA EM ARQUIVO" << endl;
//             }
//         }

//         return entrada;
//     }
//     if (entrada == 3)
//     {
//         cout << "Digite o Numero de Registros N que deve ser importado" << endl;
//         int imp;
//         cin >> imp;
//         int *vetValSorteados = new int[imp];
//         vetValSorteados = sorteia(dbA.getIdUltimaPosicao(arqBin), imp);
//         versao **tabela = criaTabela(arqBin, imp, vetValSorteados);
//         // imprimeTabela(tabela, 1087);

//         int m = 1087;
//         int chaves[m * 2];
//         for (int i = 0; i < (m * 2); i++)
//         {
//             chaves[i] = -1;
//         }

//         int next = 0;
//         for (int j = 0; j < m; j++)
//         {
//             if (tabela[j] != NULL)
//             {
//                 if (tabela[j]->prox != NULL)
//                 {
//                     for (versao *p = tabela[j]; p != NULL; p = p->prox)
//                     {
//                         chaves[next] = p->chave;
//                         next++;
//                     }
//                 }
//                 else
//                 {
//                     chaves[next] = tabela[j]->chave;
//                     next++;
//                 }
//             }
//         }
//         int tam = next;
//         int *resultado = new int[tam];
//         for (int i = 0; i < tam; i++)
//         {
//             resultado[i] = chaves[i];
//         }
//         resultado = radix2(resultado, tabela, tam);

//         int quantidade;
//         cout << "sabendo que existem " << tam << " versoes, de uma quantidade de versoes: " << endl;
//         cin >> quantidade;

//         for (int i = tam - 1; i >= tam - quantidade; i--)
//         {
//             cout << "Versao : " << busca(resultado[i], tabela)->versao_app << "      Repeticoes : " << busca(resultado[i], tabela)->reps << endl;
//         }

//         return entrada;
//     }
//     if (entrada == 4)
//     {
//         string nome;
//         ofstream arqSaida;

//         cout << "De um nome ao arquivo de saida: " << endl;
//         cin >> nome;
//         arqSaida.open(nome, ios::out);

//         int imp = 100;
//         int *vetValSorteados = new int[imp];
//         vetValSorteados = sorteia(dbA.getIdUltimaPosicao(arqBin), imp);

//         SubNo *vetOrdenados = new SubNo[imp];
//         SubNo *vetOrdenados2 = new SubNo[imp];
//         SubNo *vetOrdenados3 = new SubNo[imp];

//         arqSaida << "Radix" << endl;
//         /// radix
//         vetOrdenados = radix(vetValSorteados, imp, arqBin);

//         dbA.leArqBinarioEmArquivoTexto(arqSaida, vetOrdenados, arqBin, imp);
//         delete[] vetOrdenados;
//         arqSaida << "==========================================================================================" << endl
//                  << endl;
//         arqSaida << "HeapSort" << endl;
//         /// heap
//         vetOrdenados2 = getVet(vetValSorteados, imp, arqBin);

//         dbA.leArqBinarioEmArquivoTexto(arqSaida, vetOrdenados2, arqBin, imp);
//         delete[] vetOrdenados2;
//         arqSaida << "==========================================================================================" << endl
//                  << endl;
//         arqSaida << "QuickSort" << endl;
//         /// quick
//         vetOrdenados3 = criaVetSubNo(arqBin, vetValSorteados, imp, vetOrdenados3);
//         quickSort(vetOrdenados3, 0, imp, imp);

//         dbA.leArqBinarioEmArquivoTexto(arqSaida, vetOrdenados3, arqBin, imp);
//         delete[] vetOrdenados3;
//         arqSaida << "==========================================================================================" << endl
//                  << endl;
//         arqSaida << "Hashing" << endl;
//         /// hash
//         versao **tabela = criaTabela(arqBin, imp, vetValSorteados);
//         // imprimeTabela(tabela, 1087);
//         int m = 1087;
//         int chaves[m * 2];
//         for (int i = 0; i < (m * 2); i++)
//         {
//             chaves[i] = -1;
//         }

//         int next = 0;
//         for (int j = 0; j < m; j++)
//         {
//             if (tabela[j] != NULL)
//             {
//                 if (tabela[j]->prox != NULL)
//                 {
//                     for (versao *p = tabela[j]; p != NULL; p = p->prox)
//                     {
//                         chaves[next] = p->chave;
//                         next++;
//                     }
//                 }
//                 else
//                 {
//                     chaves[next] = tabela[j]->chave;
//                     next++;
//                 }
//             }
//         }
//         int tam = next;
//         int *resultado = new int[tam];
//         for (int i = 0; i < tam; i++)
//         {
//             resultado[i] = chaves[i];
//         }
//         resultado = radix2(resultado, tabela, tam);
//         for (int i = tam - 1; i >= 0; i--)
//         {
//             arqSaida << "Versao : " << busca(resultado[i], tabela)->versao_app << " --- Repeticoes : " << busca(resultado[i], tabela)->reps << endl;
//         }
//         system("cls");
//         delete[] vetValSorteados;
//         arqSaida.close();
//         return entrada;
//     }
//     if (entrada == 5)
//     {
//         cout << "ultima pos = " << dbA.getIdUltimaPosicao(arqBin) << endl;
//         cout << "Digite o Numero de Registros N que deve ser importado" << endl;
//         int imp;
//         cin >> imp;
//         int *vetValSorteados = new int[imp];
//         vetValSorteados = sorteia(dbA.getIdUltimaPosicao(arqBin), imp);
//         ArvoreVP *vp = new ArvoreVP;
//         vp->criaArvore(vetValSorteados, imp, arqBin);
//         cout << "Total de comparacao ao Inserir: " << vp->comparacaoIns << endl;
//         cout << "Digite o Numero de Registros N que deve ser buscado" << endl;
//         cin >> imp;
//         int *vetValSorteados2 = new int[imp];
//         vetValSorteados2 = sorteia(dbA.getIdUltimaPosicao(arqBin), imp);
//         vp->MetodoBusca(vetValSorteados2, imp, arqBin);
//         cout << "Total de comparacao ao Buscar: " << vp->comparacaoBus << endl;
//         cin >> imp;
//     }
//     if (entrada == 6)
//     {
//         return entrada;
//     }
//     if (entrada == 0)
//     {
//         return entrada;
//     }
//     return entrada;
// }

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

            if (selecao == 3)
            {
                system("cls");
                system("cls");
            }
            if (selecao == -1)
            {
                cout << "ERRO: Digite uma das opcoes dadas" << endl;
            }
            if (arqBin.is_open())
            {
                selecao = menuArvores(dbA, arqBin);
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
                    selecao = menuArvores(dbA, arqBin);
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