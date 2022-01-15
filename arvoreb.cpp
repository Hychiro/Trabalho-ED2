#include "arvoreb.h"
#include <iostream>


using namespace std;


arvoreb::~arvoreb()
{
    //dtor
}

int arvoreb::insert(int k, No no, int comp) {
  if (root == NULL) {
    root = new TreeNode(t, true);
    root->keys[0] = k;
    root->nos[0] = no;
    root->n = 1;
  } else {
    if (root->n == 2 * t - 1) {
      TreeNode *s = new TreeNode(t, false);

      s->C[0] = root;

      s->splitChild(0, root);

      int i = 0;
      if (s->keys[0] < k)
        i++;
      s->C[i]->insertVal(k,no, comp);

      root = s;
    } else
      root->insertVal(k,no, comp);
  }
  return comp;
}
