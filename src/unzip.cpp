#include "unzip.h"
#include "AdaptiveHuffmanTree.h"
#include <fstream>
#include <iostream>
bool unzip::unzipFile(const std::string &name)
{
    // read files from zipfile
    this->src = "files\\" + name;
    std::ifstream file(this->src.c_str(), std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "unable to find file" << std::endl;
        std::cout << "failed";
        return false;
    }
    std::cout << "unziping...";
    this->des = "files\\r:"  + this->src.substr(0, this->src.find_last_of('.'));
    // whats_this.jpg.zip -> r:whats_this.jpg

    // TODO : read the haffuman tree

    // TODO : decode the file

    // TODO : write the file

    return 1;
}
