#include "symbol.h"

bool Symbol::symbolIsEncodable(char symbol)
{
  return (symbol >= 32 && symbol <= 126); // might need some changes
}

void Symbol::setLabel(char label)
{
  this->label = label;
}

char Symbol::getLabel()
{
  return this->label;
}

void Symbol::setProbability(float probability)
{
  this->probability = probability;
}

float Symbol::getProbability() const
{
  return this->probability;
}

void Symbol::setFather(Symbol* symbol)
{
	fatherSymbol = symbol;
}

Symbol* Symbol::getFather()
{
	return this->fatherSymbol;
}

Symbol* Symbol::getLeftChild()
{
	return 0;
}

Symbol* Symbol::getRightChild()
{
	return 0;
}

bool Symbol::isCombined()
{
  return false;
}

void Symbol::getCodification()
{
	Symbol* father = this->getFather();

	if (father == 0)
		printf("\n");
	else
		if (father->getLeftChild() == this)
			printf("0");
		else
			printf("1");
}

CombinedSymbol::CombinedSymbol(Symbol symbol1, Symbol symbol2)
{
	this->probability = symbol1.getProbability() + symbol2.getProbability();
	this->leftChild = &symbol1;
	this->rightChild = &symbol2;
	symbol1.setFather(this);
	symbol2.setFather(this);
}

Symbol* CombinedSymbol::getLeftChild()
{
	return this->leftChild;
}

Symbol* CombinedSymbol::getRightChild()
{
	return this->rightChild;
}

bool CombinedSymbol::isCombined()
{
  return true;
}
