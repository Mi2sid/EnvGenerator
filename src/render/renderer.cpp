#include "renderer.hpp"

namespace RENDER {

	const std::vector<glm::vec3> GLCube::vertexPosition = {
	    { -0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f, -0.5f }, { 0.5f,  0.5f, -0.5f }, { -0.5f,  0.5f, -0.5f }, // Face arrière
	    { -0.5f, -0.5f,  0.5f }, { 0.5f, -0.5f,  0.5f }, { 0.5f,  0.5f,  0.5f }, { -0.5f,  0.5f,  0.5f }  // Face avant
	};

	const std::vector<uint> GLCube::vertexIndex = {
	    0, 1, 2, 2, 3, 0, // Face arrière
	    4, 5, 6, 6, 7, 4, // Face avant
	    4, 5, 1, 1, 0, 4, // Face bas
	    7, 6, 2, 2, 3, 7, // Face haut
	    4, 0, 3, 3, 7, 4, // Face gauche
	    5, 1, 2, 2, 6, 5  // Face droite
	};

	static const std::vector<glm::vec4> _atlas = {
    	glm::vec4(1.0f, 1.0f, 1.0f, 1.f),
    	glm::vec4(0.7f, 0.7f, 0.7f, 1.f),
    	glm::vec4(0.5f, 0.3f, 0.1f, 1.f)
	};

    Renderer::~Renderer() {

		glDeleteProgram(_idProgram);

		glDeleteBuffers( 1, &_cubeSample.vbo_vertex );
		glDeleteBuffers( 1, &_cubeSample.vbo_color );

		glDeleteVertexArrays( 1, &_cubeSample.vao );

		glDeleteBuffers(1, &_cubeSample.ebo);
		glDisable( GL_DEPTH_TEST );
    }

    void Renderer::init() {
        std::cout << "Initializing Renderer." << std::endl;

		glClearColor( _backgroundColor.x, _backgroundColor.y, _backgroundColor.z, _backgroundColor.w );
    
		glEnable(GL_DEPTH_TEST);

        const std::string vertShaderSource = UTILS::readFile(_shaderFolder + "initialVert.glsl");
        const std::string fragShaderSource = UTILS::readFile(_shaderFolder + "initialFrag.glsl");

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
            UTILS::error(UTILS::COMPILE_SHADER_ERROR, log);
		}

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &verified);
		if (!verified)
		{
			GLchar log[1024];
			glGetShaderInfoLog(fragmentShader,sizeof(log), NULL, log);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			UTILS::error(UTILS::COMPILE_SHADER_ERROR, log);
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
			UTILS::error(UTILS::LINK_PROGRAM_ERROR, log);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		for ( int i = 0; i < _cubeSample.vertexPosition.size() ; i++ )
			_cubeSample.vertexColor.push_back( glm::vec4( static_cast<float>(std::rand()) / RAND_MAX, static_cast<float>(std::rand()) / RAND_MAX, static_cast<float>(std::rand()) / RAND_MAX, 1.f ) );

		_locMVP 		= glGetUniformLocation( _idProgram, "uMVPMatrix" );
		_locAtlas 		= glGetUniformLocation( _idProgram, "uAtlas" );
		_locAtlasIndex	= glGetUniformLocation( _idProgram, "uAtlasIndex" );

		// camera
		_fov = _camera.getFov();
		_camera.setPosition( glm::vec3( 1.f, 1.f, 4.f ) );
		_camera.setScreenSize( 1280, 720 );
				
		glUseProgram( _idProgram );

		glUniform4fv(_locAtlas, _atlas.size(), &_atlas[0][0]);

		// vao
		glCreateVertexArrays( 1, &_cubeSample.vao);
		glEnableVertexArrayAttrib( _cubeSample.vao, 0 );
		glEnableVertexArrayAttrib( _cubeSample.vao, 1 );

		// vbo
		glCreateBuffers( 1, &_cubeSample.vbo_vertex );
		glNamedBufferData( _cubeSample.vbo_vertex, GLCube::vertexPosition.size() * sizeof( glm::vec3 ), GLCube::vertexPosition.data(), GL_STATIC_DRAW );

		// vao, vbo link
		glVertexArrayVertexBuffer	( _cubeSample.vao, 0, _cubeSample.vbo_vertex, 0, sizeof( glm::vec3 ) );
		glVertexArrayAttribFormat	( _cubeSample.vao, 0, 3, GL_FLOAT, GL_FALSE, 0 );
		glVertexArrayAttribBinding	( _cubeSample.vao, 0, 0 );

		// vbo color
		glCreateBuffers( 1, &_cubeSample.vbo_color );
		glNamedBufferData( _cubeSample.vbo_color, _cubeSample.vertexColor.size() * sizeof( glm::vec4 ), _cubeSample.vertexColor.data(), GL_STATIC_DRAW );

		// vao, vbo color link
		glVertexArrayVertexBuffer( _cubeSample.vao, 1, _cubeSample.vbo_color, 0, sizeof( glm::vec4 ) );
		glVertexArrayAttribFormat( _cubeSample.vao, 1, 4, GL_FLOAT, GL_FALSE, 0 );
		glVertexArrayAttribBinding( _cubeSample.vao, 1, 1 );

		// ebo
		glCreateBuffers( 1, &_cubeSample.ebo );
		glNamedBufferData( _cubeSample.ebo, GLCube::vertexIndex.size() * sizeof( uint ), GLCube::vertexIndex.data(), GL_STATIC_DRAW );

		// link vao ebo
		glVertexArrayElementBuffer( _cubeSample.vao, _cubeSample.ebo );

		std::cout << "Renderer initilised!" << std::endl;

    }

    void Renderer::render(ENV_GEN::Chunk* chunk, ENTITY::Player* player) {
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		glBindVertexArray( _cubeSample.vao );

		glm::mat4 VP = _camera.getProjectionMatrix() * _camera.getViewMatrix();
		glm::mat4 MVP;

		for(int x=0; x<ENV_GEN::CHUNK_SIZE; x++)
			for(int y=0; y<ENV_GEN::CHUNK_SIZE; y++)
				for(int z=0; z<ENV_GEN::CHUNK_SIZE; z++){
					if(chunk->_data[x][y][z]._type != 0) {
						MVP = VP * chunk->_data[x][y][z]._position;
						glProgramUniform1i(_idProgram, _locAtlasIndex, chunk->_data[x][y][z]._type);
						glProgramUniformMatrix4fv( _idProgram, _locMVP, 1, GL_FALSE, glm::value_ptr(MVP) );
						glDrawElements( GL_TRIANGLES, (GLsizei) GLCube::vertexIndex.size(), GL_UNSIGNED_INT, 0 );
					}
				}
		MVP = VP * glm::scale(glm::translate({
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f	
		}, player->getPosition() + glm::vec3(0.f, (player->getSize().y  - 1.f) / 2.f, 0.f) ), player->getSize());
		glProgramUniform1i(_idProgram, _locAtlasIndex, 0);
		glProgramUniformMatrix4fv( _idProgram, _locMVP, 1, GL_FALSE, glm::value_ptr(MVP) );
		glDrawElements( GL_TRIANGLES, (GLsizei) GLCube::vertexIndex.size(), GL_UNSIGNED_INT, 0 );
		
		glBindVertexArray( 0 );
    }

	void Renderer::animate(const double deltaT, ENTITY::Player* player){
		player->applyForces();
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
}