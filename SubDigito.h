#ifndef SUBDIGITO_H
#define SUBDIGITO_H
#include <iostream>
#include <string>

using namespace std;

class SubDigito
{
private:
    char digito;
    string codigo;
    // int chave;
    // SubDigito * prox;

public:
    SubDigito(){};
    ~SubDigito(){};

    char getDigito() { return digito; };
    void setDigito(char i) { digito = i; };

    string getCodigo() { return codigo; };
    void setCodigo(string i) { codigo = i; };

    // int getChave() { return chave; };
    // void setChave(int i) { chave = i; };

    
    // SubDigito* getProx() { return prox; };
    // void setProx(SubDigito* i) { prox = i; };
};
#endif // SUBDIGITO_H