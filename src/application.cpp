#include "application.hpp"

namespace APP {
    
    Application::Application( const std::string & title, const uint width, const uint height) :
        _title(title), _width(width), _height(height) {
            
        _initGLFW();
        _initWindows();

        glfwMakeContextCurrent(_window);

        _initGLEW();

        glfwSetWindowUserPointer        (_window, this);
        glfwSetKeyCallback              (_window, Application::_handleKeyEventsWrapper);
        glfwSetMouseButtonCallback      (_window, Application::_handleMouseButtonEventsWrapper);
        glfwSetCursorPosCallback        (_window, Application::_handleCursorPositionEventsWrapper);
        glfwSetScrollCallback           (_window, Application::_handleScrollEventsWrapper);
        glfwSetFramebufferSizeCallback  (_window, Application::_handleResizeEventsWrapper);

        _renderer.resize( _width, _height );
        _renderer.init();

        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        std::cout << "Application initialized." << std::endl;
    }

    Application::~Application() {

        std::cout << "Stop application." << std::endl;

        glfwTerminate();
        glfwDestroyWindow(_window);

        std::cout << "Application stoped." << std::endl;
        
    }

    uint Application::run() {
        double  deltaTime       = 0.0,
                currentTime     = 0.0,
                previousTime    = glfwGetTime();

        std::cout << "Running application." << std::endl;

        _chunk = new ENV_GEN::Chunk(glm::ivec3(0, 0, 0));
        _player = new ENTITY::Player(glm::vec3(0.f, 7.f, 0.f));

        while (!glfwWindowShouldClose(_window)) {
            currentTime     = glfwGetTime();
            deltaTime       = currentTime - previousTime;
            previousTime    = currentTime;

            _renderer.animate(deltaTime, _player);
            _renderer.render(_chunk, _player);
            
            glfwSwapBuffers(_window);
            glfwPollEvents();

            std::cout << 1/deltaTime << " fps." << std::endl;
        }

        return 0;
    }


    void Application::_initWindows() {

        std::cout << "Initializing window." << std::endl;

        _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);

        if (!_window) {
            glfwTerminate();
            UTILS::error(UTILS::WINDOW_ERROR);
        }
    }


    void Application::_initGLFW() {

        std::cout << "Initializing GLFW." << std::endl;

        if (!glfwInit()) UTILS::error(UTILS::GLFW_ERROR);
    }

    void Application::_initGLEW() {

        std::cout << "Initializing GLEW" << std::endl;

        if (glewInit() != GLEW_OK) UTILS::error(UTILS::GLEW_ERROR);

    }

    void Application::_handleKeyEvents(const uint key, const uint scancode, const uint action, const uint mods) {

        std::cout << "key :" << key << " action:" << action << " mods:" << mods << " scancode:" << scancode << std::endl;
        
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            std::cout << "Echap pressed, closing window.\n";
            glfwSetWindowShouldClose(_window, true);
        }

        _renderer.handleInputEvents(key, action);

    }

    void Application::_handleMouseButtonEvents(const uint button, const uint action, const uint mods) {
        //std::cout << "button :" << button << " action:" << action << " mods:" << mods << std::endl;

        _renderer.handleInputEvents(button, action);

    }

    void Application::_handleCursorPositionEvents(const double xpos, const double ypos) {
        //std::cout << "xpos :" << xpos << " ypos:" << ypos << std::endl;

        _renderer.handleMousePosition( xpos - _oldx, ypos - _oldy);
        _oldx = _width / 2.0;
        _oldy = _height / 2.0;
        glfwSetCursorPos(_window, _width / 2.0, _height / 2.0);
    }

    void Application::_handleScrollEvents(const double xoffset, const double yoffset) {
        std::cout << "xoffset :" << xoffset << " yoffset:" << yoffset << std::endl;
    }

    void Application::_handleResizeEvents(const uint width, const uint height) {
        std::cout << "width :" << width << " height:" << height << std::endl;

        _width = width;
        _height = height;
        _renderer.resize(_width, _height);
    }

}
