#include "../include/btree.h"
#include <iomanip>
#include <iostream>

#define COUNT 10

using namespace std;

void BTree::_addNodeHelper(node *root, double val) {

  if (root->prob > val) {
    if (!root->left)
      root->left = new node(val);
    else
      this->_addNodeHelper(root->left, val);
  } else {
    if (!root->right)
      root->right = new node(val);
    else
      this->_addNodeHelper(root->right, val);
  }
};

void BTree::addNode(double val) {

  if (this->root)
    this->_addNodeHelper(this->root, val);
  else
    this->root = new node(val);
};

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
  printf("%.2f\n", p->prob);

  // Process left child
  printTree(p->left, indent);

  /* if (p != NULL) {
     if (p->right) {
       printTree(p->right, indent + 4);
     }
     if (indent) {
       std::cout << std::setw(indent) << ' ';
     }
     if (p->right)
       std::cout << " /\n" << std::setw(indent) << ' ';
     std::cout << p->prob << "\n ";
     if (p->left) {
       std::cout << std::setw(indent) << ' ' << " \\\n";
       printTree(p->left, indent + 4);
     }
   }*/
}

node *BTree::getRoot() { return this->root; }