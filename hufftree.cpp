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
	// maybe can cause problems with deletion
	symbolList = source.getSymbolList();
  rootNode = new HuffmanNode();

  rootNode->getCodification(symbolList);
}

void HuffmanNode::getCodification(std::list <Symbol> symbolList)
{
	std::list <Symbol>::iterator it;
	std::list <Symbol>::iterator minIt1 = symbolList.begin();
	float minProb = symbolList.front().getProbability();

	for (it = symbolList.begin(); it != symbolList.end(); it++)
	{
		if (minProb > (*it).getProbability())
		{
			minProb = (*it).getProbability();
			minIt1 = it;
		}
	}

	// TODO:
	// extract first min symbol
	Symbol *symbol1 = &(*minIt1);
	// delete first min symbol from list
	symbolList.erase(minIt1);

	// must try until here

	/*
	minIt1 = symbolList.begin();
	minProb = symbolList.front().getProbability();

	for (it = symbolList.begin(); it != symbolList.end(); it++)
	{
		if (minProb > (*it).getProbability())
		{
			minProb = (*it).getProbability();
			minIt1 = it;
		}
	}
	*/


}
