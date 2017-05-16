#include "../include/btree.h"
#include "../include/prob-Calc.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

BTree *getLowestProb(vector<BTree *> &fila);

int main() {

  string entrada = "AAAAAAAAABBBBCCCDDDEEF";
  unordered_map<char, double> probOfChars;

  calcProb(probOfChars, entrada);
  // printProb(probOfChars);

  vector<BTree *> filaDePrioridades;
  for (auto n : probOfChars) {
    BTree *folha = new BTree(n.second, n.first);
    filaDePrioridades.push_back(folha);
  }

  // ALGORITMO PARA GERAR A ÁRVORE
  while (filaDePrioridades.size() > 1) {

    BTree *folha1 = getLowestProb(filaDePrioridades);
    BTree *folha2 = getLowestProb(filaDePrioridades);

    // cria novo node com com a soma das duas menores probabilidades
    // e os adicionam como filhos
    BTree *newNode = new BTree(folha1, folha2);

    // adiciona nova probabilidade na fila
    filaDePrioridades.push_back(newNode);
  }

  cout << "\nok";

  BTree *tree = filaDePrioridades[0];

  return 0;
}

// retorna folha com menor probabilidade e
// já a deleta da fila!
BTree *getLowestProb(vector<BTree *> &fila) {

  double menorProb = fila.front()->getProb();
  BTree *folhaMenorProb = fila.front();

  // busca node com menor probabilidade
  for (auto i : fila) {
    if (i->getProb() < menorProb) {
      menorProb = i->getProb();
      folhaMenorProb = i;
    }
  }

  // deleta o respectivo node da fila
  // esse for feio é porque preciso pegar o indice do vetor
  for (vector<BTree *>::size_type i = 0; i != fila.size(); ++i) {
    if (fila[i]->getProb() == folhaMenorProb->getProb() &&
        fila[i]->getChar() == folhaMenorProb->getChar()) {

      fila.erase(fila.begin() + i);

      return folhaMenorProb;
    }
  }
  return folhaMenorProb;
}