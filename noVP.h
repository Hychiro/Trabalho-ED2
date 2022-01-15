#ifndef NOVP_H
#define NOVP_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class noVP
{

    private:
    int iD;

public:
    noVP *esq=new noVP;
    noVP *dir=new noVP;
    noVP *pai=new noVP;
    noVP(){
        this->esq=nullptr;
        this->dir=nullptr;
        this->pai=nullptr;
        this->cor=false;};
    ~noVP(){};
    char review_id[90];
    bool cor;//falso = vermelho; verdadeiro=preto;
    int getId() { return iD; };
    void setId(int i) { iD = i; };
};


#endif // NOVP_HS