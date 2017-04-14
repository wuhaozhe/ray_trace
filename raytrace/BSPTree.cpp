#include "BSPTree.h"



BSPTree::BSPTree(): root(nullptr)
{
}


BSPTree::~BSPTree()
{
}

void BSPTree::build_tree()
{
	root = new BSPTree_Node();
	root->cut = 0;
	for (int i = 0; i < objects.size(); i++)
	{
		root->object_list.push_back(i);
	}
	resursive_build(root, 0);
}

void BSPTree::resursive_build(BSPTree_Node* parent, int current_depth)
{

}