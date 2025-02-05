#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#include <stdexcept>
#include <string>
#include <map>
#include <iostream>

namespace UTILS {

    struct ErrorInfo {
        const char* code; 
        const char* description;
    };

    constexpr unsigned int WINDOW_ERROR = 0;
    constexpr unsigned int GLFW_ERROR = 1;
    constexpr unsigned int GLEW_ERROR = 2;
    constexpr unsigned int COMPILE_SHADER_ERROR = 3;
    constexpr unsigned int LINK_PROGRAM_ERROR = 4;

    inline const std::map<unsigned int, ErrorInfo> ERROR_MAP = {
        { WINDOW_ERROR,         {"0001", "Windows initialization failed."} },
        { GLFW_ERROR,           {"0002", "GLFW initialization failed."} },
        { GLEW_ERROR,           {"0003", "GLEW initialization failed."} },
        { COMPILE_SHADER_ERROR, {"0004", "Compiling shader failed."} },
        { LINK_PROGRAM_ERROR,   {"0005", "Linking program failed."} },
    };

    inline void error(int code, const std::string& log = "") {

        auto it = ERROR_MAP.find(code);
        if (it == ERROR_MAP.end()) {
            throw std::runtime_error("Unknown error code: " + std::to_string(code));
        }

        const ErrorInfo& errorInfo = it->second;

        std::string errorMessage = "Error " + std::string(errorInfo.code) + ":\n\t" + errorInfo.description;

        if (!log.empty()) errorMessage += "\n\tAdditional info: " + log;
        
        throw std::runtime_error(errorMessage);
    }

}

#endif // __ERROR_HPP__
