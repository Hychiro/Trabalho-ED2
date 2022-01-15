#ifndef TREENODE_H
#define TREENODE_H

#include "no.h"

class TreeNode
{
    //int *keys; //armazena um ponteiro para as chaves, que serão = posição 9+n do char id
    int t;
    TreeNode **C;
    int n;
    bool leaf;


    No* nos; //<---- um vetor de nós, o id do nó precisa ser igual ao seu id em -->*keys<--//exemplo keys[0] precisa armazenar o id de nos[0]<---

public:
    TreeNode(int temp, bool bool_leaf);
    ~TreeNode();

    int *keys; //armazena um ponteiro para as chaves, que serão = posição 9+n do char id

    int insertVal(int k, No no, int comp);
    void splitChild(int i, TreeNode *y);
    void traverse();

    TreeNode *search(int k);

    friend class arvoreb;
};

#endif // TREENODE_H
