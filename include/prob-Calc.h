#ifndef __CALCPROB_H_INCLUDED__
#define __CALCPROB_H_INCLUDED__

#include <unordered_map>

using namespace std;

void calcProb(unordered_map<char, int> &probMap, string str);
void printProb(unordered_map<char, int> &probMap);

#endif