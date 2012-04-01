#include "hufftree.h"

bool HuffmanNode::isLeaf()
{
  return false;
}

bool HuffmanLeaf::isLeaf()
{
  return true;
}

void HuffmanTree::buildHuffmanTree(Source source)
{
  symbolList(source.getSymbolList);
  rootNode = new HuffmanNode();

  rootNode->getCodification(symbolList);
}

/*{
  float minProb = 100.0f;
  std::list <Symbol>::iterator it;
  std::list <Symbol>::iterator minIt;

  for (it = symbolList.begin(); it != symbolList.end(); it++)
  {
    if (minProb > (*it).getProbability())
      minProb = (*it).getProbability();
    minIt = (*it);
  }
  return minSymbol;
}*/

void HuffmanNode::getCodification(std::list <Symbol> symbolList)
{
}
