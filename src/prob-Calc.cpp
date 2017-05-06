#include "../include/prob-Calc.h"
#include <iostream>
#include <unordered_map>

// Ainda não calcula a probabilidade, só faz a contagem
// O "&" faz com que o map seja passado por referência
void calcProb(unordered_map<char, int> &probMap, string str) {

  // Maneira bem elegante de fazer uma contagem em Map
  for (char &c : str) {
    probMap[c]++;
  }

  return;
}

void printProb(unordered_map<char, int> &probMap) {

  unordered_map<char, int>::iterator p;
  for (auto &p : probMap)
    cout << "(" << p.first << ", " << p.second << ")\n";

  return;
}