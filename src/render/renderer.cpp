#include "renderer.hpp"

namespace ENV_GEN {

    Renderer::~Renderer() {

		glDeleteBuffers( 1, &_vbo );

		glDisableVertexArrayAttrib( _vao, 0 );
		glDeleteVertexArrays( 1, &_vao );

        glDeleteProgram(_idProgram);
    }

    void Renderer::init() {
        std::cout << "Initializing Renderer." << std::endl;

		glClearColor( _backgroundColor.x, _backgroundColor.y, _backgroundColor.z, _backgroundColor.w );
    
        const std::string vertShaderSource = readFile(_shaderFolder + "initialVert.glsl");
        const std::string fragShaderSource = readFile(_shaderFolder + "initialFrag.glsl");

        GLuint vertexShader     = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShader   = glCreateShader(GL_FRAGMENT_SHADER);

        const char* charVertSource = vertShaderSource.c_str();
        const char* charFragSource = fragShaderSource.c_str();

        glShaderSource(vertexShader,    1, &charVertSource, nullptr);
        glShaderSource(fragmentShader,  1, &charFragSource, nullptr);
        
        glCompileShader(vertexShader);
        glCompileShader(fragmentShader);

        GLint verified;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &verified);
		if (!verified)
		{
			GLchar log[1024];
			glGetShaderInfoLog(vertexShader, sizeof( log ), NULL, log);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
            error(COMPILE_SHADER_ERROR, log);
		}

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &verified);
		if (!verified)
		{
			GLchar log[1024];
			glGetShaderInfoLog(fragmentShader,sizeof(log), NULL, log);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			error(COMPILE_SHADER_ERROR, log);
		}

        _idProgram = glCreateProgram();

		glAttachShader(_idProgram, vertexShader);
		glAttachShader(_idProgram, fragmentShader);

		glLinkProgram(_idProgram);

		glGetProgramiv(_idProgram, GL_LINK_STATUS, &verified);
		if (!verified)
		{
			GLchar log[1024];
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			glGetProgramInfoLog(_idProgram, sizeof(log), NULL, log);
			error(LINK_PROGRAM_ERROR, log);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

        _vertexPosition = { { -0.5f, 0.5f }, { 0.5f, 0.5f }, { 0.f, -0.5f } };

		// vbo
		glCreateBuffers( 1, &_vbo );
		glNamedBufferData( _vbo, _vertexPosition.size() * sizeof( glm::vec2 ), _vertexPosition.data(), GL_STATIC_DRAW );

		// vao
		glCreateVertexArrays( 1, &_vao);
		glEnableVertexArrayAttrib( _vao, 0 );
		glVertexArrayAttribFormat( _vao, 0, 2, GL_FLOAT, GL_FALSE, 0 );

		// vao, vbo link
		glVertexArrayVertexBuffer( _vao, 0, _vbo, 0, sizeof( glm::vec2 ) );
		glVertexArrayAttribBinding( _vao, 0, 0 );

		glUseProgram( _idProgram );

		std::cout << "Renderer initilised!" << std::endl;

    }

    void Renderer::render() {
        glClear( GL_COLOR_BUFFER_BIT );
		glBindVertexArray( _vao );
		glDrawArrays( GL_TRIANGLES, 0, _vertexPosition.size() );
		glBindVertexArray( 0 );
    }
}