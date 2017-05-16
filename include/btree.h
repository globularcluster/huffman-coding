#ifndef __BTREE_H_INCLUDED__
#define __BTREE_H_INCLUDED__

// baseado em: https://gist.github.com/mgechev/5911348

#include <iostream>

struct node {

  double prob;
  char charac;
  node *left;
  node *right;

  node(double val = 0, char c = 0) {
    this->prob = val;
    this->charac = c;
    this->left = NULL;
    this->right = NULL;
  }
};

class BTree {

private:
  node *root;
  void _addNodeHelper(node *root, double val, char c);

public:
  BTree();
  BTree(BTree *direita, BTree *esquerda);
  BTree(double prob, char c);
  void addNode(double val, char c);
  void addNode(BTree *node);
  node *getNode(double val);
  node *getRoot();
  double getProb();
  char getChar();
  void printTree(node *p, int indent = 0);
};

#endif