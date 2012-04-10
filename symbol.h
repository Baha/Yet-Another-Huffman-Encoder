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
	/**
	 * Void constructor for the Symbol class
	 */
  Symbol();

	/**
	 * A method for determining if the symbol is encodable.
	 * 
	 * It is used while the input file is being read, so
	 * it counts only those symbols that we want to encode.
	 * 
	 * @param symbol The symbol that we want to know if is
	 * encodable
	 */
  static bool symbolIsEncodable(char symbol);

	/**
	 * A setter for the attribute "label".
	 * 
	 * @param label The value that we want the "label" field
	 * to be set.
	 */
  void setLabel(char label);

	/**
	 * A getter for the attribute "label".
	 */
  char getLabel();
	/**
	 * A setter for the attribute "probability".
	 * 
	 * @param probability The value that we want the "probability" field
	 * to be set.
	 */
  void setProbability(float probability);
	/**
	 * A getter for the attribute "probability".
	 */
  float getProbability() const;
	/**
	 * A setter for the attribute "fatherSymbol".
	 * 
	 * @param symbol The symbol that we want the "fatherSymbol" field
	 * to point.
	 */
	void setFather(Symbol* symbol);
	/**
	 * A getter for the attribute "fatherSymbol".
	 */
	Symbol* getFather();
	/**
	 * A getter for the attribute "leftChild".
	 */
	virtual Symbol* getLeftChild();
	/**
	 * A getter for the attribute "rightChild".
	 */
	virtual Symbol* getRightChild();
	/**
	 * A getter for the attribute "codification".
	 */
	std::string getCodification();
	/**
	 * A virtual function to know if this is a Symbol
	 * object or a CombinedSymbol object.
	 */
  virtual bool isCombined();
	/**
	 * A function to set the "codification" value to
	 * the correct value once the Huffman algorithm
	 * has been executed (the tree has been obtained).
	 *
	 * The function makes the symbol to look for its
	 * fathers and getting the binary values for its
	 * codification while doing it.
	 */
  void obtainCodification();
	/**
	 * 
	 */
  void serializeNode(std::string* serial);
  static Symbol* unserializeNode(FILE* input);
	void addToListIfNotCombined(std::list <Symbol*> *symbolList);
};

class CombinedSymbol : public Symbol
{
public:
  CombinedSymbol(){ }; //FIXME
	CombinedSymbol(Symbol* symbol1, Symbol* symbol2);
  void setLeftChild(Symbol* symbol);
  void setRightChild(Symbol* symbol);
	Symbol* getLeftChild();
	Symbol* getRightChild();
  bool isCombined();
};

struct SymbolComp : public std::binary_function < Symbol, Symbol, bool >
{
	bool operator ()(Symbol* symbol1, Symbol* symbol2) const
	{
		return (symbol1->getProbability() > symbol2->getProbability());
	}
};

#endif 
