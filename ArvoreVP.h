#ifndef ArvoreVP_H
#define ArvoreVP_H
#include <iostream>
#include <string>
#include "NoVP.h"
#include "No.h"

using namespace std;

class ArvoreVP
{
public:

    ArvoreVP();
    ~ArvoreVP();
    int comparacaoIns;
    int comparacaoBus;


    NoVP *raiz=new NoVP;
    NoVP *Nill=new NoVP;

    NoVP *Libera(NoVP *no);
    void insere(No *noInserindo);
    int buscaPorId(char id[90]);
    void MetodoBusca(int vetorId[], int tam, ifstream &arqBin);
    void verificaRaiz(NoVP *no);
    void rotacaoSimplesEsq(NoVP *no,NoVP *pai,NoVP *avo);
    void rotacaoSimplesDir(NoVP *no,NoVP *pai,NoVP *avo);
    void rotacaoDuplaEsq(NoVP *no,NoVP *pai,NoVP *avo);
    void rotacaoDuplaDir(NoVP *no,NoVP *pai,NoVP *avo);
    void verificaQuebraDePropriedade(NoVP *no);
    bool comparacaoAmaiorB(NoVP* noA, NoVP *noB);
    bool comparacaoAmenorB(NoVP* noA, NoVP *noB);
    bool comparacaoiDmaiorB(char noA[], NoVP *noB);
    bool comparacaoiDmenorB(char noA[], NoVP *noB);
    bool comparacaoiDigualB(char noA[], NoVP *noB);
    void trocaCor(NoVP *no);
    NoVP *SubNoParanoVP(No *noInserindo);
    void criaArvore(int vetorId[], int tam, ifstream &arqBin);
    void ImprimeArvore(NoVP *no, int i);
};


#endif // ArvoreVP_H