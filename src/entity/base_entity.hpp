#ifndef __BASE_ENTITY_HPP__
#define __BASE_ENTITY_HPP__

#include <glm/glm.hpp>


namespace ENTITY {

    class BaseEntity {
        public:

            BaseEntity(const float maxHp, const glm::vec3 & position, const glm::vec3 & size) :
                _maxHp(maxHp), _position(position), _size(size), _hp(maxHp)
            {};

            ~BaseEntity()   = default;

            float getHp() const {return _hp;};
            glm::vec3 getPosition() const {return _position;};
            glm::vec3 getSize() const {return _size;};

            glm::vec3 getVelocity() const {return _velocity;};

            void addForce(const glm::vec3 & force) {
                _velocity = force + _velocity;
            };
            void applyForces(){
                if(glm::length(_velocity) < 0.1f)
                    return;
                _position += glm::normalize(_velocity) * 0.001f;
                _velocity -= glm::normalize(_velocity) * 0.001f;
            }
            virtual void animate() = 0;

        protected:
            const float _maxHp;
            float _hp;
            
            glm::vec3 _position;
            glm::vec3 _front    = {0.f, 0.f, 1.f};
            glm::vec3 _right    = {-1.f, 0.f, 0.f};
            glm::vec3 _up       = {0.f, 1.f, 0.f};



            glm::vec3 _velocity = {0.f, 1.f, 0.f};

            const glm::vec3 _size;   
    };
}

#endif // __BASE_ENTITY_HPP__