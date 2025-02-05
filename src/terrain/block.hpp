#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ENV_GEN {
    class Block {
        public:
            Block(uint type = 0, const glm::vec3 & size = glm::vec3(1.0f));

            inline void move(const glm::ivec3 & offset) {
                _position = glm::translate( _position, glm::vec3(offset) );
            };

            static Block BlockType0;
            static Block BlockType1;
            static Block BlockType2;

            glm::mat4 _position;
            glm::vec3 _size;
            
            uint _type;

    };
}

#endif // __BLOCK_HPP__