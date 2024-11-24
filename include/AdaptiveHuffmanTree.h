#ifndef ADAPTIVEHUFFMANTREE_H
#define ADAPTIVEHUFFMANTREE_H

#include "AdaptiveHuffmanNode.h"
#include <unordered_map>
#include <vector>
#include <queue>
#include <fstream>
class AdaptiveHuffmanTree
{
private:
    AdaptiveHuffmanNode *root;
    AdaptiveHuffmanNode *NYT;
    /**
     *
     * offset represent for the number of
     * last bits that can't cmpose a byte
     */
    unsigned short offset;
    unsigned char dictionary[257];

public:
    AdaptiveHuffmanTree();
    AdaptiveHuffmanNode *getroot() { return root; }
    unsigned short getoffset() { return offset; }
    void setoffset(unsigned short) { this->offset = offset; }
    int getnum();
    AdaptiveHuffmanNode *getleft() { return root->getleft(); }
    AdaptiveHuffmanNode *getright() { return root->getright(); }
    void get_code_exist(AdaptiveHuffmanNode *crrNode, const char buffer, char *addcode, std::queue<char> *code);
    void get_code_doesnt_exist(AdaptiveHuffmanNode *crrNode, const char buffer, char *addcode, std::queue<char> *code);
    char getdata() { return root->getdata(); }
    void encode(unsigned char buffer, std::queue<char> *code);
    void decode(std::queue<char> *code_read,unsigned short offset,std::ofstream *outfile,std::ifstream *file,bool *oke);
    void get_char_from_code(std::queue<char> *code_read, unsigned char *character);
    void update(unsigned char buffer);
    AdaptiveHuffmanNode *find_node(AdaptiveHuffmanNode *crrNode, const char buffer);
    void find_leader(AdaptiveHuffmanNode *crrNode, int weight, int *number, int parent_number, AdaptiveHuffmanNode **leader);
    void setNumber(); // give number to each node
    // destruct
    void deleteHuffmanTree(AdaptiveHuffmanNode *crrNode);
    ~AdaptiveHuffmanTree();
    bool readfile(std::ifstream *file, std::queue<char> *code_read);
    void write(std::ofstream *file, unsigned char symbol);
};

#endif