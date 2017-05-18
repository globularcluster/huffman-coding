#include "../include/huffman-coding.h"
#include "../include/btree.h"
#include "../include/compress.h"
#include "../include/decompress.h"
#include "../include/prob-Calc.h"
#include <algorithm>
#include <bitset>
#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

typedef unordered_map<char, boost::dynamic_bitset<>> char_bit_t;
typedef unordered_map<char, double> char_doub_t;

int main(int argc, char *argv[]) {

  string entrada = "AAAAAAAAABBBBCCCDDDEEF";

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

  decompress(charCodMap['F'], "probs.txt");
  if (argc > 1)
    string s = argv[1];

  return 0;
}

void generateHuffmanTree(vector<BTree *> &fila) {

  while (fila.size() > 1) {

    BTree *folha1 = getLowestProb(fila);
    BTree *folha2 = getLowestProb(fila);

    // cria novo node com com a soma das duas menores probabilidades
    // e os adicionam como filhos
    BTree *newNode = new BTree(folha1, folha2);

    // adiciona nova probabilidade na fila
    fila.push_back(newNode);
  }

  return;
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
  string fileName("output/probabilidades.txt");

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

void exportOriginalToBinFile(string str) {
  ofstream outfile("output/textoOriginal.bin", ofstream::binary);
  for (unsigned i = 0; i < str.length(); i++) {
    outfile << std::bitset<8>((int)str[i]);
  }

  cout << "original message saved in binary. \n";
}

void exportCodedToBinFile(string str, char_bit_t codes) {
  string file = "output/textoCodificado.bin";

  ofstream myFile(file, ios::out | ios::binary);

  for (auto i : str) {
    myFile << codes[i];
  }

  myFile.close();

  cout << "coded message saved in binary. \n";

  return;
}