#pragma once
#include <glm/glm.hpp>

struct Player {
	float PLAYER_EYE_HEIGHT = 8.5f;
	bool isShiftWalking = false;
	bool isCrouched = false;
	bool isMoving = false;
	bool Collision = false;
	bool Collision_Cube = false;
	bool Collision_MarbleWall = false;
	bool Collision_MarbleWallDirTwo = false;
	bool Collion_StoneWall = false;
	bool Collision_StoneWallDirTwo = false;
	glm::vec3 lastSafePosition;
	const glm::vec3 WeaponSquarePosition = glm::vec3(0.0f, PLAYER_EYE_HEIGHT / 2, 3.0f);

	void UpdateState()
	{
		if (Collision_Cube || Collision_MarbleWall || Collision_MarbleWallDirTwo ||
			Collion_StoneWall || Collision_StoneWallDirTwo)
		{
			Collision = true;
		}
	}

	glm::vec3 getWeaponSquarePosition()
	{
		return WeaponSquarePosition;
	}
};