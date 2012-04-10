#ifndef _SOURCE_H_
#define _SOURCE_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <list>
#include <vector>
#include <queue>
#include <string>
#include "symbol.h"

class Source
{
  std::map <char, unsigned int> symbolCounter;
  std::map <char, std::string> codificationTable;
	std::map <std::string, char> decodificationTable;
  std::list <Symbol*> symbolList;
  Symbol* rootSymbol;
  unsigned int totalSymbols;
  std::string serial;
public:  
  void getFrequencies(FILE *input);
  void getProbabilities();
  void getProperties(FILE *input);
  std::string getSerial();
	void solveHuffman();
  void serializeTree();
  void unserializeTree(FILE *input);
  void writeCodifiedFile(char* inputFileName);
  void writeUncodifiedFile(FILE *input, char* outputFileName);
	void buildSymbolList();
	void buildCodeList();
	bool stringInCodeList(std::string binaryString);
  void showProperties();
};

#endif 
