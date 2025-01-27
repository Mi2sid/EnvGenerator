#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ENV_GEN {

    class Camera {
        public:
            Camera();

            inline const glm::mat4 & getViewMatrix() const { return _view; }
		    inline const glm::mat4 & getProjectionMatrix() const { return _projection; }

            void setPosition( const glm::vec3 & position );
            glm::vec3 getPosition();
            void setLookAt( const glm::vec3 & point );

            void setFov(const float fov);
            float getFov();

            void setScreenSize(const uint width, const uint height);

            void rotate(const float deltaX, const float deltaY);

            void moveFront(const float delta);
            void moveRight(const float delta);
            void moveUp(const float delta);

        private:

            void _updateViewMatrix();
            void _updateProjectionMatrix();
            void _updateVectors();

        private:
            glm::vec3 _position = glm::vec3(0.f, 0.f, 0.f);
            glm::vec3 _front    = glm::vec3(0.f, 0.f, -1.f); 
            glm::vec3 _right    = glm::vec3(-1.f, 0.f, 0.f);
            glm::vec3 _up       = glm::vec3(0.f, 1.f, 0.f);

            float _yaw	 = 90.f;
		    float _pitch = 0.f;

            uint _screenWidth   = 1280;
            uint _screenHeight  = 720;
		    
            float _aspectRatio	= float( _screenWidth ) / _screenHeight;
            
            float _fov          = 60.f;
            const float _zNear  = 0.1f;
            const float _zFar   = 1000.f;

            glm::mat4 _view;
            glm::mat4 _projection;
    };
}




#endif // __CAMERA_HPP__