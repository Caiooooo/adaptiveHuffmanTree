#ifndef ZIP_H
#define ZIP_H

#include<iostream>
#include<string>
#include<queue>
class zip
{
private:
    std::string des ;
    std::string src ;
public:
    bool zipFile(const std::string& name);
    void write8bits(std::ofstream* outfile, std::queue<char>* code);
    void handleLastBits(std::ofstream* outfile, std::queue<char>& code);
};

#endif // !ZIP_H