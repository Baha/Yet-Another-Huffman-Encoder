/**
 * @file 
 * The file with the code for the methods of the
 * Symbol class.
 */

#include "symbol.h"

/**
 * Void constructor for the Symbol class
 */
Symbol::Symbol()
{
  this->fatherSymbol = 0;
}

/**
 * A method for determining if the symbol is encodable.
 * 
 * It is used while the input file is being read, so
 * it counts only those symbols that we want to encode.
 * 
 * @param symbol The symbol that we want to know if is
 * encodable
 */
bool Symbol::symbolIsEncodable(char symbol)
{
  return (symbol >= 32 && symbol <= 126); // might need some changes
}

/**
 * A setter for the attribute "label".
 * 
 * @param label The value that we want the "label" field
 * to be set.
 */
void Symbol::setLabel(char label)
{
  this->label = label;
}

/**
 * A getter for the attribute "label".
 */
char Symbol::getLabel()
{
  return this->label;
}

/**
 * A setter for the attribute "probability".
 * 
 * @param probability The value that we want the "probability" field
 * to be set.
 */
void Symbol::setProbability(float probability)
{
  this->probability = probability;
}

/**
 * A getter for the attribute "probability".
 */
float Symbol::getProbability() const
{
  return this->probability;
}

/**
 * A setter for the attribute "fatherSymbol".
 * 
 * @param symbol The symbol that we want the "fatherSymbol" field
 * to point.
 */
void Symbol::setFather(Symbol* symbol)
{
	fatherSymbol = symbol;
}

/**
 * A getter for the attribute "fatherSymbol".
 */
Symbol* Symbol::getFather()
{
	return this->fatherSymbol;
}

/**
 * A getter for the attribute "leftChild".
 */
Symbol* Symbol::getLeftChild()
{
	return 0;
}

/**
 * A getter for the attribute "rightChild".
 */
Symbol* Symbol::getRightChild()
{
	return 0;
}

/**
 * A getter for the attribute "codification".
 */
std::string Symbol::getCodification()
{
  return this->codification;
}

/**
 * A function to know if this is a Symbol
 * object or a CombinedSymbol object.
 *
 * (This one will return false)
 */
bool Symbol::isCombined()
{
  return false;
}

/**
 * A function to set the "codification" value to
 * the correct value once the Huffman algorithm
 * has been executed (the tree has been obtained).
 *
 * The function makes the symbol to look for its
 * fathers and getting the binary values for its
 * codification while doing it.
 */
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

/**
 * This method is recursive and it is called by the
 * symbols to get the serial corresponding to the
 * binary tree.
 *
 * If the current node is a CombinedSymbol, we
 * will make a recursive call for serializing
 * the leftChild and the RightChild, while appending
 * a 0 to the serial.
 * 
 * If it is not, then we append a 1 to the serial
 * and the label of this symbol.
 *
 * @param serial The pointer to the string where the
 * nodes will have to append the characters.
 */
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

/**
 * This method is used in the decodification step
 * to build the tree from the serial.
 *
 * It creates nodes based on the characters that
 * is reading from the serial in the input file.
 *
 * @param input The file where the serial is being
 * read.
 */
Symbol* Symbol::unserializeNode(FILE *input)
{
  char cur_c = fgetc(input);
  Symbol* newSymbol;

  if (cur_c == '0')
  {
    Symbol* symbol1 = Symbol::unserializeNode(input);
    Symbol* symbol2 = Symbol::unserializeNode(input);
    newSymbol = new CombinedSymbol(symbol1, symbol2);
  }
  else // cur_c == '1'
  {
    newSymbol = new Symbol();
    cur_c = fgetc(input);
    newSymbol->setLabel(cur_c);
  }
  return newSymbol;
}

/**
 * This methods is recursive and it is used in
 * the step of decodification.
 *
 * It will help to recollect those nodes that
 * were symbols in the original file (leaves).
 *
 * @param symbolList A point to the list where
 * the symbols will be recollected.
 */
void Symbol::addToListIfNotCombined(std::list <Symbol*> *symbolList)
{
	if (this->isCombined())
	{
		Symbol *symbol1 = getLeftChild();
		Symbol *symbol2 = getRightChild();

		symbol1->addToListIfNotCombined(symbolList);
		symbol2->addToListIfNotCombined(symbolList);
	}
	else
		symbolList->push_back(this);
}

/**
 * The only constructor for the CombinedSymbol class
 * that we will use is this one.
 *
 * It creates an object CombinedSymbol that is "father"
 * of two other symbols (from the point of view of 
 * the binary tree). This means that those two symbols
 * have been merged in one, resulting in this 
 * CombinedSymbol.
 *
 * To do so, we sum the probabilities of the child
 * symbols and we update the pointers.
 *
 * @param symbol1 The symbol that will be assigned as
 * the "leftChild" for this object.
 *
 * @param symbol2 The symbol that will be assigned as
 * the "rightChild" for this object.
 */
CombinedSymbol::CombinedSymbol(Symbol* symbol1, Symbol* symbol2)
{
	this->probability = symbol1->getProbability() + symbol2->getProbability();
	this->leftChild = symbol1;
	this->rightChild = symbol2;
	symbol1->setFather(this);
	symbol2->setFather(this);
}

/**
 * A setter for the attribute "leftChild".
 *
 * @param symbol The symbol that the "leftChild"
 * pointer should point at.
 */
void CombinedSymbol::setLeftChild(Symbol* symbol)
{
  this->leftChild = symbol;
  symbol->setFather(this);
}

/**
 * A setter for the attribute "rightChild".
 *
 * @param symbol The symbol that the "rightChild"
 * pointer should point at.
 */
void CombinedSymbol::setRightChild(Symbol* symbol)
{
  this->rightChild = symbol;
  symbol->setFather(this);
}

/**
 * A getter for the attribute "leftChild".
 */
Symbol* CombinedSymbol::getLeftChild()
{
	return this->leftChild;
}

/**
 * A getter for the attribute "leftChild".
 */
Symbol* CombinedSymbol::getRightChild()
{
	return this->rightChild;
}

/**
 * A function to know if this is a Symbol
 * object or a CombinedSymbol object.
 *
 * (This one will return true)
 */
bool CombinedSymbol::isCombined()
{
  return true;
}
