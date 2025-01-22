#include "camera.cpp"

namespace ENV_GEN {

    Camera::Camera() {
        _updateViewMatrix();
        _updateProjectionMatrix();

    }

    void Camera::setPosition(const glm::vec3 & position) {
        _position = position;
        _updateViewMatrix();
    }

    glm::vec3 Camera::getPosition() {
        return _position;
    }

    void Camera::setLookAt(const glm::vec3 & point) {
        _front = glm::normalize(point - _position);
        _updateVectors();
    }

    void Camera::setFov(const float fov) {
        _fov = fov;
    }

    float Camera::getFov() {
        return _fov;
    }

    void Camera::setScreenSize(const uint width, const uint height) {
        _screenWidth    = width;
        _screenHeight   = height;

        _aspectRatio =  float( _screenWidth ) / _screenHeight;

        _updateVectors();
        _updateViewMatrix();
        _updateProjectionMatrix();
    } 


    void Camera::_updateViewMatrix() {
        _view = glm::lookAt( _position, glm::vec3( 0.f ), _up );
    }

    void Camera::_updateProjectionMatrix() {
        _projection = glm::perspective( glm::radians( _fov ), _aspectRatio, _zNear, _zFar );
    }

    void Camera::_updateVectors() {

        _right = glm::normalize( glm::cross( glm::vec3( 0.f, 1.f, 0.f ), -_front ) );
		_up	   = glm::normalize( glm::cross( -_front, _right ) );

    }

}
