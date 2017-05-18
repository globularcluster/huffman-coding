#ifndef __COMPRESS_H_INCLUDED__
#define __COMPRESS_H_INCLUDED__

#include "btree.h"
#include <boost/dynamic_bitset.hpp>
#include <iostream>
#include <unordered_map>

typedef std::unordered_map<char, boost::dynamic_bitset<>> char_bit_t;
typedef std::unordered_map<char, double> char_doub_t;

char_bit_t calcCodMap(char_doub_t chars, BTree *tree);

#endif