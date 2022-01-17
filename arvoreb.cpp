#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Arvoreb.h"

using namespace std;

Arvoreb::~Arvoreb()
{
  //dtor
}

int Arvoreb::insert(char k[], No no, int comp)// aqui
{
 // cout<<"insert id: "<<k<<endl;
  if (root == NULL)
  {
    root = new TreeNode(t, true);
    root->nos[0] = no;
    root->n = 1;
  }
  else
  {
    if (root->n == 2 * t - 1)
    {
      TreeNode *s = new TreeNode(t, false);

      s->C[0] = root;

      s->splitChild(0, root);

      int i = 0;
      if (s->comparacaoiDmaiorB(k,s->nos[0]))// aqui
        i++;
      s->C[i]->insertVal(k, no, comp);

      root = s;
    }
    else
      root->insertVal(k, no, comp);
  }
  return comp;
}

