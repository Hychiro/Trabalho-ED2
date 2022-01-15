#ifndef ARVOREB_H
#define ARVOREB_H
#include "TreeNode.h"
#include <iostream>

using namespace std;

class arvoreb
{
    TreeNode *root;
    int t;

public:

    int comparacoes;

    arvoreb(int temp)
    {
        root = NULL;
        t = temp;
        comparacoes = 0;
    }
    ~arvoreb();

    void traverse()
    {
        if (root != NULL)
            root->traverse();
    }

    TreeNode *search(int k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }

    void insert(int k, No no);
};

#endif // ARVOREB_H
