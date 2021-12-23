#include <iostream>
#include <chrono>
#include <cstdlib>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>
#include "no.h"

using namespace std;
using namespace std::chrono;

typedef struct ver_no
{
    int chave;
    int reps = 0;
    string versao_app = "";
    ver_no *prox;
} versao;

int criaChave(char *app_version)
{
    int k = 0;
    int primP = 0;
    int secP = 0;
    if ('\0' != app_version[0])
    {
        for (int i = 0; app_version[i] != '\0'; i++)
        {
            if (app_version[i] == '.')
            {
                if (primP == 0)
                {
                    primP = i;
                }
                else
                {
                    if (secP == 0)
                    {
                        secP = i;
                    }
                }
            }
            k++;
        }

        int chave = 0;
        int posi = k - 1;

        for (int j = 0; j < k - 2; j++)
        {
            if (posi == primP || posi == secP)
            {
                posi--;
            }
            chave = chave + (((int)app_version[posi] - 48) * pow(10, j));
            posi--;
        }
        return chave;
    }
    return 0;
}

void imprimeTabela(versao **tabela, int m)
{
    for (int i = 0; i < m; i++)
    {
        cout << "[" << i << "] ";
        if (tabela[i] != NULL)
        {
            for (versao *p = tabela[i]; p != NULL; p = p->prox)
                cout << " Chave: " << p->chave << " Versao: " << p->versao_app << " --> ";
            cout << "NULL";
        }
        else
            cout << "NULL";
        cout << endl;
    }
    cout << endl;
}

versao *novoNoVersao(int chave, No *p)
{
    versao *novo = new versao;
    novo->chave = chave;
    novo->versao_app = p->app_version;
    novo->prox = NULL;
    return novo;
}

int funcaoDispersaoDivisao(int chave, int m)
{
    int posicao = chave % m;
    return posicao;
}

void insereChave(versao **tabelaHash, int m, int chave, No *aux)
{
    int h = funcaoDispersaoDivisao(chave, m);
    bool verifica = false;
    if (tabelaHash[h] == NULL)
    {
        tabelaHash[h] = novoNoVersao(chave, aux);
        tabelaHash[h]->reps = 1;
    }
    else
    {
        string compara = aux->app_version;
        for (versao *p = tabelaHash[h]; p != NULL; p = p->prox)
        {

            if (p->versao_app == compara)
            {
                p->reps = p->reps + 1;
                verifica = true;
            }
        }

        if (!verifica)
        {
            versao *novo = novoNoVersao(chave, aux);
            novo->reps = 1;
            novo->prox = tabelaHash[h];
            tabelaHash[h] = novo;
        }
    }
}

versao **criaTabela(ifstream &arqBin, int tam, int vetorId[])
{
    int m = 1087;
    versao **tabelaHash = new versao *[m];
    No *aux = new No();
    for (int u = 0; u < m; u++)
    {
        tabelaHash[u] = NULL;
    }

    for (int i = 0; i < tam; i++)
    {
        arqBin.seekg((sizeof(No)) * (vetorId[i] - 1), ios_base::beg);
        while (arqBin.read((char *)aux, sizeof(No)))
        {
            if (aux->getId() == vetorId[i])
            {

                int chave = criaChave(aux->app_version);
                insereChave(tabelaHash, m, chave, aux);
                int o = funcaoDispersaoDivisao(chave, m);
                break;
            }
        }
    }
    return tabelaHash;
}

versao *buscaIteracao(int chave, versao **tabela)
{
    int m = 1087;
    for (int i = 0; i < m; i++)
    {
        if (tabela[i] != NULL)
        {
            if (tabela[i]->prox != NULL)
            {
                for (versao *p = tabela[i]; p != NULL; p = p->prox)
                {
                    if (p->chave == chave)
                    {
                        return p;
                    }
                }
            }
            else
            {
                if (tabela[i]->chave == chave)
                {
                    return tabela[i];
                }
            }
        }
    }
    return NULL;
}
// por func de dispersão
versao *busca(int chave, versao **tabela)
{
    int m = 1087;
    int i = funcaoDispersaoDivisao(chave, m);
    if (tabela[i] != NULL)
    {
        if (tabela[i]->prox != NULL)
        {
            for (versao *p = tabela[i]; p != NULL; p = p->prox)
            {
                if (p->chave == chave)
                {
                    return p;
                }
            }
        }
        else
        {
            return tabela[i];
        }
    }
    return NULL;
}