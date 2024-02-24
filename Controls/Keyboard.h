#pragma once

enum Keyboard_Controls {
	SHIFT,
	CTRL
};


class Keyboard {
public:
	const float SHIFT_SPEED = 10.0f;
	const float CROUCH_SPEED = 5.0f;

	void ShiftWalk(float& MovementSpeed, bool& isShiftWalking)
	{
		MovementSpeed = SHIFT_SPEED;
		isShiftWalking = true;
	}

	void Crouch(glm::vec3& Position, float& eyeHeight, bool& isCrouched)
	{
		Position.y = eyeHeight / 2;
		isCrouched = true;
	}

	void CrouchWalk(float& MovementSpeed)
	{
		MovementSpeed = CROUCH_SPEED;
	}
};