/**
 * @file
 * Defines the structure of the Symbol class and the
 * classes related to it.
 */

#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <iostream>
#include <cstdio>
#include <string>
#include <list>

/**
 * The Symbol class is the basic class for representing
 * an encodable character.
 *
 * Usually, a source is composed of two tuples of the same
 * length: One for describing the symbols of the alphabet
 * and another one for the values of the emission 
 * probabilities of these symbols.
 *
 * We pack both values into one class, making it easier
 * to access this values.
 */

class Symbol
{
protected:
	/**
	 * The "label" attribute is set to the character that is
	 * used to represent the symbol in the file.
	 *
	 * Note that this program will work OK if the input
	 * file contains only ASCII characters. Otherwise,
	 * the characters can not be stored in these labels
	 * if the codification needs more than 8 bits.
	 */
  char label;
	/**
	 * The "probability" attribute stores the emission
	 * probability of the symbol.
	 */
  float probability;
	/**
	 * The "codification" attribute will store a string of
	 * 0s and 1s once the Huffman algorithm is executed
	 * and the codification for this symbol is obtained
	 */
  std::string codification;
	/**
	 * The "fatherSymbol" is a pointer used for storing
	 * the ascendant node in the binary tree.
	 */
	Symbol *fatherSymbol;
	/**
	 * This pointer is used in the CombinedSymbol class
	 * only. Its purpose is to store the descendant nodes
	 * in the binary tree.
	 */
  Symbol *leftChild;
	/**
	 * This pointer is used in the CombinedSymbol class
	 * only. Its purpose is to store the descendant nodes
	 * in the binary tree.
	 */
	Symbol *rightChild;
public:
  Symbol();
  static bool symbolIsEncodable(char symbol);
  void setLabel(char label);
  char getLabel();
  void setProbability(float probability);
  float getProbability() const;
	void setFather(Symbol* symbol);
	Symbol* getFather();
	virtual Symbol* getLeftChild();
	virtual Symbol* getRightChild();
	std::string getCodification();
  virtual bool isCombined();
  void obtainCodification();
  void serializeNode(std::string* serial);
  static Symbol* unserializeNode(FILE* input);
	void addToListIfNotCombined(std::list <Symbol*> *symbolList);
};

/**
 * The CombinedSymbol class represents the union of two
 * symbols in one, and it is necessary for obtaining the
 * solution of the Huffman algorithm.
 *
 * This will be the class of the nodes that are not leaves
 * in the binary tree.
 *
 * The "label" atributte is not used.
 */
class CombinedSymbol : public Symbol
{
public:
	CombinedSymbol(Symbol* symbol1, Symbol* symbol2);
  void setLeftChild(Symbol* symbol);
  void setRightChild(Symbol* symbol);
	Symbol* getLeftChild();
	Symbol* getRightChild();
  bool isCombined();
};

/**
 * This structure is a functor for the priority queue that will
 * be used in the source class for executing the Huffman algorithm.
 *
 * It only includes the operator for comparing two elements of the
 * Symbol class between them so the priority queue can sort the
 * elements automatically.
 */
struct SymbolComp : public std::binary_function < Symbol, Symbol, bool >
{
	/**
	 * The operator for comparing two Symbol objects.
	 *
	 * It is made so the symbol with less probability will be closer
	 * to the top of the symbols, this is, the queue will be sorted
	 * in ascending order of probability.
	 *
	 * This way we can get the symbols with lower probabilities from
	 * the top.
	 */
	bool operator ()(Symbol* symbol1, Symbol* symbol2) const
	{
		return (symbol1->getProbability() > symbol2->getProbability());
	}
};

#endif 
