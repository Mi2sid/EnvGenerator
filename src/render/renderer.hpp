#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

#include "utils/error.hpp"
#include "utils/readfile.hpp"

namespace ENV_GEN {

    class Renderer {
        public:
            Renderer() {};
            ~Renderer();

            void init();
            void render();

        
        private:
            const std::string _shaderFolder     = "data/shaders/";
            const glm::vec4 _backgroundColor    = glm::vec4(0.1f, 0.1f, 0.1f, 1.f);

            std::vector<glm::vec3>  _vertexPosition;
            std::vector<glm::vec4>  _vertexColor;
            std::vector<uint>       _vertexIndex;


            GLuint _idProgram   = GL_INVALID_INDEX;
            GLuint _vao         = GL_INVALID_INDEX;
            GLuint _vbo_vertex  = GL_INVALID_INDEX;
            GLuint _vbo_color   = GL_INVALID_INDEX;
            GLuint _ebo         = GL_INVALID_INDEX;

    };
}

#endif // __RENDERER_HPP__