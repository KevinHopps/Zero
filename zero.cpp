#include <iostream>
#include "zero.h"

std::string shift(Args& args);
void zero(const std::string& path);

void zero(Args args)
{
    std::string cmdName = shift(args);
    bool printNames = args.size() > 1;
    for (const auto& name : args)
    {
        if (printNames)
            std::cout << name << std::flush;
        
        zero(name);
        
        if (printNames)
            std::cout << '\n';
    }
}

std::string shift(Args& args)
{
    std::string result = args.front();
    args.pop_front();
    return result;
}

void zero(const std::string& path)
{
    FILE* fp = fopen(path.c_str(), "r+");
    char buf[4096];
    char zero[sizeof(buf)];
    memset(zero, 0, sizeof(zero));
    off_t size = 0;
    size_t got = 0;
    while ((got = fread(buf, 1, sizeof(buf), fp)) > 0)
    {
        fseek(fp, size, SEEK_SET);
        fwrite(zero, 1, got, fp);
        size = ftell(fp);
    }
}
