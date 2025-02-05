#include "block.hpp"

namespace ENV_GEN {

    Block Block::BlockType0 = Block(0);  // Type 0
    Block Block::BlockType1 = Block(1);  // Type 1
    Block Block::BlockType2 = Block(2);  // Type 7


    Block::Block(uint type, const glm::vec3 & size) : _type(type), _size(size) {
        _position = {
            1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
        };
    }




}