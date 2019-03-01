#include <cstdint>
#include <fstream>
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
    auto flags = std::ios::in | std::ios::out | std::ios::binary;
    std::fstream file(path, flags);
    if (!file)
        THROW(path << ": cannot open");
    std::vector<char> buf(4096);
    std::vector<char> zero(buf.size());
    std::memset(zero.data(), 0, zero.size());
    std::ios::pos_type offs = 0;
    auto read = [](std::fstream& file, char* buf, size_t want)
    {
        size_t got = want;
        if (!file.read(buf, want))
        {
            got = file.gcount();
            file.clear();
        }
        return got;
    };
    size_t got = 0;
    while ((got = read(file, buf.data(), buf.size())) > 0)
    {
        if (!file.seekg(offs))
            THROW(path << ": seek failure");
        if (!file.write(zero.data(), got))
            THROW(path << ": write failure");
        file.flush();
        offs += got;
    }
}
