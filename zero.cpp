#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>
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
    std::vector<std::uint8_t> buf(4096);
    std::vector<std::uint8_t> zero(buf.size());
    memset(zero.data(), 0, zero.size());
    off_t size = 0;
    size_t got = 0;
    while ((got = fread(buf.data(), 1, buf.size(), fp)) > 0)
    {
        if (fseek(fp, size, SEEK_SET) != 0)
            THROW(path << ": fseek failure");
        if (ftell(fp) != size)
            THROW(path << ": unexpected offset after fseek");
        
        size_t sent = fwrite(zero.data(), 1, got, fp);
        if (sent != got)
            THROW(path << ": read " << got << " but only rewrote " << sent);
        
        size += sent;
        
        if (ftell(fp) != size)
            THROW(path << ": unexpected offset after fwrite");
    }
}
