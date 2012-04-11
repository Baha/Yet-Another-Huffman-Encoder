/**
 * @file
 * Defines the structure of the Source class.
 */

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

/**
 * The source class is the main class of the program.
 *
 * We will use one Source class in the main program
 * in order to do the operations we want.
 *
 * Taking a look to the different main.cpp files for
 * the different modules will help us to understand
 * how to use this methods for codifying and decodifying.
 */
class Source
{
	/**
	 * The "symbolCounter" structure will help us
	 * to count the symbols in the file, so we can
	 * extract later the probabilities for that symbol.
	 */
  std::map <char, unsigned int> symbolCounter;
	/**
	 * The "codificationTable" is a table that relates
	 * the label of a symbol to the string of 0s and 1s
	 * (binary code) corresponding to that label.
	 *
	 * It is used in the codification of a file.
	 */
  std::map <char, std::string> codificationTable;
	/**
	 * The "decodificationTable" is a table that relates
	 * the string of 0s and 1s (binary code) with the label
	 * of a symbol.
	 *
	 * It is used in the decodification of a file.
	 */
	std::map <std::string, char> decodificationTable;
	/**
	 * The "symbolList" list will store the simple
	 * symbols of the process, this is, the objects
	 * of the class Symbol (not the ones from the
	 * CombinedSymbol class) created after counting
	 * frequencies or reading a serial from file.
	 */
  std::list <Symbol*> symbolList;
	/**
	 * The "rootSymbol" is a pointer to the object
	 * that is in the root of the binary tree.
	 *
	 * This way we can trigger the serializing methods
	 * easily.
	 */
  Symbol* rootSymbol;
  /**
	 * A counter for the number of symbols read in the
	 * input file.
	 */
  unsigned int totalSymbols;
	/**
	 * The serial for the describing the binary tree.
	 * It is a binary code which can be composed in two
	 * different ways: by looking at the binary tree or
	 * by reading it from a file.
	 */
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
