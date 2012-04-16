#include "source.h"

/**
 * This methods reads the input file looking for the
 * symbols to be encoded, and puts them on a table
 * with the purpose of counting the number of
 * appearances.
 *
 * @param input The file that we are reading from. 
 */
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

/**
 * After counting the frequencies, the next step is to
 * get the total probabilities.
 *
 * Later, we create the basic symbols for the source with
 * the data we have analyzed and we put them on the symbol
 * list.
 */
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

/**
 * This is a wrapper for getting the frequencies
 * and then the probabilities.
 */
void Source::getProperties(FILE *input)
{
  this->getFrequencies(input);
  this->getProbabilities();
}

/**
 * A getter for the attribute "serial".
 */
std::string Source::getSerial()
{
  return this->serial; 
}

/**
 * The algorithm for solving the Huffman encoding is a greedy algorithm
 * that must select the two symbols with the lowest probabilites and add
 * another one with sum of its probabilities.
 *
 * This can be solved by using a priority queue as I did, and in fact, it
 * is an optimal solution:
 * 
 * We just create the queue associating it to the functor we created for
 * establishing an ascendant order in the queue.
 *
 * Later we add the elements from the symbol list, and then we start the
 * algorithm, popping 2 symbols from the queue and adding another one that
 * we create from the symbols we extracted before.
 *
 * Finally, we store the last element on the queue (the root node for the
 * tree) and we obtain the codification for the symbols in the original
 * symbol list.
 */
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

/**
 * This function just resets the serial and calls the method
 * for serializing from the root node.
 */
void Source::serializeTree()
{
  serial = "";
  rootSymbol->serializeNode(&serial);
}

/**
 * This method analyzes the character being read
 * (in this case, the first one from the serial)
 * and calls the same method from the childs in
 * case the characters is a 0 and returns an unique
 * symbol if it is a 1.
 *
 * Note that this is a particular case for the root
 * node.
 *
 * In the end we call the serializeTree() method so
 * we can build the serial from the tree.
 *
 * @param input The descriptor of the file that
 * we are reading from.
 */
void Source::unserializeTree(FILE *input)
{
  char cur_c = fgetc(input);
	symbolList.clear();

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

/**
 * This method can be used after solving the Huffman
 * algorithm and obtaining the codification for the
 * original symbols.
 *
 * It will use the name of the input file passed as
 * the first argument to determine the name of the
 * output file.
 *
 * It will create and then it will write the codifications
 * for the symbols it reads from the input in the output
 * file.
 *
 * @param inputFileName The name of the input file.
 */
void Source::writeCodifiedFile(char* inputFileName)
{
  FILE *input;
  FILE *output;
  std::string outputFileName;
  char* dotPointer;
  char cur_input;
	Binarizer* binarizer = new Binarizer();

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
  fprintf(output, "%s ", (this->getSerial().c_str())); 

  cur_input = fgetc(input);

  while (cur_input != EOF)
  {
    if (Symbol::symbolIsEncodable(cur_input))
			binarizer->addStringToCode(codificationTable[cur_input].c_str());
    cur_input = fgetc(input);
  }
	fprintf(output, "%d %d\n", binarizer->getOffset(), binarizer->getCodeLength());
  
  std::string code = binarizer->getBinaryCode();
  unsigned int code_length = binarizer->getCodeLength();

  for (int i = 0; i < code_length; i++)
    fprintf(output, "%c", code[i]);

  fclose(input);
  fclose(output);
}

/**
 * This method makes the reverse operation of writing a codified
 * file.
 *
 * It will look for the codes after having built the
 * binary tree from the serial put in the first line of the header.
 * Then it will start reading the codes and printing the original
 * symbols to the output file.
 *
 * @param input The descriptor of the codified file that we are
 * reading from.
 *
 * @param outputFileName The name of the file (it is passed by\
 * the user as the second parameter of the main program.
 */
void Source::writeUncodifiedFile(FILE* input, char* outputFileName)
{
	char cur_c;
	FILE* output;
	std::string binaryString = "";
	Debinarizer* debinarizer = new Debinarizer();
	int offset;
  int n_chars;

  fscanf(input, " %d %d\n", &offset, &n_chars);
  debinarizer->setOffset(offset);

	buildSymbolList();
	buildCodeList();

	output = fopen(outputFileName, "w");
  
  if (output == NULL)
  {
    printf("Fichero de salida no pudo crearse.\n");
    exit(-1);
  }

	cur_c = fgetc(input);

  for (unsigned int i = 0; i < n_chars; i++)
	{
		debinarizer->addCharToString(cur_c);
		cur_c = fgetc(input);
	}

	while (debinarizer->codesLeft())
	{
		debinarizer->readChar();
		if (stringInCodeList(debinarizer->getTempCode()))
		{
			fprintf(output, "%c", decodificationTable[debinarizer->getTempCode()]);
			debinarizer->resetTempCode();
		}
	}

	fclose(input);
	fclose(output);
}

/**
 * This function triggers the addToListIfNotCombined
 * from the root node so we get the original symbols
 * in the symbol list.
 */
void Source::buildSymbolList()
{
	rootSymbol->addToListIfNotCombined(&symbolList);
}

/**
 * This method looks for the symbols in the symbol list
 * and makes a table that relates its codification with
 * its label. 
 */
void Source::buildCodeList()
{
	std::list <Symbol*>::iterator it;

	decodificationTable.clear();

	for (it = symbolList.begin(); it != symbolList.end(); it++)
  {
		(*it)->obtainCodification();
    decodificationTable[((*it)->getCodification())] = (*it)->getLabel();
  }
}

/**
 * This methods verifies it the decodification table contains a code.
 *
 * @param binaryString The binary code that is being searched in the table.
 */
bool Source::stringInCodeList(std::string binaryString)
{
	return (decodificationTable.find(binaryString) != decodificationTable.end());
}

/**
 * A function for showing the statistics and results from the program.
 */
void Source::showProperties()
{
  std::map<char, unsigned int>::iterator it;
  std::list <Symbol*>::iterator it2;

#ifdef MODULO1
  printf("Total number of symbols read: %d\n", totalSymbols);
  printf("The frequencies for this file are...\n");

  for (it = symbolCounter.begin(); it != symbolCounter.end();it++)
    printf("%c => %d\n", (*it).first, (*it).second); 
  
  printf("\n");
  printf("The probabilities for this file are...\n");

  for (it2 = symbolList.begin(); it2 != symbolList.end(); it2++)
    printf("%c => %f\n", (*it2)->getLabel(), (*it2)->getProbability());

  printf("\n");
#endif

#ifdef MODULO2
  printf("The codifications for the symbols are...\n");

  for (it2 = symbolList.begin(); it2 != symbolList.end(); it2++)
  {
    printf("%c => %s\n", (*it2)->getLabel(), ((*it2)->getCodification()).c_str());
  }
  printf("\n");
#endif
}
