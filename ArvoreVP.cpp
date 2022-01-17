#include <iostream>
#include <string>
#include "NoVP.h"
#include "ArvoreVP.h"
#include "No.h"

using namespace std;

ArvoreVP::ArvoreVP()
{
    comparacaoIns=0;
    comparacaoBus=0;
    Nill->cor = true;
    char a[90] = "";
    Nill->setreview_id(a);
    Nill->setId(-1);
    raiz = Nill;
    raiz->pai = Nill;
}

ArvoreVP::~ArvoreVP() {
    raiz = Libera(raiz);
    delete Nill;
}

NoVP *ArvoreVP::Libera(NoVP *p) {
    if(p->getId() != Nill->getId())
    {
        p->esq=Libera(p->esq);
        p->dir=Libera(p->dir);
        delete p;
        p = Nill;
    }
    return p;
}

void ArvoreVP::ImprimeArvore(NoVP *no, int i)
{
    if (no->getId() > 0)
    {
        cout << "(" << i << ")" << no->getId() << " -- ";
        ImprimeArvore(no->esq, i + 1);
        ImprimeArvore(no->dir, i + 1);
    }
}

void ArvoreVP::criaArvore(int vetorId[], int tam, ifstream &arqBin)
{
    cout << "Criando a Arvore VP" << endl;
    for (int i = 0; i < tam; i++)
    {
        No *aux = new No();
        arqBin.seekg((sizeof(No)) * (vetorId[i] - 1), ios_base::beg);
        while (arqBin.read((char *)aux, sizeof(No)))
        {
            if (aux->getId() == vetorId[i])
            {
                //cout << i << endl;
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

    NoVP *noNovo;
    noNovo = SubNoParanoVP(noInserindo);

    if (raiz->getId() == Nill->getId())
    {

        this->raiz = noNovo;
        this->raiz->pai = this->Nill;
        verificaQuebraDePropriedade(noNovo);
        //cout << "adicionou a raiz" << endl;
        return;
    }

    NoVP *noPai;
    noPai = this->raiz;
    NoVP *noAnalisado;
    noAnalisado = this->raiz;
    bool add_esq;

    while (1)
    {
        //cout << "noAnalisado->getId():   " << noAnalisado->getId() << endl;
        if (noAnalisado->getId() == Nill->getId())
        {
            break;
        }

        if (noAnalisado->getId()==noNovo->getId())
        {
            delete noNovo;
            return;
        }
        

        if (comparacaoAmaiorB(noAnalisado, noNovo))
        {
            this->comparacaoIns++;
            //cout << "entra no if" << endl;
            noPai = noAnalisado;
            noAnalisado = noAnalisado->esq;
            add_esq = true;
        }
        else
        {
            this->comparacaoIns++;
            //cout << "entra no else" << endl;
            noPai = noAnalisado;
            noAnalisado = noAnalisado->dir;
            add_esq = false;
        }
    }

    if (add_esq)
    {
        // cout << "adicionou na esq" << endl;
        noPai->esq = noNovo;
        noNovo->pai = noPai;
        noNovo->esq = Nill;
        noNovo->dir = Nill;
    }
    else
    {
        // cout << "adicionou na dir" << endl;
        noPai->dir = noNovo;
        noNovo->pai = noPai;
        noNovo->esq = Nill;
        noNovo->dir = Nill;
    }

    verificaQuebraDePropriedade(noNovo);

    verificaRaiz(raiz);

    //cout << "Imprimindo Arvore" << endl;
    //ImprimeArvore(raiz, 0);
    // cout << endl;

    return;
}

NoVP *ArvoreVP::SubNoParanoVP(No *noInserindo)
{
    NoVP *no = new NoVP;
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

void ArvoreVP::verificaRaiz(NoVP *no)
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
    int enc = 0;
    int Nenc = 0;
    for (int i = 0; i < tam; i++)
    {
        No *aux2 = new No();
        arqBin.seekg((sizeof(No)) * (vetorId[i] - 1), ios_base::beg);
        while (arqBin.read((char *)aux2, sizeof(No)))
        {
            if (aux2->getId() == vetorId[i])
            {
                //cout << "buscando pelo id: " << aux2->review_id << "naArvore//Pos = " << aux2->getId() << endl;
                if (buscaPorId(aux2->review_id) != -1)
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

    cout << "Total Encontrado = " << enc << endl;
    cout << "Total Nao Encontrado = " << Nenc << endl;
}

int ArvoreVP::buscaPorId(char id[])
{
    //cout<<"entra aqui"<<endl;
    NoVP *atual;
    atual = this->raiz;

    while (1)
    {

        //cout<<"loop"<<endl;
        if (comparacaoiDigualB(id, atual))
        {
            this->comparacaoBus++;
            //cout<<"entra aqui 1"<<endl;
            break;
        }

        if (atual->getId() == Nill->getId())
        {
            this->comparacaoBus++;
            //cout<<"entra aqui 2"<<endl;
            //delete atual;
            return -1; //não encontrou
        }

        if (comparacaoiDmaiorB(id, atual))
        {
            this->comparacaoBus++;
            //cout<<"entra aqui 3"<<endl;
            atual = atual->dir;
        }
        else
        {
            this->comparacaoBus++;
            //cout<<"entra aqui 4"<<endl;
            atual = atual->esq;
        }
    }
    //cout<<"sai do loop"<<endl;


    //delete atual;
    return atual->getId();
}

void ArvoreVP::verificaQuebraDePropriedade(NoVP *no)
{ // verifica se existe caso 1,2 ou 3

    if (this->raiz->cor == false) //caso 1
    {
        //cout << "mudando a cor da raiz" << endl;
        this->raiz->cor = true;
    }

    NoVP *pai;
    NoVP *tio;
    NoVP *avo;
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

    if (pai->cor == false && tio->cor == false) //caso 2
    {
        //cout << "pai e tio vermelho" << endl;
        trocaCor(pai);
        if (tio != this->Nill)
            trocaCor(tio);
        if (avo != this->Nill)
            trocaCor(avo);
        return;
    }

    if (pai->cor == false && tio->cor == true) //caso 3
    {
        //cout << "pai vermelho e tio preto" << endl;
        if (paiDirAvo)
        {
            if (!noDirPai)
            {
                trocaCor(no);
                if (avo != this->Nill)
                    trocaCor(avo);
                //cout << "rotacaoDuplaEsq" << endl;
                rotacaoDuplaEsq(no, pai, avo);

            }
            if (noDirPai)
            {
                trocaCor(pai);
                if (avo != this->Nill)
                    trocaCor(avo);
                //cout << "rotacaosimplesEsq" << endl;
                rotacaoSimplesEsq(no, pai, avo);

            }
        }
        if (!paiDirAvo)
        {
            if (noDirPai)
            {
                trocaCor(no);
                if (avo != this->Nill)
                    trocaCor(avo);
                //cout << "rotacaoDuplaDir" << endl;
                rotacaoDuplaDir(no, pai, avo);

            }
            if (!noDirPai)
            {
                trocaCor(pai);
                //if (avo != this->Nill)
                trocaCor(avo);
                //cout << "rotacaoSimplesDir" << endl;
                rotacaoSimplesDir(no, pai, avo);
            }
        }
    }
}

void ArvoreVP::trocaCor(NoVP *no)
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

void ArvoreVP::rotacaoSimplesDir(NoVP *no, NoVP *pai, NoVP *avo) // verificar
{
    // pai->dir = avo;      // passa o avo para a direita do pai
    // avo->esq = this->Nill;
    NoVP *bis = avo->pai;
    if (bis->getId() != this->Nill->getId())
    {
        if (bis->dir->getId() == avo->getId())
        { // avo a direita do bisavo
            bis->dir = pai;
        }
        else
        {
            bis->esq = pai;
        }
    }
    pai->pai = avo->pai;
    avo->pai = pai;

    avo->esq = pai->dir;
    pai->dir = avo;
    //cout << "analise: " << no->getId() << " -- " << pai->getId() << " -- " << avo->getId() << endl;
    if (avo->esq->getId() != this->Nill->getId()) // n sei pq ta com erro
        avo->esq->pai = avo;
    //pai->pai = avo->pai; // oq esta no topo do avo passa para o topo do pai
    //avo->pai = pai;      // o topo do avo passa a ser o pai
}

void ArvoreVP::rotacaoSimplesEsq(NoVP *no, NoVP *pai, NoVP *avo) // verificar
{
    NoVP *bis = avo->pai;
    if (bis->getId() != this->Nill->getId())
    {
        if (bis->dir->getId() == avo->getId())
        { // avo a direita do bisavo
            bis->dir = pai;
        }
        else
        {
            bis->esq = pai;
        }
    }
    pai->pai = avo->pai;
    avo->pai = pai;

    avo->dir = pai->esq;
    pai->esq = avo;
    //cout << "analise: " << no->getId() << " -- " << pai->getId() << " -- " << avo->getId() << endl;
    if (avo->dir->getId() != this->Nill->getId())
        avo->dir->pai = avo;
}

void ArvoreVP::rotacaoDuplaDir(NoVP *no, NoVP *pai, NoVP *avo) // verificar
{
    rotacaoSimplesEsq(no->dir, no, pai);
    avo->esq = no;
    rotacaoSimplesDir(pai, no, avo);
}

void ArvoreVP::rotacaoDuplaEsq(NoVP *no, NoVP *pai, NoVP *avo) // verificar
{
    rotacaoSimplesDir(no->esq, no, pai);
    avo->dir = no;
    rotacaoSimplesEsq(pai, no, avo);
}

bool ArvoreVP::comparacaoAmaiorB(NoVP *noA, NoVP *noB)
{ // retornar Maior
    int n = 0;
    char a, b;
    while ((9+n)<90)
    {
        // cout<<"loop"<< endl;
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

bool ArvoreVP::comparacaoAmenorB(NoVP *noA, NoVP *noB)
{ // retorna menor
    int n = 0;
    char a, b;
    while ((9+n)<90)
    {
        //  cout<<"loop"<< endl;
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

bool ArvoreVP::comparacaoiDmaiorB(char noA[], NoVP *noB)
{ // retornar Maior
    int n = 0;
    char a, b;
    while ((9+n)<90)
    {
        //  cout<<"loop"<< endl;
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

bool ArvoreVP::comparacaoiDmenorB(char noA[], NoVP *noB)
{ // retornar Maior
    int n = 0;
    char a, b;
    while ((9+n)<90)
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

bool ArvoreVP::comparacaoiDigualB(char noA[], NoVP *noB)
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
