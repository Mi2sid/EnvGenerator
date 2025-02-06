#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "entity/base_entity.hpp"

namespace ENTITY {
    class Player : public BaseEntity {
        public:
            Player(const glm::vec3 & position) : BaseEntity(20.f, position, {0.8f, 1.8f, 0.8f}) {};

            void animate();

        private:
        
    };
}



#endif