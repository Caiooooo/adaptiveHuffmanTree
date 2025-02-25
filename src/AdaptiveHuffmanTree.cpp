#include "AdaptiveHuffmanTree.h"
#include "AdaptiveHuffmanNode.h"
#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <cstring>
#include <utility>
#include <algorithm>
AdaptiveHuffmanTree::AdaptiveHuffmanTree()
{
    root = new AdaptiveHuffmanNode(0x00, 0, nullptr, nullptr, nullptr); // NYT
    NYT = root;
    offset = 0;
    memset(dictionary, 0, sizeof(dictionary));
}
void AdaptiveHuffmanTree::encode(unsigned char buffer, std::queue<char> *code)
{
    char init[1] = {'\0'};

    // std::cout<<(int)buffer<<' ';
    if (dictionary[(int)buffer] == 0x01)
        this->get_code_exist(root, buffer, init, code);
    else
        this->get_code_doesnt_exist(root, buffer, init, code);

    // update
    this->update(buffer);
    // std::cout<<"upsucess"<<' ';
    // write to file
}

void AdaptiveHuffmanTree::get_char_from_code(std::queue<char> *code_read, unsigned char *character)
{
    unsigned char temp;
    temp &= 0x00;
    for (int i = 0; i < 8; i++)
    {
        if ((*code_read).front() == '1')
        {
            temp ^= 0x01;
        }
        if (i != 7)
        {
            temp <<= 1;
        }
        (*code_read).pop();
    }
    character[0] = temp;
    return;
}

bool AdaptiveHuffmanTree::readfile(std::ifstream *file, std::queue<char> *code_read)
{
    char temp;
    temp &= 0x00;
    if ((*file).get(temp))
    {
        for (int i = 0; i < 8; i++)
        {
            if ((temp & 0x80) == 0x80)
            {
                (*code_read).push('1');
            }
            else
            {
                (*code_read).push('0');
            }
            temp <<= 1;
        }
        return true;
    }
    else
    {
        return false;
    }
}

void AdaptiveHuffmanTree::write(std::ofstream *file, unsigned char symbol)
{
    *file << symbol;
    return;
}

void AdaptiveHuffmanTree::decode(std::queue<char> *code_read, unsigned short offset, std::ofstream *outfile, std::ifstream *file, bool *oke)
{
    AdaptiveHuffmanNode *temp = root;
    while ((*code_read).size() < 32 && *oke)
    {
        *oke = readfile(&*file, &*code_read);
    }
    if (temp == nullptr)
    {
        unsigned char symbol[1];
        get_char_from_code(&*code_read, symbol);
        write(&*outfile, symbol[0]);
        // call update procedure
        update(symbol[0]);
    }
    else
    {
        while (temp->getleft() != nullptr && temp->getright() != nullptr && (*code_read).size() > offset)
        {
            if ((*code_read).front() == '0')
            {
                temp = temp->getleft();
                (*code_read).pop();
            }
            else
            {
                temp = temp->getright();
                (*code_read).pop();
            }
            while ((*code_read).size() < 32 && *oke)
            {
                *oke = readfile(&*file, &*code_read);
            }
        }
        if ((*code_read).size() == offset && temp->getleft() != NULL && temp->getright() != NULL)
        {
            return;
        }
        if (temp->getweight() == 0)
        {
            unsigned char symbol[1];
            get_char_from_code(&*code_read, symbol);
            write(&*outfile, symbol[0]);
            update(symbol[0]);
        }
        else
        {
            write(&*outfile, temp->getdata());
            update(static_cast<unsigned char>(temp->getdata()));
        }
    }
    return;
}

void AdaptiveHuffmanTree::get_code_exist(AdaptiveHuffmanNode *crrNode, const char buffer, char *addcode, std::queue<char> *code)
{
    // found
    if (crrNode->getdata() == buffer && crrNode->getleft() == NULL && crrNode->getright() == NULL && crrNode->getweight() != 0)
    {
        for (int i = 0; i < strlen(addcode); i++)
        {
            code->push(addcode[i]);
        }
        return;
    }
    char temp[strlen(addcode) + 1];
    strcpy(temp, addcode);
    if (crrNode->getleft() != nullptr)
        get_code_exist(crrNode->getleft(), buffer, strcat(temp, "0"), code);
    strcpy(temp, addcode);
    if (crrNode->getright() != nullptr)
        get_code_exist(crrNode->getright(), buffer, strcat(temp, "1"), code);
    return;
}
/**
 * this function is used to get the code of the symbol that doesn't exist in the tree
 * e.g NTY is 010 and we need to insert a
 * then add 0100123(ascii of a)
 */
void AdaptiveHuffmanTree::get_code_doesnt_exist(AdaptiveHuffmanNode *crrNode, char buffer, char *addcode, std::queue<char> *code)
{
    // found

    if (crrNode->getweight() == 0 && crrNode->getleft() == NULL && crrNode->getright() == NULL)
    {
        for (int i = 0; i < strlen(addcode); i++)
            code->push(addcode[i]);
        for (int i = 0; i < 8; i++)
        {
            if ((buffer & 0x80) == 0x80)
                code->push('1');
            else
                code->push('0');
            buffer <<= 1;
        }
        return;
    }
    char temp[strlen(addcode) + 1];
    strcpy(temp, addcode);
    if (crrNode->getleft() != nullptr)
        get_code_doesnt_exist(crrNode->getleft(), buffer, strcat(temp, "0"), code);
    strcpy(temp, addcode);
    if (crrNode->getright() != nullptr)
        get_code_doesnt_exist(crrNode->getright(), buffer, strcat(temp, "1"), code);
}
void AdaptiveHuffmanTree::update(unsigned char buffer)
{

    AdaptiveHuffmanNode *now = nullptr;
    if (dictionary[(int)buffer])
    {
        /*
        Swap p with leader of its block
        if (n ew  p is sibling to NYT) then
            leaf_to_increment = p
            p = parent of p
        */
        // node:pointer to the leaf nmode contaning the buffer
        // std::cout << buffer << std::endl;
        AdaptiveHuffmanNode *node = this->find_node(this->root, buffer); // find p
        // std::cout<<node->getdata()<<std::endl;
        now = node;
        AdaptiveHuffmanNode *leader = NULL;
        int numtemp = node->getnumber();
        this->find_leader(root, node->getweight(), &numtemp, node->getparent()->getnumber(), &leader); // find leader

        // swap p with leader of its block
        // std::cout << "shenmegui" << leader->getdata() << std::endl;
        if (leader != nullptr)
            // std::cout << "zhaodaole:" << leader->getparent()->getnumber();
            node->swap(leader);
        // for leaves: move first then update
        node->addweight();
    }
    else // add n ew node
    {
        /*
         if (p is NYT) then
        Extend p by adding two children
        Left child becomes n ew NYT and right child is the n ew symbol leaf node
        p := parent of n ew symbol leaf node
        leaf_to_increment := Right Child of p
        */
        // update the tree
        AdaptiveHuffmanNode *newNYT = new AdaptiveHuffmanNode(0x00, 0, nullptr, nullptr, nullptr);   // NYT
        AdaptiveHuffmanNode *origin = new AdaptiveHuffmanNode(buffer, 1, nullptr, nullptr, nullptr); // ori
        AdaptiveHuffmanNode *newNode = new AdaptiveHuffmanNode(0x00, 1, newNYT, origin, nullptr);    // new
        now = newNode;
        newNYT->setparent(newNode);
        origin->setparent(newNode);
        if (this->NYT == this->root)
        {
            AdaptiveHuffmanNode *temp = this->root;
            delete root;
            this->root = newNode;
            this->NYT = newNYT;
            // delete temp;

            // std::cout << "update" << std::endl;
        }
        else
        {
            // std::cout << "update" << std::endl;
            newNode->setparent(this->NYT->getparent());
            this->NYT->getparent()->setleft(newNode);
            //  this->NYT = nullptr;
            // printTree();
            delete this->NYT;
            // printTree();
            this->NYT = newNYT;
            // delete todel;
            //  bfs the whole tree to update the number
            //  update the dictionary
        }
        this->setNumber();
        dictionary[(int)buffer] = 0x01;
        // update the symbol
    }
    // this->printTree();
    /*
    while (p ≠ NULL) do
        Slide_And_Increment(p)

    if (leaf_to_increment != NULL) then
        Slide_And_Increment(leaf_to_increment)
    */
    // std::cout<<"update"<<std::endl;

    while (now->getparent() != nullptr)
    {
        // this->printTree();
        now = now->getparent();
        // if not root
        if (now != root)
        {
            AdaptiveHuffmanNode *leader = nullptr;
            int numtemp = now->getnumber();
            this->find_leader(root, now->getweight(), &numtemp, now->getparent()->getnumber(), &leader); // find leader
            // swap p with leader of its block
            if (leader != nullptr)
            {
                // std::cout << "zhaodaole" << leader->getparent()->getnumber() << std::endl;
                now->swap(leader);
            }
        }
        now->addweight();
        this->setNumber();
    }
    // this->printTree();
}
AdaptiveHuffmanNode *AdaptiveHuffmanTree::find_node(AdaptiveHuffmanNode *crrNode, const char buffer)
{
    if (crrNode == nullptr)
        return nullptr;
    if (crrNode->getdata() == buffer && crrNode->getleft() == nullptr && crrNode->getright() == nullptr && crrNode->getweight() != 0)
        return crrNode;
    AdaptiveHuffmanNode *temp;
    if ((temp = find_node(crrNode->getleft(), buffer)) != nullptr)
        return temp;
    if ((temp = find_node(crrNode->getright(), buffer)) != nullptr)
        return temp;
    return nullptr; // never used
}
void AdaptiveHuffmanTree::find_leader(AdaptiveHuffmanNode *crrNode, int weight, int *number, int parent_number, AdaptiveHuffmanNode **leader)
{
    if (crrNode->getweight() == weight && crrNode->getnumber() > (*number) && crrNode->getparent()->getnumber() != parent_number)
    {
        *leader = crrNode;
        *number = crrNode->getnumber();
        // std::cout<<leader->getnumber();
    }
    if (crrNode->getleft() != nullptr)
        find_leader(crrNode->getleft(), weight, &*number, parent_number, &*leader);
    if (crrNode->getright() != nullptr)
        find_leader(crrNode->getright(), weight, &*number, parent_number, &*leader);
    return;
}
bool my_sort(std::pair<int, AdaptiveHuffmanNode *> p, std::pair<int, AdaptiveHuffmanNode *> q)
{
    return p.first < q.first;
}
void dfs_node(AdaptiveHuffmanNode *now, std::vector<std::pair<int, AdaptiveHuffmanNode *>> *queue, int deep)
{
    (*queue).push_back(std::make_pair(deep, now));
    if (now->getright() != NULL)
        dfs_node(now->getright(), &*queue, deep + 1);
    if (now->getleft() != NULL)
        dfs_node(now->getleft(), &*queue, deep + 1);
    return;
}
void AdaptiveHuffmanTree::setNumber()
{
    // dfs to set number
    std::vector<std::pair<int, AdaptiveHuffmanNode *>> my_pair;
    dfs_node(root, &my_pair, 0);
    std::sort(my_pair.begin(), my_pair.end(), my_sort);

    int num = 512;
    for (int i = 0; i < my_pair.size(); i++)
        my_pair.at(i).second->setnumber(--num);
}
// destroy
void AdaptiveHuffmanTree::deleteHuffmanTree(AdaptiveHuffmanNode *crrNode)
{
    if (crrNode == nullptr)
        return;
    deleteHuffmanTree(crrNode->getleft());
    deleteHuffmanTree(crrNode->getright());
    delete crrNode;
}
AdaptiveHuffmanTree::~AdaptiveHuffmanTree()
{
    deleteHuffmanTree(root);
}
