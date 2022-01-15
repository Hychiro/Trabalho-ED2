#include "TreeNode.h"
#include <iostream>

#include "no.h"
#include "arvoreb.h"

using namespace std;

TreeNode::TreeNode(int t1, bool leaf1) {
  t = t1;
  leaf = leaf1;

  keys = new int[2 * t - 1];
  C = new TreeNode *[2 * t];

  nos = new No[2 * t - 1]; //inicializa o vetor de nós

  n = 0;
}

TreeNode::~TreeNode()
{
    //dtor
}

void TreeNode::traverse() {
  int i;
  for (i = 0; i < n; i++) {
    if (leaf == false){
        C[i]->traverse();
    }
    cout << " " << keys[i];
  }

  if (leaf == false){
       C[i]->traverse();
  }
}

TreeNode *TreeNode::search(int k) {
  int i = 0;
  while (i < n && k > keys[i])
    i++;

  if (keys[i] == k)
    return this;

  if (leaf == true)
    return NULL;

  return C[i]->search(k);
}
int TreeNode::insertVal(int k, No no, int comp) {
  int i = n - 1;

  if (leaf == true) {
    while (i >= 0 && keys[i] > k) {
      comp++;
      keys[i + 1] = keys[i];
      nos[i + 1] = nos[i];
      i--;
    }

    int j = n - 1;
    while(i >= 0 && keys[j] < k){
        comp++;
        j--;
    }

    keys[i + 1] = k;
    nos[i + 1] = no;
    n = n + 1;
  } else {
    while (i >= 0 && keys[i] > k){
      comp++;
        i--;
    }

    int j = n - 1;
    while(i >= 0 && keys[j] < k){
        comp++;
        j--;
    }

    if (C[i + 1]->n == 2 * t - 1) {
      splitChild(i + 1, C[i + 1]);

      if (keys[i + 1] < k){
        comp++;
        i++; 
      }
    }
    C[i + 1]->insertVal(k,no, comp);
  }
  return comp;
}

void TreeNode::splitChild(int i, TreeNode *y) {
  TreeNode *z = new TreeNode(y->t, y->leaf);
  z->n = t - 1;

  for (int j = 0; j < t - 1; j++)
    z->keys[j] = y->keys[j + t];

  if (y->leaf == false) {
    for (int j = 0; j < t; j++)
      z->C[j] = y->C[j + t];
  }

  y->n = t - 1;
  for (int j = n; j >= i + 1; j--)
    C[j + 1] = C[j];

  C[i + 1] = z;

  for (int j = n - 1; j >= i; j--)
    keys[j + 1] = keys[j];

  keys[i] = y->keys[t - 1];
  n = n + 1;
}
