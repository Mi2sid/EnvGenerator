#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <glm/gtc/type_ptr.hpp>

#include "utils/error.hpp"
#include "utils/readfile.hpp"
#include "render/camera.hpp"


namespace ENV_GEN {

    class Renderer {
        public:
            Renderer() {};
            ~Renderer();

            void init();
            void render();
            void animate(const double deltaT);

            void resize(const uint width, const uint height);

            void handleInputEvents(const uint key, const uint action);
	        void handleMousePosition(const double xpos, const double ypos);

        private:
            void _updateMVP();
        
        private:
            const std::string _shaderFolder     = "data/shaders/";
            const glm::vec4 _backgroundColor    = glm::vec4(0.1f, 0.1f, 0.1f, 1.f);

            std::vector<glm::vec3>  _vertexPosition;
            std::vector<glm::vec4>  _vertexColor;
            std::vector<uint>       _vertexIndex;

            GLuint _idProgram   = GL_INVALID_INDEX;
            GLuint _locMVP      = GL_INVALID_INDEX;

            GLuint _vao         = GL_INVALID_INDEX;
            GLuint _vbo_vertex  = GL_INVALID_INDEX;
            GLuint _vbo_color   = GL_INVALID_INDEX;
            GLuint _ebo         = GL_INVALID_INDEX;
            
            Camera _camera;
            const float _mouseSensibility = 0.2f; 
            float _fov; 
    };
}

#endif // __RENDERER_HPP__