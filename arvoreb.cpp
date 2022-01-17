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

void Arvoreb::criaArvore(int vetorId[], int tam, ifstream &arqBin)
{
  cout << "Carregando upvotes dos registro" << endl;
  for (int i = 0; i < tam; i++)
  {
    No *aux = new No();
    arqBin.seekg((sizeof(No)) * (vetorId[i] - 1), ios_base::beg);
    while (arqBin.read((char *)aux, sizeof(No)))
    {
      if (aux->getId() == vetorId[i])
      {
        No p = *aux;
        cout << i << " -- " << aux->getId() << " -- " << p.getId() << endl;
        this->insert(aux->review_id, p, comparacoes);
        //cout << "passa  do insere" << endl;
        delete aux;
        break;
      }
    }
  }
}

int Arvoreb::insert(char k[], No no, int comp)// aqui
{
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

