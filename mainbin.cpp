#include "binarizer.h"

int main(int argc, char* argv[])
{
	Binarizer* binarizer = new Binarizer();

	binarizer->addStringToCode("001");
	//$binarizer->addStringToCode("00100100");
	binarizer->addStringToCode("00");
	binarizer->addStringToCode("100");
	binarizer->addStringToCode("001");
	//$binarizer->addStringToCode("00100100");
	binarizer->addStringToCode("00");
	binarizer->addStringToCode("100");
	binarizer->printCode();
	
  return 0;
}
