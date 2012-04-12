#ifndef _BINARIZER_H_
#define _BINARIZER_H_

#include <cstdio>
#include <cstring>
#include <iostream>

#define BYTE_LENGTH 8

inline int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

class Binarizer
{
protected:
	std::string binaryCode;
	unsigned int bits_used;
	char cur_byte;
public:
	Binarizer();
	void addStringToCode(char* code);
	void processString(int cur_shift, int bits_to_process, char* code);
	void processChar(char bit);
	void finalizeEncoding();
	void printCode();
};

#endif
