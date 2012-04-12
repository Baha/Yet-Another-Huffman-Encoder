#include "binarizer.h"

Binarizer::Binarizer()
{
	binaryCode = "";
	bits_used = 0;
	cur_byte = 0;
}

int Binarizer::getOffset()
{
	return (BYTE_LENGTH - bits_used) % BYTE_LENGTH;
}

void Binarizer::addStringToCode(const char* code)
{
	int code_length = strlen(code);
	int cur_shift = 0;
	int bits_to_process;

	while (cur_shift != code_length)
	{
		bits_to_process = min(BYTE_LENGTH - bits_used, code_length - cur_shift);
		processString(cur_shift, bits_to_process, code);
		cur_shift += bits_to_process;
	}
}

void Binarizer::processString(int cur_shift, int bits_to_process, const char* code)
{
	for (int i = 0; i < bits_to_process; i++)
	{
		processChar(code[cur_shift]);
		cur_shift++;
	}
}

void Binarizer::processChar(char bit)
{
	char mask = 0x01;

	if (bit == '1')
	{
		mask = mask << bits_used;
		cur_byte = cur_byte | mask;
	}
	bits_used++;

	if (bits_used == BYTE_LENGTH)
	{
		binaryCode.push_back(cur_byte);
		cur_byte = 0;
		bits_used = 0;
	}
}

void Binarizer::finalizeEncoding()
{
	if (bits_used != 0)
		binaryCode.push_back(cur_byte);
}

std::string Binarizer::printCode()
{
	finalizeEncoding();
	return this->binaryCode;
}

Debinarizer::Debinarizer()
{
	binaryCode = "";
	tempCode = "";
	cur_char = 0;
}

void Debinarizer::setOffset(int offset)
{
	this->offset = offset;
}
void Debinarizer::addCharToString(char character)
{
	for (int i = 0; i < BYTE_LENGTH; i++)
	{
		if (((character >> i) & 0x01) == 1)
			binaryCode.push_back('1');
		else binaryCode.push_back('0');
	}
}

void Debinarizer::resetTempCode()
{
	tempCode = "";
}

void Debinarizer::readChar()
{
	if (codesLeft())
	{
		tempCode.push_back(binaryCode[cur_char]);
		cur_char++;
	}
}

std::string Debinarizer::getTempCode()
{
	return this->tempCode;
}

bool Debinarizer::codesLeft()
{
	return (cur_char != (binaryCode.size() - offset));
}
