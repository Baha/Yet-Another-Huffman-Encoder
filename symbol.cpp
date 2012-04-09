#include "symbol.h"

Symbol::Symbol()
{
  this->fatherSymbol = 0;
}

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

std::string Symbol::getCodification()
{
  return this->codification;
}

bool Symbol::isCombined()
{
  return false;
}

void Symbol::obtainCodification()
{
	Symbol* father = this->getFather();
  Symbol* child = this;
  std::string tmpCodification = "";

	while (!(father == 0))
  {
		if (father->getLeftChild() == child)
			tmpCodification.push_back('0');
		else if (father->getRightChild() == child)
      tmpCodification.push_back('1');
    father = father->getFather();
    child = child->getFather();
  }

  codification = "";
  for (int i = tmpCodification.length() - 1; i >= 0; i--)
    codification.push_back(tmpCodification[i]);
}

void Symbol::serializeNode(std::string* serial)
{
  if (this->isCombined())
  {
    serial->append("0");
    leftChild->serializeNode(serial);
    rightChild->serializeNode(serial);
  }
  else
  {
    serial->append("1");
    serial->push_back(this->getLabel());
  }
}

CombinedSymbol::CombinedSymbol(Symbol* symbol1, Symbol* symbol2)
{
	this->probability = symbol1->getProbability() + symbol2->getProbability();
	this->leftChild = symbol1;
	this->rightChild = symbol2;
	symbol1->setFather(this);
	symbol2->setFather(this);
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
