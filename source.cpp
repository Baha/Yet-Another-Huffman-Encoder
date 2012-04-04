#include "source.h"

void Source::getFrequencies(FILE *input)
{
  FILE *in = input;
  char cur_c;
  std::map<char, unsigned int>::iterator it;

  symbolCounter.clear();
  totalSymbols = 0;
  
  cur_c = fgetc(in);

  while (cur_c != EOF)
  {
    if (Symbol::symbolIsEncodable(cur_c))
    {
      it = symbolCounter.find(cur_c);
      totalSymbols++;
      if (it == symbolCounter.end())
        symbolCounter[cur_c] = 1;
      else
        symbolCounter[cur_c]++;
    }
    cur_c = fgetc(in);
  }
}

void Source::getProbabilities()
{
  std::map<char, unsigned int>::iterator it;

  for (it = symbolCounter.begin(); it != symbolCounter.end();it++)
  {
    float lab = (*it).first;
    float prob = (float)((*it).second) / (float)totalSymbols;
    Symbol newSymbol;

    newSymbol.setLabel(lab);
    newSymbol.setProbability(prob);

    symbolList.push_back(newSymbol);
  }
}

void Source::getProperties(FILE *input)
{
  this->getFrequencies(input);
  this->getProbabilities();
}

void Source::solveHuffman()
{
	std::priority_queue <Symbol, std::vector <Symbol> , SymbolComp> symbolQueue; 
	std::list <Symbol>::iterator it;

	for (it = symbolList.begin(); it != symbolList.end(); it++)
	{
		Symbol newSymbol(*it);
		symbolQueue.push(newSymbol);
	}

	while (symbolQueue.size() > 1)
	{
		Symbol symbol1 = symbolQueue.top();
		symbolQueue.pop();

		Symbol symbol2 = symbolQueue.top();
		symbolQueue.pop();

		CombinedSymbol newCombinedSymbol(symbol1, symbol2);
		symbolQueue.push(newCombinedSymbol);
	}
}

void Source::showProperties()
{
  //debug version
  std::map<char, unsigned int>::iterator it;
  std::list <Symbol>::iterator it2;

  printf("Total number of symbols read: %d\n", totalSymbols);
  printf("The frequencies for this file are...\n");

  for (it = symbolCounter.begin(); it != symbolCounter.end();it++)
    printf("%c => %d\n", (*it).first, (*it).second); 
  
  printf("\n");
  printf("The probabilities for this file are...\n");

  for (it2 = symbolList.begin(); it2 != symbolList.end(); it2++)
    printf("%c => %f\n", it2->getLabel(), it2->getProbability());
  
  printf("\n");
}
