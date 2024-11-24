#ifndef UNZIP_H
#define UNZIP_H

#include<string>
#include<queue>
class unzip
{
private:
    std::string src;
    std::string des;
public:
    bool unzipFile(const std::string& name);
    void read8bits(std::ifstream* file, std::queue<char>* code);
};

#endif // !UNZIP_H