#ifndef _HUFFTREE_H_
#define _HUFFTREE_H_

#include "symbol.h"

class HuffmanNode
{
    Symbol *symbols;
    float probability;
};

class HuffmanLeaf : public HuffmanNode
{
};

class HuffmanTree
{
};

#endif
