#include "AdaptiveHuffmanNode.h"
#include "AdaptiveHuffmanTree.h"

void AdaptiveHuffmanNode::swap(AdaptiveHuffmanNode *node)
{
    bool crrisLeft = (this->parent->getleft()->getnumber() == this->getnumber());
    bool nodeisLeft = (node->parent->getleft()->getnumber() == node->getnumber());
    AdaptiveHuffmanNode *crrparent = this->getparent();
    AdaptiveHuffmanNode *nodeparent = node->getparent();
    if (crrisLeft && nodeisLeft)
    {
        crrparent->setleft(node);
        nodeparent->setleft(this);
    }
    else if (crrisLeft)
    {
        crrparent->setleft(node);
        nodeparent->setright(this);
    }
    else if (nodeisLeft)
    {
        crrparent->setright(node);
        nodeparent->setleft(this);
    }
    else
    {
        crrparent->setright(node);
        nodeparent->setright(this);
    }
    nodeparent->left->parent = nodeparent;
    nodeparent->right->parent = nodeparent;
    crrparent->left->parent = crrparent;
    crrparent->right->parent = crrparent;
    return;
}
void AdaptiveHuffmanNode::addweight()
{
    if (this->left == nullptr && this->right == nullptr)
        this->weight++;
    else
        this->weight = this->left->getweight() + this->right->getweight();
}