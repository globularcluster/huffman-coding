#include "../include/util.h"
#include "../include/btree.h"
#include "../include/compress.h"
#include "../include/decompress.h"
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

int main(int argc, char *argv[]) {

//Lê arquivo de entrada por linha de comando
  string entrada = argv[1];


  char_doub_t probOfChars;
  calcProb(probOfChars, entrada);
  // printMap(probOfChars);

  saveProbs(probOfChars);

  vector<BTree *> filaDePrioridades;
  for (auto n : probOfChars) {
    BTree *folha = new BTree(n.second, n.first);
    filaDePrioridades.push_back(folha);
  }

  // ALGORITMO PARA GERAR A ÁRVORE
  generateHuffmanTree(filaDePrioridades);

  BTree *huffmanTree = filaDePrioridades[0];
  // huffmanTree->printTree(huffmanTree->getRoot());

  char_bit_t charCodMap;
  charCodMap = calcCodMap(probOfChars, huffmanTree);

  exportOriginalToBinFile(entrada);
  exportCodedToBinFile(entrada, charCodMap);

  // decompress(charCodMap['F'], "probs.txt");

  return 0;
}
