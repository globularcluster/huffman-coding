#include "../include/prob-Calc.h"
#include <iostream>
#include <unordered_map>

using namespace std;
int main() {

  string entrada = "AAAAABBCCCEFF";
  unordered_map<char, int> probOfChars;

  calcProb(probOfChars, entrada);
  printProb(probOfChars);

  return 0;
}
