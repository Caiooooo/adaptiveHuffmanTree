#include "zip.h"
#include "AdaptiveHuffmanTree.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <Windows.h>
bool zip::zipFile(const std::string &name)
{
    // init zipname and open file
    // this->des = "files\\" + this->src.substr(0, this->src.find_last_of('.'));
    this->src = "files\\" + name;
    std::ifstream file(this->src.c_str(), std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "unable to find file" << std::endl;
        return false;
    }
    std::cout << "ziping..." << std::endl;
    this->des = this->src + ".ah";
    // test -> test.zip
    // write file
    std::ofstream outfile(this->des.c_str(), std::ios::out | std::ios::binary);
    if (!outfile.is_open())
    {
        std::cerr << "unable to open file" << std::endl;
        return false;
    }

    // Adaptive HuffmanTree
    AdaptiveHuffmanTree tree;
    char buffer;
    std::queue<char> code;
    outfile << (unsigned char)0x00; // offset use to handle last bits
    // std::cout << this->des << std::endl;
    while (file.get(buffer))
    {
        // build and update tree
        // std::cout << buffer << std::endl;
        tree.encode(buffer, &code);
        // std::cout << 2 << std::endl;
        while (code.size() >= 8)
            this->write8bits(&outfile, &code);
        // std::cout << 3 << std::endl;
    }
    // Handle last bits in write file
    // Sleep(10000);
    this->handleLastBits(&outfile, code);

    return true;
}

void zip::write8bits(std::ofstream *outfile, std::queue<char> *code)
{
    unsigned char buffer = 0x00;
    for (int i = 0; i < 8; i++)
    {
        // std::cout << code->front();
        if (code->front() == '1')
            buffer ^= 0x01;
        if (i != 7)
            buffer <<= 1;

        code->pop();
    }
    // for (int i = 0; i < 8; i++)
    // {
    //     buffer = buffer << 1;
    //     if (code->front() == '1')
    //         buffer = buffer | 0x01;
    //     // 0000 0001
    //     std::cout << code->front();
    //     code->pop();
    // }
    // std::cout << buffer;
    (*outfile) << buffer;
    return;
}
void zip::handleLastBits(std::ofstream *outfile, std::queue<char> &code)
{
    if (code.size() == 0)
        return;
    unsigned short offset = 8 - code.size();
    while (code.size() < 8)
        code.push('0');
    this->write8bits(outfile, &code);
    outfile->seekp(0);
    char offset_char = (char)offset;
    (*outfile) << offset_char;
    return;
}