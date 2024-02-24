#pragma once
#include <glm/vec3.hpp>
#include <cstdlib>
#include <iostream>
#include <cmath>

class Physics {
public:
	bool CheckCollisionOnCamera(glm::vec3& pos1, glm::vec3 pos2,float playerHeight, float size2)
	{

		bool collisionX = (std::abs(pos1.x - pos2.x) < size2);
		bool collisionY = (std::abs(pos1.y - pos2.y) < size2 + playerHeight);
		bool collisionZ = (std::abs(pos1.z - pos2.z) < size2);
		bool collision = (collisionX && collisionY && collisionZ);

		return collision;
	}

	glm::vec3 convertRotatedWallPos(glm::vec3& wallPos, glm::vec3& camPos)
	{
		glm::vec3 oldPos = wallPos;
		wallPos.x = (oldPos.z * sin(-90)) + (oldPos.x * cos(-90));
		wallPos.z = (oldPos.z * cos(-90)) + (oldPos.x * sin(-90));

		return wallPos;
	}
};