#ifndef __CHUNK_HPP__
#define __CHUNK_HPP__

#include <iostream>
#include <array>
#include <random>

#include "terrain/block.hpp"

namespace ENV_GEN {
    
    constexpr uint CHUNK_SIZE = 10; 
    using Grid = std::array<std::array<std::array<Block, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE>;

    class Chunk {
        public:
            Chunk(const glm::ivec3 & position);

            Grid _data;
        
        private:

            glm::ivec3 _position;
    };
}


#endif // __CHUNK_HPP__