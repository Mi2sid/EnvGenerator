#include "chunk.hpp"

namespace ENV_GEN {

    Chunk::Chunk(const glm::ivec3 & position) : _position(position) {
        std::cout << "Creating chunk" << std::endl;
        
        for(int x = 0; x < CHUNK_SIZE; x++)
            for(int y = 0; y < CHUNK_SIZE; y++)
                for(int z = 0; z < CHUNK_SIZE; z++) {
                    if(y<5) {
                        _data[x][y][z] = Block::BlockType1;
                    } else {
                        std::mt19937 gen(x + (z*z));
                        std::uniform_int_distribution<int> dist(1, 4);
                        if( dist(gen) > y-4 ){
                            _data[x][y][z] = Block::BlockType2;
                        } else {
                            _data[x][y][z] = Block::BlockType0;
                        }
                    }
                    std::cout << "Chunk " << x << " " << y << " " << z <<  std::endl;

                    _data[x][y][z].move(glm::ivec3(x, y, z));
                }

        std::cout << "Chunk done..." << std::endl;

    };
}