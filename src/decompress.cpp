#include "../include/decompress.h"
#include "../include/btree.h"
#include "../include/compress.h"
#include "../include/huffman-coding.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;
typedef std::unordered_map<char, double> char_doub_t;
typedef unordered_map<char, boost::dynamic_bitset<>> char_bit_t;

void decompress(boost::dynamic_bitset<> compressed, std::string Filein) {

  char_doub_t charsProbs = getProbs(Filein);

  vector<BTree *> filaPrioridades;
  for (auto n : charsProbs) {
    BTree *folha = new BTree(n.second, n.first);
    filaPrioridades.push_back(folha);
  }

  generateHuffmanTree(filaPrioridades);

  BTree *huffTree = filaPrioridades[0];
  cout << "decompressed tree: " << endl;
  huffTree->printTree(huffTree->getRoot());

  char_bit_t charCod;
  charCod = calcCodMap(charsProbs, huffTree);

  exportDecodedToASCII(charCod, compressed);

  return;
}

char_doub_t getProbs(string file) {

  char_doub_t probs;
  char c;
  string s;
  ifstream inStream(file);

  if (inStream.is_open()) {

    while (inStream.get(c)) {
      getline(inStream, s);

      const char *ch = s.c_str();
      probs[c] = std::atof(ch);
    }
  } else {
    cout << "não foi possível abrir o arquivo codificado." << endl;
  }

  /*for (auto i : probs)
    cout << i.first << " - " << i.second << endl;*/

  return probs;
}

void exportDecodedToASCII(char_bit_t charCod,
                          boost::dynamic_bitset<> compressed) {

  string s;
  char ch = 0;
  boost::dynamic_bitset<> charac;

  // para todo bit comprimido
  for (int i = compressed.size() - 1; i >= 0; --i) {

    // aumenta um bit e shift pra esquerda
    charac.resize(charac.size() + 1);
    charac = charac << 1;

    // se o bit comprimido lido for 1, bit menos significativo é setado.
    if (compressed[i])
      charac[0].flip();

    // procura pelo char pelo seu respectivo bit codificado
    for (auto c : charCod) {
      // se achar, concatena char na string final
      if (c.second == charac) {
        s += c.first;
        charac.resize(0); // e zera a parada loca
      }
    }
  }
  cout << s << endl;

  return;
}
