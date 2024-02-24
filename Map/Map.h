#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "../Controls/Player.h"

class Map {
public:
    // Public member functions
    void InitializePositions();

    // Getter functions
    const std::vector<glm::vec3>& GetCubePositions() const { return cubePositions; };
    const std::vector<glm::vec3>& GetMarbleWallPositions() const { return marbleWallPositions; };
    const std::vector<glm::vec3>& GetMarbleWallDirTwoPositions() const { return marbleWallDirTwoPositions; };
    const std::vector<glm::vec3>& GetStoneWallPositions() const { return stoneWallPositions; };
    const std::vector<glm::vec3>& GetStoneWallDirTwoPositions() const { return stoneWallDirTwoPositions; };
    const std::vector<glm::vec3>& GetFloorPositions() const { return floorPositions; };

    std::vector<std::vector<glm::vec3>> getAllObjects() const {
        return { cubePositions, marbleWallPositions, marbleWallDirTwoPositions,
        stoneWallPositions, stoneWallDirTwoPositions, floorPositions };
    };

    std::vector<glm::vec3> PlayerCollidedWith(Player& player)
    {
        if (player.Collision_Cube)
            return cubePositions;

        if (player.Collision_MarbleWall)
            return marbleWallPositions;

        if (player.Collision_MarbleWallDirTwo)
            return marbleWallDirTwoPositions;

        if (player.Collion_StoneWall)
            return stoneWallPositions;

        if (player.Collision_StoneWallDirTwo)
            return stoneWallDirTwoPositions;
    }

private:
    std::vector<glm::vec3> cubePositions;
    std::vector<glm::vec3> marbleWallPositions;
    std::vector<glm::vec3> marbleWallDirTwoPositions;
    std::vector<glm::vec3> stoneWallPositions;
    std::vector<glm::vec3> stoneWallDirTwoPositions;
    std::vector<glm::vec3> floorPositions;

    float WallEnd = 170.0f;
    float wallSideZ = 60.0f;
    float diffWallSideZ = 50.0f;
};

void Map::InitializePositions() {
    // Initialize your positions here
    // Example:
    cubePositions = {
        glm::vec3(-5.0f, 0.0f, -20.0f),
        glm::vec3(22.0f, 0.0f, 20.0f),
        glm::vec3(-25.0f,  0.5f,  -15.0f)
        // Add more positions as needed
    };

    float marbleWallSide1 = 50.0f;
    float marbleWallSide2 = -40.0f;
    float marbleStart = -30.0f;
    float marbleHeight = 0;
    float stepX = 10.0f;
    float stepZ = 10.0f;

    // Initialize marble wall positions
    for (float y = 0.0f; y <= 10.0f; y += 10.0f) {
        for (float x = -30.0f; x <= 30.0f; x += 10.0f) {
            for (float z = -40.0f; z <= 50.0f; z += 90.0f) {
                marbleWallPositions.push_back(glm::vec3(x, y, z));
            }
        }
    }

    // Initialize marbleWallDirTwoPositions
    for (float z = 50.0f; z >= -30.0f; z -= 10.0f) {
        for (float x = -30.0f; x <= 40.0f; x += 70.0f) {
            for (float y = 0.0f; y <= 10.0f; y += 10.0f) {
                marbleWallDirTwoPositions.push_back(glm::vec3(x, y, z));
            }
        }
    }

    // Initialize stoneWallPositions
    for (float y = 0.0f; y <= 40.0f; y += 10.0f) {
        for (float x = -50.0f; x <= 50.0f; x += 10.0f) {
            stoneWallPositions.push_back(glm::vec3(x, y, WallEnd));
        }
    }

    // Initialize stoneWallDirTwoPositions
    for (float y = 0.0f; y <= 40.0f; y += 10.0f) {
        for (float z = 170.0f; z >= 50.0f; z -= 10.0f) {
            stoneWallDirTwoPositions.push_back(glm::vec3(wallSideZ, y, z));
        }
    }

    // Other side
    for (float y = 0.0f; y <= 40.0f; y += 10.0f) {
        for (float z = 170.0f; z >= 50.0f; z -= 10.0f) {
            stoneWallDirTwoPositions.push_back(glm::vec3(-diffWallSideZ, y, z));
        }
    }

    

    // Initialize floorPositions using multiple for-loops
    for (float x = -50.0f; x <= 50.0f; x += stepX) {
        for (float z = -30.0f; z <= 170.0f; z += stepZ) {
            floorPositions.push_back(glm::vec3(x, 0.0f, z));
        }
    }

}
