#include "application.hpp"


namespace ENV_GEN {
    
    Application::Application( const std::string & title, const uint width, const uint height) :
        _title(title), _width(width), _height(height) {
            
        _initGLFW();
        _initWindows();

        glfwMakeContextCurrent(_window);

        _initGLEW();

        _renderer.init();

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

        while (!glfwWindowShouldClose(_window)) {
            currentTime     = glfwGetTime();
            deltaTime       = currentTime - previousTime;
            previousTime    = currentTime;

            //A.animate(deltaTime);

            // Rendu 
            _renderer.render();

            glfwSwapBuffers(_window);
            glfwPollEvents();
        }

        return 0;
    }


    void Application::_initWindows() {

        std::cout << "Initializing window." << std::endl;

        _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);

        if (!_window) {
            glfwTerminate();
            error(WINDOW_ERROR);
        }
    }


    void Application::_initGLFW() {

        std::cout << "Initializing GLFW." << std::endl;

        if (!glfwInit()) error(GLFW_ERROR);
    }

    void Application::_initGLEW() {

        std::cout << "Initializing GLEW" << std::endl;

        if (glewInit() != GLEW_OK) error(GLEW_ERROR);

    }
}
