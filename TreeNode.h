#ifndef TREENODE_H
#define TREENODE_H

#include "No.h"

class TreeNode
{
    public:
    //int *keys; //armazena um ponteiro para as chaves, que serão = posição 9+n do char id
    int t;
    TreeNode **C;
    int n;
    bool leaf;

    No *nos; //<---- um vetor de nós, o id do nó precisa ser igual ao seu id em -->*keys<--//exemplo keys[0] precisa armazenar o id de nos[0]<---

    TreeNode(int temp, bool bool_leaf);
    ~TreeNode();

    //char **keys; //armazena um ponteiro para as chaves, que serão = posição 9+n do char id

    int *keys;

    void insertVal(char k[], No no, int* comp); //aqui
    void splitChild(int i, TreeNode *y);
    void traverse();

    TreeNode *search(char k[],int* comp);

    bool comparacaoiDmaiorB(char noA[], No noB, int *comp);
    bool comparacaoiDmenorB(char noA[], No noB, int *comp);
    bool comparacaoiDigualB(char noA[], No noB, int *comp);

    friend class arvoreb;
};

#endif // TREENODE_H
