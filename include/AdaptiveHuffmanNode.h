#ifndef ADAPTIVEHUFFMANNODE_H
#define ADAPTIVEHUFFMANNODE_H
class AdaptiveHuffmanNode
{
private:
    unsigned char data;
    int weight;
    int number;
    AdaptiveHuffmanNode *left;
    AdaptiveHuffmanNode *right;
    AdaptiveHuffmanNode *parent;

public:
    AdaptiveHuffmanNode(char data, int weight, AdaptiveHuffmanNode *left, AdaptiveHuffmanNode *right, AdaptiveHuffmanNode *parent)
    : data(data), weight(weight), left(left), right(right), parent(parent) {}
    AdaptiveHuffmanNode(){};
    char getdata(){return data;}
    int getweight(){return weight;}
    int getnumber(){return number;}
    AdaptiveHuffmanNode *getleft() { return left; }
    AdaptiveHuffmanNode *getright() { return right; }
    AdaptiveHuffmanNode *getparent() { return parent; }
    
    void setdata(char data) { this->data = data; }
    void setweight(int weight) { this->weight = weight; }
    void setleft(AdaptiveHuffmanNode *left) { this->left = left; }
    void setright(AdaptiveHuffmanNode *right) { this->right = right; }
    void setparent(AdaptiveHuffmanNode *parent) { this->parent = parent; }
    void setnumber(int number) { this->number = number; }
    void swap(AdaptiveHuffmanNode *node);
    void addweight();
};

#endif // !HuffmanNODE_H