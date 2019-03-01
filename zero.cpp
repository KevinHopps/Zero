#include <iostream>
#include <sstream>
#include "zero.h"

#define THROW(stuff) do { std::ostringstream oss; oss << stuff; throw std::runtime_error(oss.str()); } while (false)

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
    if (fp == nullptr)
        THROW(path << ": cannot open");
    char buf[4096];
    char zero[sizeof(buf)];
    memset(zero, 0, sizeof(zero));
    off_t size = 0;
    size_t got = 0;
    while ((got = fread(buf, 1, sizeof(buf), fp)) > 0)
    {
        if (fseek(fp, size, SEEK_SET) != 0)
            THROW(path << ": fseek failure");
        if (ftell(fp) != size)
            THROW(path << ": unexpected offset after fseek");
        
        size_t sent = fwrite(zero, 1, got, fp);
        if (sent != got)
            THROW(path << ": read " << got << " but only rewrote " << sent);
        
        size += sent;
        
        if (ftell(fp) != size)
            THROW(path << ": unexpected offset after fwrite");
    }
}
