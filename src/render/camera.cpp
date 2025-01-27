#include "camera.hpp"

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

        _front  = glm::normalize(point - _position);
        _pitch  = glm::clamp( glm::degrees( glm::asin( -_front.y ) ), -89.f, 89.f );
		_yaw	= glm::degrees( glm::atan( -_front.z, -_front.x ) );

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

    void resize(const uint width, const uint height) {

    }


    void Camera::rotate(const float deltaX, const float deltaY) {
        _yaw   = glm::mod( _yaw + deltaX, 360.f );
		_pitch = glm::clamp( _pitch + deltaY, -89.f, 89.f );
		_updateVectors();
    }

    void Camera::moveFront(const float delta) {
        _position += _front * delta;
        _updateViewMatrix();
    }

    void Camera::moveRight(const float delta) {
        _position += _right * delta;
        _updateViewMatrix();
    }

    void Camera::moveUp(const float delta) {
        _position += _up * delta;
        _updateViewMatrix();
    }

    void Camera::_updateViewMatrix() {
        _view = glm::lookAt( _position, _position + _front, _up );
    }

    void Camera::_updateProjectionMatrix() {
        _projection = glm::perspective( glm::radians( _fov ), _aspectRatio, _zNear, _zFar );
    }

    void Camera::_updateVectors() {

        _right = glm::normalize( glm::cross( glm::vec3( 0.f, 1.f, 0.f ), -_front ) );
		_up	   = glm::normalize( glm::cross( -_front, _right ) );

        const float yaw	  = glm::radians( _yaw );
		const float pitch = glm::radians( _pitch );
		_front = -glm::normalize( glm::vec3( glm::cos( yaw ) * glm::cos( pitch ), glm::sin( pitch ), glm::sin( yaw ) * glm::cos( pitch ) ) );
		_right = glm::normalize( glm::cross( glm::vec3( 0.f, 1.f, 0.f ), -_front ) );
		_up	   = glm::normalize( glm::cross( -_front, _right ) );

        _updateViewMatrix();
    }

}
