#ifndef __HUFFMANCODING_H_INCLUDED__
#define __HUFFMANCODING_H_INCLUDED__

#include "../include/btree.h"
#include <unordered_map>
#include <vector>

using namespace std;

typedef unordered_map<char, boost::dynamic_bitset<>> char_bit_t;
typedef unordered_map<char, double> char_doub_t;

void generateHuffmanTree(vector<BTree *> &fila);
BTree *getLowestProb(vector<BTree *> &fila);
void saveProbs(char_doub_t map);
void exportOriginalToBinFile(string str);
void exportCodedToBinFile(string str, char_bit_t codes);

#endif
