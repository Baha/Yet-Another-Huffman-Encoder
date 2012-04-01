#include "source.h"

void Source::getFrequencies(FILE *input)
{
  FILE *in = input;
  char cur_c;
  std::map<char, unsigned int>::iterator it;

  symbolCounter.clear();
  
  cur_c = fgetc(in);

  while (cur_c != EOF)
  {
    if (symbolIsEncodable(cur_c))
    {
      it = symbolCounter.find(cur_c);
    }
  }
}

void Source::getProbabilities()
{

}

void Source::getProperties(FILE *input)
{
  this->getFrequencies(input);
  this->getProbabilities();
}

void Source::showProperties()
{
  
}
