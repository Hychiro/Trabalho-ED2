#ifndef ARVOREB_H
#define ARVOREB_H
#include "TreeNode.h"
#include <iostream>

using namespace std;

class Arvoreb
{
    TreeNode *root;
    int t;

public:
    void criaArvore(int vetorId[], int tam, ifstream &arqBin);


    Arvoreb(int temp)
    {
        root = NULL;
        t = temp;
    }
    ~Arvoreb();

    void traverse()
    {
        if (root != NULL)
            root->traverse();
    }

    TreeNode *search(char k[], int*comp)//aqui
    {
        return (root == NULL) ? NULL : root->search(k,comp);
    }

    void insert(char k[], No no, int* comp);//aqui
};

#endif // ARVOREB_H
