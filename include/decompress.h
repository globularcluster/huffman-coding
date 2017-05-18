#ifndef __DECOMPRESS_H_INCLUDED__
#define __DECOMPRESS_H_INCLUDED__

#include <boost/dynamic_bitset.hpp>
#include <string>
#include <unordered_map>

using namespace std;

typedef unordered_map<char, double> char_doub_t;
typedef unordered_map<char, boost::dynamic_bitset<>> char_bit_t;

void decompress(string compressedFile, string probabilidadesFile);
char_doub_t getProbs(std::string file);
void exportDecodedToASCII(char_bit_t charCod,
                          boost::dynamic_bitset<> compressed);
void loadBitsFile(string str, boost::dynamic_bitset<> &db);

#endif