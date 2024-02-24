#pragma once

#include "Util/stb_image.h"
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

constexpr int CUBEVERTSIZE = 108;

struct Cube {
    float cubeLength = 6.0f;

    void Initialize(unsigned int& cubeVBO, unsigned int& cubeVAO) 
    {
        float cubeVertices[] = {
            -cubeLength, -cubeLength, -cubeLength,  0.0f, 0.0f,
             cubeLength, -cubeLength, -cubeLength,  1.0f, 0.0f,
             cubeLength,  cubeLength, -cubeLength,  1.0f, 1.0f,
             cubeLength,  cubeLength, -cubeLength,  1.0f, 1.0f,
            -cubeLength,  cubeLength, -cubeLength,  0.0f, 1.0f,
            -cubeLength, -cubeLength, -cubeLength,  0.0f, 0.0f,

            -cubeLength, -cubeLength,  cubeLength,  0.0f, 0.0f,
             cubeLength, -cubeLength,  cubeLength,  1.0f, 0.0f,
             cubeLength,  cubeLength,  cubeLength,  1.0f, 1.0f,
             cubeLength,  cubeLength,  cubeLength,  1.0f, 1.0f,
            -cubeLength,  cubeLength,  cubeLength,  0.0f, 1.0f,
            -cubeLength, -cubeLength,  cubeLength,  0.0f, 0.0f,

            -cubeLength,  cubeLength,  cubeLength,  1.0f, 0.0f,
            -cubeLength,  cubeLength, -cubeLength,  1.0f, 1.0f,
            -cubeLength, -cubeLength, -cubeLength,  0.0f, 1.0f,
            -cubeLength, -cubeLength, -cubeLength,  0.0f, 1.0f,
            -cubeLength, -cubeLength,  cubeLength,  0.0f, 0.0f,
            -cubeLength,  cubeLength,  cubeLength,  1.0f, 0.0f,

             cubeLength,  cubeLength,  cubeLength,  1.0f, 0.0f,
             cubeLength,  cubeLength, -cubeLength,  1.0f, 1.0f,
             cubeLength, -cubeLength, -cubeLength,  0.0f, 1.0f,
             cubeLength, -cubeLength, -cubeLength,  0.0f, 1.0f,
             cubeLength, -cubeLength,  cubeLength,  0.0f, 0.0f,
             cubeLength,  cubeLength,  cubeLength,  1.0f, 0.0f,

            -cubeLength, -cubeLength, -cubeLength,  0.0f, 1.0f,
             cubeLength, -cubeLength, -cubeLength,  1.0f, 1.0f,
             cubeLength, -cubeLength,  cubeLength,  1.0f, 0.0f,
             cubeLength, -cubeLength,  cubeLength,  1.0f, 0.0f,
            -cubeLength, -cubeLength,  cubeLength,  0.0f, 0.0f,
            -cubeLength, -cubeLength, -cubeLength,  0.0f, 1.0f,

            -cubeLength,  cubeLength, -cubeLength,  0.0f, 1.0f,
             cubeLength,  cubeLength, -cubeLength,  1.0f, 1.0f,
             cubeLength,  cubeLength,  cubeLength,  1.0f, 0.0f,
             cubeLength,  cubeLength,  cubeLength,  1.0f, 0.0f,
            -cubeLength,  cubeLength,  cubeLength,  0.0f, 0.0f,
            -cubeLength,  cubeLength, -cubeLength,  0.0f, 1.0f
        };

        // set VBO and VAO
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);

        glBindVertexArray(cubeVAO);

        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
        
        // set data for cube
        glBindVertexArray(cubeVAO);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    };

};

struct Wall {
    const float wallLength = 5.0f;
    const float wallLengthX = 60.0f;
    const float wallLengthZ = 70.0f;
    const float marbleWallHeight = 10.0f;
    void InitializeMarbleWall(unsigned int& wallVBO, unsigned int& wallVAO)
    {
        float wallVertices[] = {
            -wallLengthX, -marbleWallHeight, -wallLengthZ,  0.0f, 0.0f,
             wallLengthX, -marbleWallHeight, -wallLengthZ,  5.f, 0.0f,
             wallLengthX,  marbleWallHeight, -wallLengthZ,  5.f, 5.f,
             wallLengthX,  marbleWallHeight, -wallLengthZ,  5.f, 5.f,
            -wallLengthX,  marbleWallHeight, -wallLengthZ,  0.0f, 5.f,
            -wallLengthX, -marbleWallHeight, -wallLengthZ,  0.0f, 0.0f,

            -wallLengthX, -marbleWallHeight,  wallLengthZ,  0.0f, 0.0f,
             wallLengthX, -marbleWallHeight,  wallLengthZ,  5.f, 0.0f,
             wallLengthX,  marbleWallHeight,  wallLengthZ,  5.f, 5.0f,
             wallLengthX,  marbleWallHeight,  wallLengthZ,  5.f, 5.f,
            -wallLengthX,  marbleWallHeight,  wallLengthZ,  0.0f, 5.f,
            -wallLengthX, -marbleWallHeight,  wallLengthZ,  0.0f, 0.0f,

            -wallLengthX,  marbleWallHeight,  wallLengthZ,  5.f, 0.0f,
            -wallLengthX,  marbleWallHeight, -wallLengthZ,  5.f, 5.f,
            -wallLengthX, -marbleWallHeight, -wallLengthZ,  0.0f, 5.f,
            -wallLengthX, -marbleWallHeight, -wallLengthZ,  0.0f, 5.f,
            -wallLengthX, -marbleWallHeight,  wallLengthZ,  0.0f, 0.0f,
            -wallLengthX,  marbleWallHeight,  wallLengthZ,  5.f, 0.0f,

             wallLengthX,  marbleWallHeight,  wallLengthZ,  5.f, 0.0f,
             wallLengthX,  marbleWallHeight, -wallLengthZ,  5.f, 5.f,
             wallLengthX, -marbleWallHeight, -wallLengthZ,  0.0f, 5.f,
             wallLengthX, -marbleWallHeight, -wallLengthZ,  0.0f, 5.f,
             wallLengthX, -marbleWallHeight,  wallLengthZ,  0.0f, 0.0f,
             wallLengthX,  marbleWallHeight,  wallLengthZ,  5.f, 0.0f,
        };

        // set VBO and VAO
        glGenVertexArrays(1, &wallVAO);
        glGenBuffers(1, &wallVBO);

        glBindVertexArray(wallVAO);

        glBindBuffer(GL_ARRAY_BUFFER, wallVBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(wallVertices), wallVertices, GL_STATIC_DRAW);

        // set data for cube
        glBindVertexArray(wallVAO);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    void InitializeDirOne(unsigned int& wallVBO, unsigned int& wallVAO) 
    {
        float wallVertices[] = {
            -wallLength, -wallLength,  wallLength,  0.0f, 0.0f,
             wallLength, -wallLength,  wallLength,  1.0f, 0.0f,
             wallLength,  wallLength,  wallLength,  1.0f, 1.0f,
             wallLength,  wallLength,  wallLength,  1.0f, 1.0f,
            -wallLength,  wallLength,  wallLength,  0.0f, 1.0f,
            -wallLength, -wallLength,  wallLength,  0.0f, 0.0f,
        };

        glGenVertexArrays(1, &wallVAO);
        glGenBuffers(1, &wallVBO);

        glBindVertexArray(wallVAO);

        glBindBuffer(GL_ARRAY_BUFFER, wallVBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(wallVertices), wallVertices, GL_STATIC_DRAW);

        glBindVertexArray(wallVAO);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    void InitializeDirTwo(unsigned int& wallVBO, unsigned int& wallVAO)
    {
        float wallVertices[] = {
        -wallLength,  wallLength,  wallLength,  1.0f, 0.0f,
        -wallLength,  wallLength, -wallLength,  1.0f, 1.0f,
        -wallLength, -wallLength, -wallLength,  0.0f, 1.0f,
        -wallLength, -wallLength, -wallLength,  0.0f, 1.0f,
        -wallLength, -wallLength,  wallLength,  0.0f, 0.0f,
        -wallLength,  wallLength,  wallLength,  1.0f, 0.0f,
        };

        glGenVertexArrays(1, &wallVAO);
        glGenBuffers(1, &wallVBO);

        glBindVertexArray(wallVAO);

        glBindBuffer(GL_ARRAY_BUFFER, wallVBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(wallVertices), wallVertices, GL_STATIC_DRAW);

        glBindVertexArray(wallVAO);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
};

struct Floor{
    const float floorLength = 5.0f;

    void Initialize(unsigned int& floorVBO, unsigned int& floorVAO) 
    {
        float floorVertices[] = {
            // floor vertices
             -floorLength, -floorLength, -floorLength,  0.0f, 0.0f,
             floorLength, -floorLength,  -floorLength,  1.0f, 0.0f,
             floorLength,  -floorLength, floorLength,  1.0f, 1.0f,
             floorLength,  -floorLength,  floorLength,  1.0f, 1.0f,
            -floorLength,  -floorLength, floorLength,  0.0f, 1.0f,
            -floorLength, -floorLength, -floorLength,  0.0f, 0.0f,

        };

        glGenVertexArrays(1, &floorVAO);
        glGenBuffers(1, &floorVBO);

        glBindVertexArray(floorVAO);

        glBindBuffer(GL_ARRAY_BUFFER, floorVBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);

        glBindVertexArray(floorVAO);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
};

struct WeaponSquare {
    void Initialize(unsigned int& floorVBO, unsigned int& floorVAO)
    {
        float unitLength = 5.0f;
        float smallSize = 2.5f;
        float shaderCoords = 1.5f;
        float glockVertices[] = {
            -unitLength, -unitLength,  unitLength,  0.0f, 0.0f,
             unitLength, -unitLength,  unitLength,  shaderCoords, 0.0f,
             unitLength,  unitLength,  unitLength,  shaderCoords, shaderCoords,
             unitLength,  unitLength,  unitLength,  shaderCoords, shaderCoords,
            -unitLength,  unitLength,  unitLength,  0.0f, shaderCoords,
            -unitLength, -unitLength,  unitLength,  0.0f, 0.0f,
        };

        glGenVertexArrays(1, &floorVAO);
        glGenBuffers(1, &floorVBO);

        glBindVertexArray(floorVAO);

        glBindBuffer(GL_ARRAY_BUFFER, floorVBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(glockVertices), glockVertices, GL_STATIC_DRAW);

        glBindVertexArray(floorVAO);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
};

class ObjectMgr {
public:
    Cube cube;
    Wall wall;
    Floor floor;
    WeaponSquare weaponSquare;

    void InitializeCube(unsigned int& cubeVBO, unsigned int& cubeVAO)
    {
        cube.Initialize(cubeVBO, cubeVAO);
    }

    void InitializeWallDirOne(unsigned int& wallVBO, unsigned int& wallVAO)
    {
        wall.InitializeDirOne(wallVBO, wallVAO);
    }

    void InitializeWallDirTwo(unsigned int& wallVBO, unsigned int& wallVAO)
    {
        wall.InitializeDirTwo(wallVBO, wallVAO);
    }

    void InitalizeMarbleWall(unsigned int& wallVBO, unsigned int& wallVAO)
    {
        wall.InitializeMarbleWall(wallVBO, wallVAO);
    }

    void InitializeFloor(unsigned int& floorVBO, unsigned int& wallVAO)
    {
        floor.Initialize(floorVBO, wallVAO);
    }

    void InitializeWeaponSquare(unsigned int& wsVBO, unsigned int& wsVAO)
    {
        weaponSquare.Initialize(wsVBO, wsVAO);
    }

    void HandleTexture(unsigned int& t1, unsigned int& t2, int& width, int& height, int& nrChannels, const char* path)
    {
        glGenTextures(1, &t1);
        glBindTexture(GL_TEXTURE_2D, t1);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    float getCubeLength() {
        return cube.cubeLength;
    }

    float getWallLength() {
        return wall.wallLength;
    }

    float getFloorLength() {
        return floor.floorLength;
    }
};