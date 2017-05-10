#include "../include/prob-Calc.h"
#include <iostream>
#include <unordered_map>

// Ainda não calcula a probabilidade, só faz a contagem
// O "&" faz com que o map seja passado por referência
void calcProb(unordered_map<char, double> &probMap, string str) {

  // Maneira bem elegante de fazer uma contagem em Map
  for (char &c : str) {
    //probMap[c]++;
    probMap[c]+= 100.0/str.length();
  }

  return;
}

void printProb(unordered_map<char, double> &probMap) {

  unordered_map<char, double>::iterator p;
  for (auto &p : probMap)
    cout << "(" << p.first << ", " << p.second << ")\n";

  return;
}