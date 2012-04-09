#ifndef _SOURCE_H_
#define _SOURCE_H_

#include <cstdio>
#include <map>
#include <list>
#include <vector>
#include <queue>
#include "symbol.h"

class Source
{
  std::map <char, unsigned int> symbolCounter;
  std::list <Symbol*> symbolList;
  Symbol* rootSymbol;
  unsigned int totalSymbols;
public:  
  void getFrequencies(FILE *input);
  void getProbabilities();
  void getProperties(FILE *input);
	void solveHuffman();
  void showProperties();
};

#endif 
