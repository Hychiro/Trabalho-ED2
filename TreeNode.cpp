#include "TreeNode.h"
#include <iostream>

#include "No.h"
#include "Arvoreb.h"

using namespace std;

TreeNode::TreeNode(int t1, bool leaf1) {//aqui
  t = t1;
  leaf = leaf1;

  C = new TreeNode *[2 * t];

  nos = new No[2 * t - 1]; //inicializa o vetor de nós

  n = 0;
}

TreeNode::~TreeNode()
{
    //dtor
}

void TreeNode::traverse() {//aqui
  int i;
  for (i = 0; i < n; i++) {
    if (leaf == false){
        C[i]->traverse();
    }
    cout << " " << C[i]->nos->review_id;
  }

  if (leaf == false){
       C[i]->traverse();
  }
}




TreeNode *TreeNode::search(char k[]) {//aqui
  
  int i = 0;
  while (i < n && comparacaoiDmaiorB( k ,this->nos[i]))
    i++;

  if (comparacaoiDigualB( k ,this->nos[i]))
    return this;

  if (leaf == true)
    return NULL;

  return C[i]->search(k);
}

int TreeNode::insertVal(char k[], No no, int comp) {//aqui
  int i = n - 1;

  if (leaf == true) {
    while (i >= 0 && comparacaoiDmenorB( k ,this->nos[i])) {
      comp++;
      nos[i + 1] = nos[i];
      i--;
    }

    int j = n - 1;
    while(i >= 0 && comparacaoiDmaiorB( k ,this->nos[i])){
        comp++;
        j--;
    }
    nos[i + 1] = no;
    n = n + 1;
  } else {
    while (i >= 0 && comparacaoiDmaiorB( k ,this->nos[i])){
      comp++;
        i--;
    }

    int j = n - 1;
    while(i >= 0 && comparacaoiDmaiorB( k ,this->nos[i])){
        comp++;
        j--;
    }

    if (C[i + 1]->n == 2 * t - 1) {
      splitChild(i + 1, C[i + 1]);

      if (comparacaoiDmaiorB( k ,this->nos[i])){
        comp++;
        i++; 
      }
    }
    C[i + 1]->insertVal(k,no, comp);
  }
  return comp;
}

void TreeNode::splitChild(int i, TreeNode *y) {//aqui
  TreeNode *z = new TreeNode(y->t, y->leaf);
  z->n = t - 1;

  for (int j = 0; j < t - 1; j++)
    z->nos[j] = y->nos[j + t];

  if (y->leaf == false) {
    for (int j = 0; j < t; j++)
      z->C[j] = y->C[j + t];
  }

  y->n = t - 1;
  for (int j = n; j >= i + 1; j--)
    C[j + 1] = C[j];

  C[i + 1] = z;

  for (int j = n - 1; j >= i; j--)
    nos[j + 1] = nos[j];

  nos[i] = y->nos[t - 1];
  n = n + 1;
}

bool TreeNode::comparacaoiDmaiorB(char noA[], No noB)
{ // retornar Maior
    int n = 0;
    char a, b;
    while (1)
    {
        a = noA[9 + n];
        b = noB.review_id[9 + n];

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

bool TreeNode::comparacaoiDmenorB(char noA[], No noB)
{ // retornar Maior
    int n = 0;
    char a, b;
    while (1)
    {
        a = noA[9 + n];
        b = noB.review_id[9 + n];

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

bool TreeNode::comparacaoiDigualB(char noA[], No noB)
{ // retornar Maior
    int n = 0;
    char a, b;
    while (n < 90)
    {
        a = noA[n];
        b = noB.review_id[n];

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

