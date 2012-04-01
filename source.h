#ifndef _SOURCE_H_
#define _SOURCE_H_

#include <cstdio>
#include <map>
#include <list>
#include "symbol.h"

class Source
{
  Symbol *symbols;
  std::map <char, unsigned int> symbolCounter;
  std::list <Symbol> symbolList;
  unsigned int totalSymbols;
public:  
  void getFrequencies(FILE *input);
  void getProbabilities();
  void getProperties(FILE *input);
  std::list <Symbol> getSymbolList();
  void showProperties();
};

#endif 
