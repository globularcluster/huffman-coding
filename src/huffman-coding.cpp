#include "../include/btree.h"
#include "../include/prob-Calc.h"
#include <algorithm>
#include <bitset>
#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

typedef unordered_map<char, boost::dynamic_bitset<>> char_bit_t;
typedef unordered_map<char, double> char_doub_t;

BTree *getLowestProb(vector<BTree *> &fila);
void saveProbs(char_doub_t map);
char_bit_t calcCodMap(char_doub_t chars, BTree *tree);
void exportOriginalToBinFile(string str);

int main() {

  string entrada = "AAAAAAAAABBBBCCCDDDEEF";

  char_doub_t probOfChars;

  calcProb(probOfChars, entrada);
  printMap(probOfChars);

  saveProbs(probOfChars);

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

  BTree *tree = filaDePrioridades[0];

  tree->printTree(tree->getRoot());

  char_bit_t charCodMap;
  charCodMap = calcCodMap(probOfChars, tree);
  exportOriginalToBinFile(entrada);


  // maneiro
  /* boost::dynamic_bitset<> db;
   db.push_back(true);
   cout << db << "\n";
   db.resize(db.size() + 1);
   cout << db << "\n";
   db = db << 1;
   cout << db << "\n";
   boost::dynamic_bitset<> db2{1, 1};
   db[0].flip();*/

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

void saveProbs(char_doub_t map) {

  ofstream outStream;
  string fileName("output.txt");

  outStream.open(fileName);

  vector<double> values;
  for (auto n : map)
    values.push_back(n.second);

  sort(values.begin(), values.end(), std::greater<int>());

  for (auto it : values) {
    for (auto iter : map) {
      if (iter.second == it) {
        outStream << iter.first << "\t" << iter.second << "\n";
        map.erase(iter.first);
        break;
      }
    }
  }

  outStream.close();
  cout << "file \"" + fileName + "\" saved\n";

  return;
}

char_bit_t calcCodMap(char_doub_t chars, BTree *tree) {

  char_bit_t cods;

  vector<char> c;
  for (auto i : chars)
    c.push_back(i.first);

  for (auto charac : c) {
    auto root = tree->getRoot();

    // cout << charac << "\n";

    while (root->charac != charac) {

      if (root->left->auxChars.find(charac) != std::string::npos) {
        cods[charac].resize(cods[charac].size() + 1);
        cods[charac] = cods[charac] << 1;
        cods[charac][0].flip();
        root = root->left;
        // cout << "\t" << cods[charac] << "\tleft\n";
      } else {
        cods[charac].resize(cods[charac].size() + 1);
        cods[charac] = cods[charac] << 1;
        root = root->right;
        // cout << "\t" << cods[charac] << "\tright\n";
      }
    }
  }

  for (auto c : cods) {
    cout << "(" << c.first << ", " << c.second << ")\n";
  }
  return cods;
}

void exportOriginalToBinFile(string str){
  ofstream outfile("textoOriginalBin.txt", ofstream::binary);
  for (int i = 0; i < str.length(); i++)
    {
        outfile << std::bitset<8>((int)str[i]);
    }



cout << "file saved\n";


}
