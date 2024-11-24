#include "unzip.h"
#include "AdaptiveHuffmanTree.h"
#include <fstream>
#include <iostream>
#include <queue>
bool unzip::unzipFile(const std::string &name)
{
    // read files from zipfile
    this->src = "files\\" + name;

    std::ifstream file(this->src.c_str(), std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "unable to find file1" << std::endl;
        return false;
    }

    std::cout << "unziping..." << std::endl;

    this->des = "files\\unzip_" + name.substr(0, name.find_last_of('.'));

    std::ofstream outfile(this->des.c_str(), std::ios::out | std::ios::binary);
    if (!outfile.is_open())
    {
        std::cerr << "unable to open file2" << std::endl;
        return false;
    }

    AdaptiveHuffmanTree tree;
    char buffer;
    std::queue<char> code;
    char temp=0x00;
    file.get(temp);
    unsigned short offset = temp;
    // std::cout<<"1"<<std::endl;
    bool oke = true;
    this->read8bits(&file, &code);
    do
    {
        tree.decode(&code, offset, &outfile, &file, &oke);
    } while (code.size() > offset || oke);

    //    while (file.get(buffer))
    //    {
    //        tree.decode(&code, offset, &outfile, &file);
    //       std::cout << "codesize:" << code.size() << std::endl;
    //        std::cout << "count:" << (i++) << std::endl;
    //    }

    std::cout << "success!" << std::endl;
    _sleep(3000);
    file.close();
    outfile.close();
    return true;
}

// void unzip::read8bits(std::ofstream *outfile, std::queue<char> *code){}
void unzip::read8bits(std::ifstream *file, std::queue<char> *code)
{
    char temp = 0x00;
    if ((*file).get(temp))
    {
        for (int i = 0; i < 8; i++)
        {
            if ((temp & 0x80) == 0x80)
                (*code).push('1');
            else
                (*code).push('0');
            temp <<= 1;
        }
    }
    return;
}
