#ifndef __BTREE_H_INCLUDED__
#define __BTREE_H_INCLUDED__

// baseado em: https://gist.github.com/mgechev/5911348

#include <iostream>

struct node {

  double prob;
  char charac;
  node *left;
  node *right;

  node(double val) {
    this->prob = val;
    this->charac = NULL;
    this->left = NULL;
    this->right = NULL;
  }
};

class BTree {

private:
  node *root;
  void _addNodeHelper(node *root, double val);

public:
  void addNode(double val);
  node *getNode(double val);
  node *getRoot();
  void printTree(node *p, int indent = 0);
};

#endif