#ifndef TREENODE_H
#define TREENODE_H

#include "NoB.h"

class TreeNode
{
    public:
    int t;
    TreeNode **C;
    int n;
    bool leaf;

    NoB *nos; //<---- um vetor de nós, o id do nó precisa ser igual ao seu id em -->*keys<--//exemplo keys[0] precisa armazenar o id de nos[0]<---

    TreeNode(int temp, bool bool_leaf);
    ~TreeNode();


    int *keys;

    void insertVal(char k[], NoB no, int* comp); //aqui
    void splitChild(int i, TreeNode *y);
    void traverse();

    TreeNode *search(char k[],int* comp);

    bool comparacaoiDmaiorB(char noA[], NoB noB, int *comp);
    bool comparacaoiDmenorB(char noA[], NoB noB, int *comp);
    bool comparacaoiDigualB(char noA[], NoB noB, int *comp);

    friend class arvoreb;
};

#endif // TREENODE_H
