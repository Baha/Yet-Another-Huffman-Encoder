#include "binarizer.h"

Binarizer::Binarizer()
{
	binaryCode = "";
}

void Binarizer::addStringToCode(char* code)
{
	int code_length = strlen(code);
	int cur_shift = 0;
	int bits_to_process;

	while (cur_shift != code_length)
	{
		bits_to_process = min(BYTE_LENGTH - bits_used, code_length - cur_shift);
		processString(cur_shift, bits_to_process, code);
		cur_shift += bits_to_process;
		printf("cs: %d btp: %d cl: %d\n", cur_shift, bits_to_process, code_length);
	}
}

void Binarizer::processString(int cur_shift, int bits_to_process, char* code)
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
	printf("bit: %c mask: %c\n", bit, cur_byte);
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

void Binarizer::printCode()
{
	finalizeEncoding();
	fprintf(stdout, "%s\n", binaryCode.c_str());
}
