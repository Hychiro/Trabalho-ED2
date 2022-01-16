#include <iostream>
#include <string>
#include "noVP.h"
#include "ArvoreVP.h"
#include "no.h"

using namespace std;

ArvoreVP::ArvoreVP()
{
    Nill->cor = true;
    char a[90] = "";
    Nill->setreview_id(a);
    Nill->setId(-1);
    raiz = Nill;
    raiz->pai = Nill;
}

ArvoreVP::~ArvoreVP() {}

void ArvoreVP::ImprimeArvore(noVP *no){
    if(no->getId()>0){
    cout<<no->getId()<<" -- ";
    ImprimeArvore(no->esq);
    ImprimeArvore(no->dir);
    }
}

void ArvoreVP::criaArvore(int vetorId[], int tam, ifstream &arqBin)
{
    cout << "Carregando upvotes dos registro" << endl;
    for (int i = 0; i < tam; i++)
    {
        No *aux = new No();
        arqBin.seekg((sizeof(No)) * (vetorId[i] - 1), ios_base::beg);
        while (arqBin.read((char *)aux, sizeof(No)))
        {
            if (aux->getId() == vetorId[i])
            {
                cout << i << " -- " << aux->getId() << endl;
                this->insere(aux);
                //cout << "passa do insere" << endl;
                 delete aux;
                break;
            }
        }
    }
}

void ArvoreVP::insere(No *noInserindo)
{
    verificaRaiz(raiz);

    noVP *noNovo = new noVP;
    noNovo = SubNoParanoVP(noInserindo);

    if (raiz->getId() == Nill->getId())
    {

        this->raiz = noNovo;
        this->raiz->pai = this->Nill;
        verificaQuebraDePropriedade(noNovo);
        //cout << "adicionou a raiz" << endl;
        return;
    }

    noVP *noPai = new noVP;
    noPai = this->raiz;
    noVP *noAnalisado = new noVP;
    noAnalisado = this->raiz;
    bool add_esq;

    while (1)
    {
        //cout << "noAnalisado->getId():   " << noAnalisado->getId() << endl;
        if (noAnalisado->getId() == Nill->getId())
        {
            break;
        }

        if (comparacaoAmaiorB(noAnalisado, noNovo))
        {
            //cout << "entra no if" << endl;
            noPai = noAnalisado;
            noAnalisado = noAnalisado->esq;
            add_esq = true;
        }
        else
        {
            //cout << "entra no else" << endl;
            noPai = noAnalisado;
            noAnalisado = noAnalisado->dir;
            add_esq = false;
        }
    }

    if (add_esq)
    {
        //cout << "adicionou na esq" << endl;
        noPai->esq = noNovo;
        noNovo->pai = noPai;
        noNovo->esq = Nill;
        noNovo->dir = Nill;
    }
    else
    {
        //cout << "adicionou na dir" << endl;
        noPai->dir = noNovo;
        noNovo->pai = noPai;
        noNovo->esq = Nill;
        noNovo->dir = Nill;
    }

    verificaQuebraDePropriedade(noNovo);

    verificaRaiz(raiz);

    cout<<"Imprimindo Arvore"<<endl;
    ImprimeArvore(raiz);
    cout<<endl;

    return;
}

noVP *ArvoreVP::SubNoParanoVP(No *noInserindo)
{
    noVP *no = new noVP;
    no->cor = false;
    no->dir = this->Nill;
    no->esq = this->Nill;
    no->pai = this->Nill;
    for (int i = 0; i < 90; i++)
    {
        no->review_id[i] = noInserindo->review_id[i];
    }
    no->setId(noInserindo->getId());

    return no;
}

void ArvoreVP::verificaRaiz(noVP *no) 
{
    while (1)
    {
        if (no->pai->getId() == -1)
        {
            this->raiz = no;
            break;
        }
        else
        {
            no = no->pai;
        }
    }
}

void ArvoreVP::MetodoBusca(int vetorId[], int tam, ifstream &arqBin)
{
    cout << "Carregando upvotes dos registro para busca" << endl;
    int enc=0;
    int Nenc=0;
    for (int i = 0; i < tam; i++)
    {
        No *aux2 = new No();
        arqBin.seekg((sizeof(No)) * (vetorId[i] - 1), ios_base::beg);
        while (arqBin.read((char *)aux2, sizeof(No)))
        {
            if (aux2->getId() == vetorId[i])
            {
                cout<<"buscando pelo id: "<<aux2->review_id<<"naArvore//Pos = "<<aux2->getId()<<endl;
                if(buscaPorId(aux2->review_id)!=-1){
                    cout<<"id encontrado"<<endl;
                    enc++;
                }else{
                    cout<<"id nao encontrado"<<endl;
                    Nenc++;
                }
                delete aux2;
                break;
            }
        }
    }

    cout<<"Total Encontrado = "<<enc<<endl;
    cout<<"Total Nao Encontrado = "<<Nenc<<endl;
}

int ArvoreVP::buscaPorId(char id[])
{
    //cout<<"entra aqui"<<endl;
    noVP *atual = new noVP;
    atual = this->raiz;

    while (1)
    {
        //cout<<"loop"<<endl;
        if (comparacaoiDigualB(id, atual))
        {
            //cout<<"entra aqui 1"<<endl;
            break;
        }

        if (atual->getId() == Nill->getId())
        {
            //cout<<"entra aqui 2"<<endl;
            return -1;//não encontrou
        }

        if (comparacaoiDmaiorB(id, atual))
        {
            //cout<<"entra aqui 3"<<endl;
            atual = atual->dir;
        }
        else
        {
            //cout<<"entra aqui 4"<<endl;
            atual = atual->esq;
        }
    }
    //cout<<"sai do loop"<<endl;

    return atual->getId();
}

void ArvoreVP::verificaQuebraDePropriedade(noVP *no)
{ // verifica se existe caso 1,2 ou 3

    if (this->raiz->cor == false)//caso 1  
    {
        //cout << "mudando a cor da raiz" << endl;
        this->raiz->cor = true;
    }


    noVP *pai = new noVP;
    noVP *tio = new noVP;
    noVP *avo = new noVP;
    bool paiDirAvo = false;
    bool noDirPai = false;
    pai = no->pai;

    if (pai->getId() == this->Nill->getId())
    {
        //cout << "pai é Nill" << endl;
        return;
    }

    avo = pai->pai;

    if (avo->getId() == this->Nill->getId())
    {
        //cout << "avo é Nill" << endl;
        return;
    }

    if (avo->esq->getId() == pai->getId())
    {
        tio = avo->dir;
    }
    else if (avo->dir->getId() == pai->getId())
    {
        tio = avo->esq;
        paiDirAvo = true;
    }

    if (pai->esq->getId() == no->getId())
    {
    }
    else if (pai->dir->getId() == no->getId())
    {
        noDirPai = true;
    }

    if (pai->cor == false && tio->cor == false)//caso 2
    {
        cout << "pai e tio vermelho" << endl;
        trocaCor(pai);
        trocaCor(tio);
        trocaCor(avo);

        verificaQuebraDePropriedade(avo);

        // delete pai;
        // delete tio;
        // delete avo;
        return;
    }

    if (pai->cor == false && tio->cor == true)//caso 3
    {
        //cout << "pai vermelho e tio preto" << endl;
        if (paiDirAvo)
        {
            if (!noDirPai)
            {
                trocaCor(no);
                trocaCor(avo);
                cout << "rotacaoDuplaEsq" << endl;
                //rotacaoDuplaEsq(no, pai, avo);
                verificaQuebraDePropriedade(avo);
            }
            if (noDirPai)
            {
                trocaCor(pai);
                trocaCor(avo);
                cout << "rotacaosimplesEsq" << endl;
                rotacaoSimplesEsq(no, pai, avo);
                verificaQuebraDePropriedade(avo);
            }
        }

        if (!paiDirAvo)
        {
            if (noDirPai)
            {
                trocaCor(no);
                trocaCor(avo);
                cout << "rotacaoDuplaDir" << endl;
                //rotacaoDuplaDir(no, pai, avo);
                verificaQuebraDePropriedade(avo);
            }
            if (!noDirPai)
            {
                trocaCor(pai);
                trocaCor(avo);
                cout << "rotacaoSimplesDir" << endl;
                //rotacaoSimplesDir(no, pai, avo);
                verificaQuebraDePropriedade(avo);
            }
        }
    }
}

void ArvoreVP::trocaCor(noVP *no)
{

    if (no->cor == false)
    {
        no->cor = true;
    }
    else
    {
        no->cor = false;
    }
}

void ArvoreVP::rotacaoSimplesDir(noVP *no, noVP *pai, noVP *avo) // verificar
{
    pai->dir = avo;      // passa o avo para a direita do pai
    avo->esq = this->Nill;



    //pai->pai = avo->pai; // oq esta no topo do avo passa para o topo do pai
    //avo->pai = pai;      // o topo do avo passa a ser o pai


}

void ArvoreVP::rotacaoSimplesEsq(noVP *no, noVP *pai, noVP *avo) // verificar
{
    pai->pai=avo->pai;
    pai->esq=avo;
}

void ArvoreVP::rotacaoDuplaDir(noVP *no, noVP *pai, noVP *avo) // verificar
{
    rotacaoSimplesEsq(no,pai,avo);
    avo->esq=pai;
    rotacaoSimplesDir(no,pai,avo);





    //no->pai = avo->pai;
    //no->dir = avo; // o  pai  passa  a ser o filho do no
    //no->esq = pai; // o avo passa a serr o filho  do  no

    // ajeitando o pai
    //pai->pai = no; // o pai do pai passa a ser o no
    //pai->dir = this->Nill;

    // ajeitando o avo
    //avo->pai = no;
    //avo->esq = this->Nill;

}

void ArvoreVP::rotacaoDuplaEsq(noVP *no, noVP *pai, noVP *avo) // verificar
{
    rotacaoSimplesDir(no,pai,avo);
    avo->dir=pai;
    rotacaoSimplesEsq(no,pai,avo);


    //no->pai = avo->pai;
    //no->esq = avo; // o  pai  passa  a ser o filho do no
    //no->dir = pai; // o avo passa a serr o filho  do  no

    // ajeitando o pai
    //pai->pai = no; // o pai do pai passa a ser o no
    //pai->esq = this->Nill;

    // ajeitando o avo
    //avo->pai = no;
    //avo->dir = this->Nill;

}

bool ArvoreVP::comparacaoAmaiorB(noVP *noA, noVP *noB)
{ // retornar Maior
    int n = 0;
    char a, b;
    while (1)
    {
        a = noA->review_id[9 + n];
        b = noB->review_id[9 + n];

        if ((int)a == (int)b)
        {
            n++;
        }

        if ((int)a != (int)b)
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

bool ArvoreVP::comparacaoAmenorB(noVP *noA, noVP *noB)
{ // retorna menor
    int n = 0;
    char a, b;
    while (1)
    {
        a = noA->review_id[9 + n];
        b = noB->review_id[9 + n];

        if ((int)a == (int)b)
        {
            n++;
        }

        if ((int)a != (int)b)
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

bool ArvoreVP::comparacaoiDmaiorB(char noA[], noVP *noB)
{ // retornar Maior
    int n = 0;
    char a, b;
    while (1)
    {
        a = noA[9 + n];
        b = noB->review_id[9 + n];

        if ((int)a == (int)b)
        {
            n++;
        }

        if ((int)a != (int)b)
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

bool ArvoreVP::comparacaoiDmenorB(char noA[], noVP *noB)
{ // retornar Maior
    int n = 0;
    char a, b;
    while (1)
    {
        a = noA[9 + n];
        b = noB->review_id[9 + n];

        if ((int)a == (int)b)
        {
            n++;
        }

        if ((int)a != (int)b)
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

bool ArvoreVP::comparacaoiDigualB(char noA[], noVP *noB)
{ // retornar Maior
    int n = 0;
    char a, b;
    while (n < 90)
    {
        a = noA[n];
        b = noB->review_id[n];

        if ((int)a == (int)b)
        {
            n++;
        }

        if ((int)a != (int)b)
        {
            return false;
        }
    }
    return true;
}
