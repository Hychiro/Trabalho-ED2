#ifndef ArvoreVP_H
#define ArvoreVP_H
#include <iostream>
#include <string>
#include "noVP.h"
#include "No.h"

using namespace std;

class ArvoreVP
{
public:

    ArvoreVP();
    ~ArvoreVP();
    int comparacaoIns;
    int comparacaoBus;


    noVP *raiz=new noVP;
    noVP *Nill=new noVP;

    noVP *Libera(noVP *no);
    void insere(No *noInserindo);
    int buscaPorId(char id[90]);
    void MetodoBusca(int vetorId[], int tam, ifstream &arqBin);
    void verificaRaiz(noVP *no);
    void rotacaoSimplesEsq(noVP *no,noVP *pai,noVP *avo);
    void rotacaoSimplesDir(noVP *no,noVP *pai,noVP *avo);
    void rotacaoDuplaEsq(noVP *no,noVP *pai,noVP *avo);
    void rotacaoDuplaDir(noVP *no,noVP *pai,noVP *avo);
    void verificaQuebraDePropriedade(noVP *no);
    bool comparacaoAmaiorB(noVP* noA, noVP *noB);
    bool comparacaoAmenorB(noVP* noA, noVP *noB);
    bool comparacaoiDmaiorB(char noA[], noVP *noB);
    bool comparacaoiDmenorB(char noA[], noVP *noB);
    bool comparacaoiDigualB(char noA[], noVP *noB);
    void trocaCor(noVP *no);
    noVP *SubNoParanoVP(No *noInserindo);
    void criaArvore(int vetorId[], int tam, ifstream &arqBin);
    void ImprimeArvore(noVP *no, int i);
};


#endif // ArvoreVP_HS