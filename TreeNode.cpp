#include "TreeNode.h"
#include <iostream>


#include "Arvoreb.h"
#include "NoB.h"

using namespace std;

TreeNode::TreeNode(int t1, bool leaf1)
{ //aqui
  t = t1;
  leaf = leaf1;

  C = new TreeNode *[2 * t];
  //keys = new int[2 * t - 1];
  nos = new NoB [2 * t - 1]; //inicializa o vetor de nós

  n = 0;
}

TreeNode::~TreeNode()
{
}

void TreeNode::traverse()
{ //aqui
  int i;
  for (i = 0; i < n; i++)
  {
    if (leaf == false)
    {
      C[i]->traverse();
    }

    cout << "id: " << nos[i].review_id << endl;
  }

  if (leaf == false)
  {
    C[i]->traverse();
  }
}

TreeNode *TreeNode::search(char k[], int *comp)
{ //aqui

  int i = 0;
  while (i < n && comparacaoiDmaiorB(k, this->nos[i], comp))
    i++;

  if (comparacaoiDigualB(k, this->nos[i], comp))
    return this;

  if (leaf == true)
    return NULL;

  return C[i]->search(k, comp);
}

void TreeNode::insertVal(char k[], NoB no, int *comp)
{ //aqui
  int i = n - 1;
  //cout<<"id insertVal: "<< k<<endl;
  if (leaf == true)
  {
    //cout << "" << endl;
    while (i >= 0 && comparacaoiDmenorB(k, this->nos[i], comp))
    {
      //cout<<"id insertVal: "<< nos[i].review_id<<endl;
      nos[i + 1] = nos[i];

      i--;
    }
    //cout << "while 2" << endl;
    int j = n - 1;

    // while (i >= 0 && comparacaoiDmaiorB(k, this->nos[j]))
    // {
    //   comp++;
    //   j--;
    // }

    nos[i + 1] = no;
    n = n + 1;
  }
  else
  {
    //cout << "while 3" << endl;
    while (i >= 0 && comparacaoiDmenorB(k, this->nos[i], comp))
    {
      i--;
    }
    //cout << "while 4" << endl;
    int j = n - 1;

    // while (i >= 0 && comparacaoiDmaiorB(k, this->nos[j]))
    // {
    //   comp++;
    //   j--;
    // }

    //cout << "splitChild" << endl;
    if (C[i + 1]->n == 2 * t - 1)
    {
      splitChild(i + 1, C[i + 1]);

      if (comparacaoiDmaiorB(k, this->nos[i + 1], comp))
      {

        i++;
      }
    }
    //cout << "foi tudo" << endl;
    C[i + 1]->insertVal(k, no, comp);
  }

  //cout<<" comparacoes: "<< comp<<endl;
}

void TreeNode::splitChild(int i, TreeNode *y)
{
  TreeNode *z = new TreeNode(y->t, y->leaf);
  z->n = t - 1;
  for (int j = 0; j < t - 1; j++)
    z->nos[j] = y->nos[j + t];
  if (y->leaf == false)
  {
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
bool TreeNode::comparacaoiDmaiorB(char noA[], NoB noB, int *comp)
{ // retornar Maior
  int n = 0;
  char a, b;
  while ((9 + n) < 90)
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

  *comp = 1 + *comp;

  if ((int)a > (int)b)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool TreeNode::comparacaoiDmenorB(char noA[], NoB noB, int *comp)
{ // retornar Maior
  int n = 0;
  char a, b;
  while ((9 + n) < 90)
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

  *comp = 1 + *comp;

  if ((int)a < (int)b)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool TreeNode::comparacaoiDigualB(char noA[], NoB noB, int *comp)
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
      *comp = 1 + *comp;
      return false;
    }
  }
  *comp = 1 + *comp;
  return true;
}
