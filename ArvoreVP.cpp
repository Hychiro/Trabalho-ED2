#include <iostream>
#include <string>
#include "noVP.h"
#include "ArvoreVP.h"
#include "no.h"

using namespace std;

void ArvoreVP::insere(SubNo noInserindo)
{

    
}

void ArvoreVP::calcAlturaNegra(noVP no)//hiero faz?
{
    
}

noVP *ArvoreVP::buscaPorId(char id[90])
{
    noVP *atual=new noVP;
    atual=this->raiz;

    while(1){
        if(comparacaoiDigualB(id,atual)){
            break;
        }

        if(atual==nullptr){
            return nullptr;
        }

        if(comparacaoiDmaiorB(id,atual)){
            atual=atual->dir;
        }else{
            atual=atual->esq;
        }

    }

    return atual;
}

noVP *ArvoreVP::buscaPorNo(noVP no)
{
    noVP *atual=new noVP;
    atual=this->raiz;

    while(1){
        if(comparacaoiDigualB(no.review_id,atual)){
            break;
        }

        if(atual==nullptr){
            return nullptr;
        }

        if(comparacaoiDmaiorB(no.review_id,atual)){
            atual=atual->dir;
        }else{
            atual=atual->esq;
        }

    }

    return atual;
}

void ArvoreVP::verificaQuebraDePropriedade(noVP *no)
{ // verifica se existe caso 1,2 ou 3

if(this->raiz->cor==false){
this->raiz->cor=true;
}
noVP *pai=new noVP;
noVP *tio=new noVP;
noVP *avo=new noVP;
bool paiDirAvo=false;
bool noDirPai=false;
pai=no->pai;

if (pai==this->Nill)
{
    return;
}

avo=pai->pai;

if (avo==this->Nill)
{
    return;
}


if(avo->esq==pai){
tio=avo->dir;
}else if(avo->dir==pai){
tio=avo->esq; 
paiDirAvo=true;
}

if(pai->esq==no){

}else if(pai->dir==no){
noDirPai=true;
}



if(pai->cor==false && tio->cor==false){
    trocaCor(pai);
    trocaCor(tio);
    trocaCor(avo);

    verificaQuebraDePropriedade(avo);
    //delete pai;
    //delete tio;
    //delete avo;
    return;
}

if(pai->cor==false && tio->cor==true){
    if (paiDirAvo)
    {
        if(!noDirPai){
            rotacaoDuplaEsq(no);
            trocaCor(no);
            trocaCor(avo);
        }
        if (noDirPai)
        {
            rotacaoSimplesEsq(no);
            trocaCor(pai);
            trocaCor(avo);
        }
        
    }

    if (!paiDirAvo)
    {
        if(noDirPai){
            rotacaoDuplaDir(no);
            trocaCor(no);
            trocaCor(avo);
        }
        if (!noDirPai)
        {
            rotacaoSimplesDir(no);
            trocaCor(pai);
            trocaCor(avo);
        }
        
    }
    

}

}

void trocaCor(noVP *no)
{

if(no->cor==false){
    no->cor=true;
}

if (no->cor==true)
{
    no->cor=false;
}


}

void ArvoreVP::rotacaoSimplesDir(noVP *no)//verificar
{
    noVP *pai=new noVP;
    noVP *avo=new noVP;
    pai=no->pai;
    avo=pai->pai;

    pai->dir=avo;//passa o avo para a esquerda do pai
    pai->pai=avo->pai;//oq esta no topo do avo passa para o topo do pai
    avo->pai=pai;//o topo do avo passa a ser o pai

    //delete pai;
    //delete avo;
}

void ArvoreVP::rotacaoSimplesEsq(noVP *no)//verificar
{
    noVP *pai=new noVP;
    noVP *avo=new noVP;
    pai=no->pai;
    avo=pai->pai;

    pai->esq=avo;//passa o avo para a esquerda do pai
    pai->pai=avo->pai;//oq esta no topo do avo passa para o topo do pai
    avo->pai=pai;//o topo do avo passa a ser o pai

    //delete pai;
    //delete avo;
}

void ArvoreVP::rotacaoDuplaDir(noVP *no)//verificar
{
    noVP *pai=new noVP;
    noVP *avo=new noVP;
    pai=no->pai;
    avo=pai->pai;

    no->dir=avo;//o  pai  passa  a ser o filho do no
    no->esq=pai;//o avo passa a serr o filho  do  no

    //ajeitando o pai
    pai->pai=no;//o pai do pai passa a ser o no
    pai->dir=this->Nill;

    //ajeitando o avo
    avo->pai=no;
    avo->esq=this->Nill;

    //delete pai;
    //delete avo;
}

void ArvoreVP::rotacaoDuplaEsq(noVP *no)//verificar
{
    noVP *pai=new noVP;
    noVP *avo=new noVP;
    pai=no->pai;
    avo=pai->pai;

    no->esq=avo;//o  pai  passa  a ser o filho do no
    no->dir=pai;//o avo passa a serr o filho  do  no

    //ajeitando o pai
    pai->pai=no;//o pai do pai passa a ser o no
    pai->esq=this->Nill;

    //ajeitando o avo
    avo->pai=no;
    avo->dir=this->Nill;
    

    //delete pai;
    //delete avo;
}

bool comparacaoAmaiorB(noVP noA, noVP noB)
{ // retornar Maior
    int n = 0;
    char a, b;
    while (1)
    {
        a = noA.review_id[9 + n];
        b = noB.review_id[9 + n];

        if (a == b)
        {
            n++;
        }

        if (a != b)
        {
            break;
        }
    }

    if ((int)a > (int)b)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool comparacaoAmenorB(noVP noA, noVP noB)
{ // retorna menor
    int n = 0;
    char a, b;
    while (1)
    {
        a = noA.review_id[9 + n];
        b = noB.review_id[9 + n];

        if (a == b)
        {
            n++;
        }

        if (a != b)
        {
            break;
        }
    }

    if ((int)a > (int)b)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool comparacaoiDmaiorB(char noA[], noVP *noB)
{ // retornar Maior
    int n = 0;
    char a, b;
    while (1)
    {
        a = noA[9 + n];
        b = noB->review_id[9 + n];

        if (a == b)
        {
            n++;
        }

        if (a != b)
        {
            break;
        }
    }

    if ((int)a > (int)b)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool comparacaoiDmenorB(char noA[], noVP *noB)
{ // retornar Maior
    int n = 0;
    char a, b;
    while (1)
    {
        a = noA[9 + n];
        b = noB->review_id[9 + n];

        if (a == b)
        {
            n++;
        }

        if (a != b)
        {
            break;
        }
    }

    if ((int)a > (int)b)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool comparacaoiDigualB(char noA[], noVP *noB)
{ // retornar Maior
    int n = 0;
    char a, b;
    while (n<90)
    {
        a = noA[n];
        b = noB->review_id[n];

        if (a == b)
        {
            n++;
        }

        if (a != b)
        {
            return false;
        }
    }
    return true;
}
