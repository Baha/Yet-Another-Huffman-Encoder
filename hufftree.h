#ifndef _HUFFTREE_H_
#define _HUFFTREE_H_

#include "symbol.h"

class HuffmanNode
{
  Symbol *symbol;
  HuffmanNode *leftNode, *rightNode;
  float probability;
public:
  void getCodification(std::list <Symbol> symbolList)
  virtual bool isLeaf();
};

class HuffmanLeaf : public HuffmanNode
{
public:
  bool isLeaf();
};

class HuffmanTree
{
  HuffmanNode *rootNode;
  std::list <Symbol> symbolList;
  void buildHuffmanTree(Source source);
};

#endif
