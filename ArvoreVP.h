#ifndef ArvoreVP_H
#define ArvoreVP_H
#include <iostream>
#include <string>
#include "noVP.h"
#include "no.h"

using namespace std;

class ArvoreVP
{
public:

    ArvoreVP(){
        this->raiz=nullptr;
        this->Nill->cor=true;
    };
    ~ArvoreVP(){};
    noVP *raiz=new noVP;
    noVP *Nill=new noVP;
    void insere(SubNo noInserindo);
    noVP *buscaPorId(char id[90]);
    noVP *buscaPorNo(noVP no);
    void calcAlturaNegra(noVP no);
    void rotacaoSimplesEsq(noVP *no);
    void rotacaoSimplesDir(noVP *no);
    void rotacaoDuplaEsq(noVP *no);
    void rotacaoDuplaDir(noVP *no);
    void verificaQuebraDePropriedade(noVP *no);
};


#endif // ArvoreVP_HS