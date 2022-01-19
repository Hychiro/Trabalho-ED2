#ifndef NOVP_H
#define NOVP_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class NoVP
{

    private:
    int iD;

public:
    NoVP *esq;
    NoVP *dir;
    NoVP *pai;
    NoVP(){
        cor=false;
        esq=nullptr;
        dir=nullptr;
        pai=nullptr;};
    ~NoVP(){};
    char review_id[90];
    void setreview_id(char a[90]){
        for (int i = 0; i < 90; i++)
        {
            review_id[i]=a[i];
        }   
        };
    bool cor;//falso = vermelho; verdadeiro=preto;
    int getId() { return iD; };
    void setId(int i) { iD = i; };
};


#endif // NOVP_HS
