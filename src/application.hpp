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


            // Inputs
            void _handleKeyEvents(const uint key, const uint scancode, const uint action, const uint mods);
            void _handleMouseButtonEvents(const uint button, const uint action, const uint mods);
            void _handleCursorPositionEvents(const double xpos, const double ypos);
            void _handleScrollEvents(const double xoffset, const double yoffset);
            void _handleResizeEvents(const uint width, const uint height);


            // Inputs Wrapper
            static void _handleKeyEventsWrapper(GLFWwindow* window, int key, int scancode, int action, int mods) {
                Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
                if (app) {
                    app->_handleKeyEvents(key, scancode, action, mods);
                }
            }
            
            static void _handleMouseButtonEventsWrapper(GLFWwindow* window, int button, int action, int mods) {
                Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
                if (app) {
                    app->_handleMouseButtonEvents(button, action, mods);
                }
            }

            static void _handleCursorPositionEventsWrapper(GLFWwindow* window, double xpos, double ypos) {
                Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
                if (app) {
                    app->_handleCursorPositionEvents(xpos, ypos);
                }
            }

            static void _handleScrollEventsWrapper(GLFWwindow* window, double xoffset, double yoffset) {
                Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
                if (app) {
                    app->_handleScrollEvents(xoffset, yoffset);
                }
            }

            static void _handleResizeEventsWrapper(GLFWwindow* window, int width, int height) {
                Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
                if (app) {
                    app->_handleResizeEvents(width, height);
                }
    }
        private:

            const std::string _title;

            uint _width;
            uint _height;

            GLFWwindow* _window;

            double _oldx = 0.f;
            double _oldy = 0.f;

            Renderer _renderer;
    };
}

#endif // __APPLICATION_HPP__