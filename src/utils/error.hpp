#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#include <stdexcept>
#include <string>
#include <map>

namespace ENV_GEN {

    struct ErrorInfo {
        const char* code; 
        const char* description;
    };

    constexpr uint WINDOW_ERROR = 0;
    constexpr uint GLFW_ERROR = 1;

    inline const std::map<uint, ErrorInfo> ERROR_MAP = {
        { WINDOW_ERROR,  {"0001", "Windows initialization failed."} },
        { GLFW_ERROR,    {"0002", "GLFW initialization failed."} },
    };

    inline void error(int code) {

        auto it = ERROR_MAP.find(code);
        if (it == ERROR_MAP.end()) {
            throw std::runtime_error("Unknown error code: " + std::to_string(code));
        }

        const ErrorInfo& errorInfo = it->second;
        throw std::runtime_error(std::string("Error ") + errorInfo.code + ":\n\t" + errorInfo.description);
    
    }
}

#endif // __ERROR_HPP__
