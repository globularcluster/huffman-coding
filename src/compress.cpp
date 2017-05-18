#include "../include/compress.h"
#include <iostream>
#include <vector>

typedef std::unordered_map<char, boost::dynamic_bitset<>> char_bit_t;

char_bit_t calcCodMap(char_doub_t chars, BTree *tree) {

  char_bit_t cods;

  std::vector<char> c;
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

  /* for (auto c : cods) {
     cout << "(" << c.first << ", " << c.second << ")\n";
   }*/
  return cods;
}