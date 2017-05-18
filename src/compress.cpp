#include "../include/compress.h"
#include "../include/btree.h"
#include "../include/decompress.h"
#include "../include/prob-Calc.h"
#include "../include/util.h"
#include <algorithm>
#include <bitset>
#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

typedef std::unordered_map<char, boost::dynamic_bitset<>> char_bit_t;

void huffmanCompress(string entrada) {

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
}
