#include "../include/btree.h"
#include "../include/prob-Calc.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

char getLowestProb(unordered_map<char, double> map, double d);

int main() {

  string entrada = "AAAAAAAAABBBBCCCDDDEEF";
  unordered_map<char, double> probOfChars;

  calcProb(probOfChars, entrada);
  printProb(probOfChars);

  // vetor para pegar valores (probabilidades) e
  vector<double> values;
  values.reserve(probOfChars.size());
  for (auto v : probOfChars) {
    values.push_back(v.second);
  }

  BTree *tree = new BTree();

  // insere todos valores na árvore
  for (auto i : values) {
    // tree->addNode(i);
    cout << i << "\t - ";
  }
  cout << "\n";

  // a árvore é visualmente vista da esquerda pra direita
  // invés de cima para baixo
  // tree->printTree(tree->getRoot());

  // ordena com parâmetro default: crescente
  sort(values.begin(), values.end(), greater<int>());

  cout << "[debug] sort: \n";
  for (auto i : values)
    cout << i << "\t - ";
  cout << "\n";

  BTree *tree2 = new BTree();

  // ALGORITMO PARA GERAR A ÁRVORE
  while (values.size()) {
    double p1, p2;
    char c1, c2;

    p1 = values.back();
    c1 = getLowestProb(probOfChars, p1);
    values.pop_back(); // remove menor probabilidade

    p2 = values.back();
    c2 = getLowestProb(probOfChars, p2);
    values.pop_back();

    BTree *sDir = new BTree(p1, c1);
    BTree *sEsq = new BTree(p2, c2);

    // cria novo node com com a soma das duas menores probabilidades
    // e os adicionam como filhos
    BTree *newNode = new BTree(sDir, sEsq);

    tree2->addNode(newNode);

    // adiciona nova soma de probabilidade na fila
    values.push_back(newNode->getRoot()->prob);
    sort(values.begin(), values.end(), greater<int>());
  }

  tree2->printTree(tree2->getRoot());

  return 0;
}

char getLowestProb(unordered_map<char, double> map, double d) {

  // busca char correspondente da probabilidade
  for (auto i : map) {
    if (i.second == d)
      return i.first;
  }

  cout << "char não encontrado\n";
  return 0;
}