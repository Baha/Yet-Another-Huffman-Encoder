#ifndef _SOURCE_H_
#define _SOURCE_H_

#include <cstdio>
#include <map>
#include "symbol.h"

class Source
{
  Symbol *symbols;
  std::map <char, unsigned int> symbolCounter;
public:  
  void getFrequencies(FILE *input);
  void getProbabilities();
  void getProperties(FILE *input);
  void showProperties();
};

#endif 
