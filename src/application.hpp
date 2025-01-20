#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "utils/error.hpp"
#include "render/renderer.hpp"

namespace ENV_GEN {
    class Application {

        public: 
            Application( const std::string & title, const uint width, const uint height);
            ~Application();
            
            uint run();

        private:
            void _initGLFW();
            void _initWindows();
            void _initGLEW();

        private:

            const std::string _title;

            const uint _width;
            const uint _height;

            GLFWwindow* _window;

            Renderer _renderer;
    };
}

#endif // __APPLICATION_HPP__