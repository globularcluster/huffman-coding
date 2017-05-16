#ifndef __CALCPROB_H_INCLUDED__
#define __CALCPROB_H_INCLUDED__

#include <unordered_map>

using namespace std;

void calcProb(unordered_map<char, double> &probMap, string str);
void printMap(unordered_map<char, double> &probMap);

#endif