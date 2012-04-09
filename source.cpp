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

std::string Source::getSerial()
{
  return this->serial; 
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
  // for serializing later...
  rootSymbol = symbolQueue.top();

  // for codifying later...
  codificationTable.clear();

  for (it = symbolList.begin(); it != symbolList.end(); it++)
  { 
    (*it)->obtainCodification();
    codificationTable[(*it)->getLabel()] = (*it)->getCodification();
  }
}

// maybe we can do an iterative version later...
void Source::serializeTree()
{
  serial = "";
  rootSymbol->serializeNode(&serial);
}

void Source::unserializeTree(FILE *input)
{
  char cur_c = fgetc(input);

  if (cur_c == '0')
  {
    Symbol* symbol1 = Symbol::unserializeNode(input);
    Symbol* symbol2 = Symbol::unserializeNode(input);
    rootSymbol = new CombinedSymbol(symbol1, symbol2);
  }
  else
  {
    rootSymbol = new Symbol();
    cur_c = fgetc(input);
    rootSymbol->setLabel(cur_c);
  }
  this->serializeTree();
}

void Source::writeCodifiedFile(char* inputFileName)
{
  FILE *input;
  FILE *output;
  std::string outputFileName;
  char* dotPointer;
  char cur_input;

  input = fopen(inputFileName, "r");

  if (input == NULL)
  {
    printf("Fichero de entrada no encontrado.\n");
    exit(-1);
  }

  dotPointer = strchr(inputFileName, '.');

  if (dotPointer != NULL)
    *dotPointer = '\0';
    
  outputFileName = inputFileName;
  outputFileName += ".huf";

  output = fopen(outputFileName.c_str(), "w");
  
  if (output == NULL)
  {
    printf("Fichero de salida no pudo crearse.\n");
    exit(-1);
  }
  
  // write serial
  fprintf(output, "%s\n", (this->getSerial().c_str())); 

  // a partir de aqui, operar con los ficheros
  cur_input = fgetc(input);

  while (cur_input != EOF)
  {
    if (Symbol::symbolIsEncodable(cur_input))
      fprintf(output, "%s", codificationTable[cur_input].c_str());
    // next 2 lines are for debugging only
    else if (cur_input == '\n')
      fprintf(output, "\n");
    // until here
    cur_input = fgetc(input);
  }

  fclose(input);
  fclose(output);
}

void Source::writeUncodifiedFile(FILE* input, char* outputFileName)
{

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
    printf("%c => %s\n", (*it2)->getLabel(), ((*it2)->getCodification()).c_str());
  }
  printf("\n");
}
