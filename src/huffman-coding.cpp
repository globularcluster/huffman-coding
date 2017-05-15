#include "../include/btree.h"
#include "../include/prob-Calc.h"
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
int main() {

  string entrada = "AAAAAAAAABBBBCCCDDDEEF";
  unordered_map<char, double> probOfChars;

  calcProb(probOfChars, entrada);
  printProb(probOfChars);

  // vetor para pegar valores (probabilidades) e
  // TO DO: posteriormente ordenalos
  vector<double> values;
  values.reserve(probOfChars.size());
  for (auto v : probOfChars) {
    values.push_back(v.second);
  }

  BTree *tree = new BTree();

  // insere todos valores na árvore
  for (auto i : values) {
    tree->addNode(i);
    cout << i << "\t - ";
  }
  cout << "\n";

  // a árvore é visualmente vista da esquerda pra direita
  // invés de cima para baixo
  tree->printTree(tree->getRoot());

  return 0;
}
