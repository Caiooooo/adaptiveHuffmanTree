#ifndef UNZIP_H
#define UNZIP_H

#include<string>
class unzip
{
private:
    std::string src;
    std::string des;
public:
    bool unzipFile(const std::string& name);
};

#endif // !UNZIP_H