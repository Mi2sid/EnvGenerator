#include "renderer.hpp"

namespace ENV_GEN {

    Renderer::~Renderer() {

		glDeleteProgram(_idProgram);

		glDeleteBuffers( 1, &_vbo_vertex );
		glDeleteBuffers( 1, &_vbo_color );

		glDisableVertexArrayAttrib( _vao, 0 );
		glDisableVertexArrayAttrib( _vao, 1 );

		glDeleteVertexArrays( 1, &_vao );

		glDeleteBuffers(1, &_ebo);
		glDisable( GL_DEPTH_TEST );
    }

    void Renderer::init() {
        std::cout << "Initializing Renderer." << std::endl;

		glClearColor( _backgroundColor.x, _backgroundColor.y, _backgroundColor.z, _backgroundColor.w );
    
		glEnable(GL_DEPTH_TEST);

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

		_vertexPosition = { { 0.5f, 0.5f, 0.5f }, { 0.5f, -0.5f, 0.5f },
							{ -0.5f, 0.5f, 0.5f }, { -0.5f, -0.5f, 0.5f }, 
							{ 0.5f, 0.5f, -0.5f }, { 0.5f, -0.5f, -0.5f },
							{ -0.5f, 0.5f, -0.5f }, { -0.5f, -0.5f, -0.5f } };

		for ( int i = 0; i < _vertexPosition.size() ; i++ )
			_vertexColor.push_back( glm::vec4( static_cast<float>(std::rand()) / RAND_MAX, static_cast<float>(std::rand()) / RAND_MAX, static_cast<float>(std::rand()) / RAND_MAX, 1.f ) );

		_vertexIndex = {
			3, 0, 1, 3, 0, 2, // z+
			7, 4, 5, 7, 4, 6, // z-
			1, 7, 3, 1, 7, 5, // y-
			0, 6, 2, 0, 6, 4, // y+
			0, 5, 1, 0, 5, 4, // x+
			2, 7, 3, 2, 7, 6, // x-
		};

		_locMVP = glGetUniformLocation( _idProgram, "uMVPMatrix" );

		// camera
		_fov = _camera.getFov();
		_camera.setPosition( glm::vec3( 1.f, 1.f, 4.f ) );
		_camera.setScreenSize( 1280, 720 );
		_updateMVP();

		glUseProgram( _idProgram );

		// vao
		glCreateVertexArrays( 1, &_vao);
		glEnableVertexArrayAttrib( _vao, 0 );
		glEnableVertexArrayAttrib( _vao, 1 );

		// vbo
		glCreateBuffers( 1, &_vbo_vertex );
		glNamedBufferData( _vbo_vertex, _vertexPosition.size() * sizeof( glm::vec3 ), _vertexPosition.data(), GL_STATIC_DRAW );

		// vao, vbo link
		glVertexArrayVertexBuffer( _vao, 0, _vbo_vertex, 0, sizeof( glm::vec3 ) );
		glVertexArrayAttribFormat( _vao, 0, 3, GL_FLOAT, GL_FALSE, 0 );
		glVertexArrayAttribBinding( _vao, 0, 0 );

		// vbo color
		glCreateBuffers( 1, &_vbo_color );
		glNamedBufferData( _vbo_color, _vertexColor.size() * sizeof( glm::vec4 ), _vertexColor.data(), GL_STATIC_DRAW );

		// vao, vbo color link
		glVertexArrayVertexBuffer( _vao, 1, _vbo_color, 0, sizeof( glm::vec4 ) );
		glVertexArrayAttribFormat( _vao, 1, 4, GL_FLOAT, GL_FALSE, 0 );
		glVertexArrayAttribBinding( _vao, 1, 1 );

		// ebo
		glCreateBuffers( 1, &_ebo );
		glNamedBufferData( _ebo, _vertexIndex.size() * sizeof( uint ), _vertexIndex.data(), GL_STATIC_DRAW );

		// link vao ebo
		glVertexArrayElementBuffer( _vao, _ebo );

		std::cout << "Renderer initilised!" << std::endl;

    }

    void Renderer::render() {
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		glBindVertexArray( _vao );

		glDrawElements( GL_TRIANGLES, (GLsizei) _vertexIndex.size(), GL_UNSIGNED_INT, 0 );
		
		_updateMVP();
		
		glBindVertexArray( 0 );
    }

	void Renderer::animate(const double deltaT){

	}

	void Renderer::handleInputEvents(const uint key, const uint action){
		if(action == GLFW_RELEASE)
			return;
		switch (key)
		{
		case GLFW_KEY_W:
			_camera.moveFront(0.1f);
			break;
		case GLFW_KEY_S:
			_camera.moveFront(-0.1f);	
			break;
		case GLFW_KEY_A:
			_camera.moveRight(-0.1f);
			break;
		case GLFW_KEY_D:
			_camera.moveRight(0.1f);
			break;
		case GLFW_KEY_Q:
			_camera.moveUp(-0.1f);
			break;
		case GLFW_KEY_E:
			_camera.moveUp(0.1f);
			break;
		default:
			break;
		}
	}

	void Renderer::handleMousePosition(const double xpos, const double ypos) {
		_camera.rotate(xpos * _mouseSensibility, ypos * _mouseSensibility);
	}
	
	void Renderer::resize( const uint width, const uint height ) {
		glViewport( 0, 0, width, height );
	}

	void Renderer::_updateMVP() {

		glm::mat4 MVP = _camera.getProjectionMatrix() * _camera.getViewMatrix();
		glProgramUniformMatrix4fv( _idProgram, _locMVP, 1, GL_FALSE, glm::value_ptr(MVP) );
	
	}
}