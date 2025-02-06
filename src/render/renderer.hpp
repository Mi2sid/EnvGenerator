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
#include "terrain/chunk.hpp"
#include "entity/player.hpp"

namespace RENDER {

    struct GLCube {
        static const std::vector<glm::vec3>  vertexPosition;
        static const std::vector<uint>       vertexIndex;
        
        std::vector<glm::vec4>  vertexColor;

        glm::mat4 model = {
            1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
        };

        GLuint vao         = GL_INVALID_INDEX;
        GLuint vbo_vertex  = GL_INVALID_INDEX;
        GLuint vbo_color   = GL_INVALID_INDEX;
        GLuint ebo         = GL_INVALID_INDEX;
    };

    class Renderer {
        public:
            Renderer() {};
            ~Renderer();

            void init();
            void render(ENV_GEN::Chunk* chunk, ENTITY::Player* player);
            void animate(const double deltaT, ENTITY::Player* player);

            void resize(const uint width, const uint height);

            void handleInputEvents(const uint key, const uint action);
	        void handleMousePosition(const double xpos, const double ypos);
        
        private:
            const std::string _shaderFolder     = "data/shaders/";
            const glm::vec4 _backgroundColor    = glm::vec4(0.1f, 0.1f, 0.1f, 1.f);

            GLuint _idProgram       = GL_INVALID_INDEX;
            GLuint _locMVP          = GL_INVALID_INDEX;
            GLuint _locAtlas        = GL_INVALID_INDEX;
            GLuint _locAtlasIndex   = GL_INVALID_INDEX;

            GLCube _cubeSample;

            Camera _camera;
            const float _mouseSensibility = 0.1f; 
            float _fov; 
    };
}

#endif // __RENDERER_HPP__