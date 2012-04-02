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
	symbolList(source.getSymbolList());
  rootNode = new HuffmanNode();

  rootNode->getCodification(symbolList);
}

void HuffmanNode::getCodification(std::list <Symbol> symbolList)
{
	std::list <Symbol>::iterator it1 = symbolList.begin();
	float minProb = 100.0f;

}
