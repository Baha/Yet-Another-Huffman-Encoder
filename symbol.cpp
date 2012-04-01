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

float Symbol::getProbability()
{
  return this->probability;
}

bool Symbol::isCombined()
{
  return false;
}

bool CombinedSymbol::isCombined()
{
  return true;
}
