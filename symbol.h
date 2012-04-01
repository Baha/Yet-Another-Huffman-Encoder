#ifndef _SYMBOL_H_
#define _SYMBOL_H_

class Symbol
{
  char label;
  float probability;
public:
  static bool symbolIsEncodable(char symbol);
  void setLabel(char label);
  char getLabel();
  void setProbability(float probability);
  float getProbability();
  virtual bool isCombined();
};

class CombinedSymbol : public Symbol
{
  Symbol *symbol1, *symbol2;
  bool isCombined();
};

#endif 
