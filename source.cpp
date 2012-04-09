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
    Symbol* newSymbol = new Symbol();

    newSymbol->setLabel(lab);
    newSymbol->setProbability(prob);

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
	std::priority_queue <Symbol*, std::vector <Symbol*> , SymbolComp> symbolQueue; 
	std::list <Symbol*>::iterator it;

	for (it = symbolList.begin(); it != symbolList.end(); it++)
		symbolQueue.push(*it); 

	while (symbolQueue.size() > 1)
	{
		Symbol* symbol1 = symbolQueue.top();
		symbolQueue.pop();

		Symbol* symbol2 = symbolQueue.top();
		symbolQueue.pop();

		CombinedSymbol* newCombinedSymbol = new CombinedSymbol(symbol1, symbol2);
		symbolQueue.push(newCombinedSymbol);
	}
  rootSymbol = symbolQueue.top();
}

void Source::showProperties()
{
  //debug version
  std::map<char, unsigned int>::iterator it;
  std::list <Symbol*>::iterator it2;

  printf("Total number of symbols read: %d\n", totalSymbols);
  printf("The frequencies for this file are...\n");

  for (it = symbolCounter.begin(); it != symbolCounter.end();it++)
    printf("%c => %d\n", (*it).first, (*it).second); 
  
  printf("\n");
  printf("The probabilities for this file are...\n");

  for (it2 = symbolList.begin(); it2 != symbolList.end(); it2++)
    printf("%c => %f\n", (*it2)->getLabel(), (*it2)->getProbability());
  
  printf("\n");
  printf("The codifications for the symbols are...\n");

  for (it2 = symbolList.begin(); it2 != symbolList.end(); it2++)
  {
    (*it2)->obtainCodification();
    printf("%c => %s\n", (*it2)->getLabel(), ((*it2)->getCodification()).c_str());
  }
  printf("\n");
}
