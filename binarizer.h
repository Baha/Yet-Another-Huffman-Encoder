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
	int getOffset();
	void addStringToCode(const char* code);
	void processString(int cur_shift, int bits_to_process, const char* code);
	void processChar(char bit);
	void finalizeEncoding();
	std::string printCode();
};

class Debinarizer
{
protected:
	std::string binaryCode;
	std::string tempCode;
	int cur_char;
	int offset;
public:
	Debinarizer();
	void setOffset(int offset);
	void addCharToString(char character);
	void resetTempCode();
	void readChar();
	std::string getTempCode();
	bool codesLeft();
};

#endif
