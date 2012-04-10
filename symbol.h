#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <iostream>
#include <cstdio>
#include <string>
#include <list>

class Symbol
{
protected:
  char label;
  float probability;
  std::string codification;
	Symbol *fatherSymbol;
  Symbol *leftChild, *rightChild;
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
