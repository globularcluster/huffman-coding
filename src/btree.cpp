#include "../include/btree.h"
#include <boost/dynamic_bitset.hpp>
#include <iomanip>
#include <iostream>

#define COUNT 10

using namespace std;

BTree::BTree() { this->root = new node(); };

BTree::BTree(double prob, char c) {
  this->root = new node(prob, c);
  this->root->prob = prob;
  this->root->charac = c;
}

BTree::BTree(BTree *direita, BTree *esquerda) {
  this->root = new node(esquerda->root->prob + direita->root->prob, 0);
  this->root->auxChars = esquerda->root->auxChars + direita->root->auxChars;
  this->root->right = direita->root;
  this->root->left = esquerda->root;
}

void BTree::_addNodeHelper(node *root, double val, char c) {

  if (root->prob > val) {
    if (!root->left)
      root->left = new node(val, c);
    else
      this->_addNodeHelper(root->left, val, c);
  } else {
    if (!root->right)
      root->right = new node(val, c);
    else
      this->_addNodeHelper(root->right, val, c);
  }
};

void BTree::addNode(double val, char c) {

  if (this->root)
    this->_addNodeHelper(this->root, val, c);
  else
    this->root = new node(val, c);
};

void BTree::addNode(BTree *node) {

  if (this->root)
    this->_addNodeHelper(node->root, node->root->prob, node->root->charac);
  else
    this->root = node->root;
}

void BTree::printTree(node *p, int indent) {
  // Base case
  if (p == NULL)
    return;

  // Increase distance between levels
  indent += COUNT;

  // Process right child first
  printTree(p->right, indent);

  // Print current node after space
  // count
  printf("\n");
  for (int i = COUNT; i < indent; i++)
    printf(" ");
  printf("%.1f", p->prob);
  if (p->charac != 0)
    printf("(%c)\n", p->charac);
  else
    cout << "(" + p->auxChars + ")\n";

  // Process left child
  printTree(p->left, indent);
}

node *BTree::getRoot() { return this->root; }
double BTree::getProb() { return this->root->prob; }
char BTree::getChar() { return this->root->charac; }

boost::dynamic_bitset<> getCod(char c) {
  static boost::dynamic_bitset<> db;

  return db;
}