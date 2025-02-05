#ifndef __READFILE_HPP__
#define __READFILE_HPP__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace UTILS {

    static inline std::string readFile(const std::string & path)
    {
        std::ifstream file(path, std::ios::in | std::ios::binary);
        if (!file)
            throw std::ios_base::failure("Cannot open file: " + path);

        std::stringstream stream;
        stream << file.rdbuf();
        return stream.str();
    }
}

#endif // __READFILE_HPP__
