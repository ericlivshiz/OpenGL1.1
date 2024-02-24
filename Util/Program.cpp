#include "Program.h"
#include <GLFW/glfw3.h>

#include <iostream>

void Program::InitializeGLFW() const
{
	glfwInit();
}

void Program::ConfigureGLFW() const
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

int Program::LoadGLFunctionPointers() const
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
}

void Program::HandlePositionAttrib() const 
{
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
void Program::HandleTexCoordAttrib() const 
{
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Program::SetVBOandVAO(unsigned int& VBO, unsigned int& VAO) const
{
	VBOandVAO_GenandBind(VBO, VAO);
}

void Program::SetTexture(unsigned int& texture) const
{
	GenAndBindTexture(texture);
	SetTextureWrapping();
	SetTextureFiltering();
}

void Program::setProjectionOnAllObjects(Shader& f, Shader& c, Shader& mwdo, Shader& mwdt, Shader& swdo, Shader& swdt, Shader& ggs, glm::mat4& projection)
{
	f.setMat4("projection", projection);
	c.setMat4("projection", projection);
	mwdo.setMat4("projection", projection);
	mwdt.setMat4("projection", projection);
	swdo.setMat4("projection", projection);
	swdt.setMat4("projection", projection);
	ggs.setMat4("projection", projection);
}

void Program::setViewOnAllObjects(Shader& f, Shader& c, Shader& mwdo, Shader& mwdt, Shader& swdo, Shader& swdt, Shader& ggs, glm::mat4& view)
{
	f.setMat4("view", view);
	c.setMat4("view", view);
	mwdo.setMat4("view", view);
	mwdt.setMat4("view", view);
	swdo.setMat4("view", view);
	swdt.setMat4("view", view);
	ggs.setMat4("view", view);
}

void Program::activateAllShaders(Shader& f, Shader& c, Shader& mwdo, Shader& mwdt, Shader& swdo, Shader& swdt, Shader& ggs)
{
	f.use();
	c.use();
	mwdo.use();
	mwdt.use();
	swdo.use();
	swdt.use();
	ggs.use();
}

void Program::ValidateMoveAfterCollision
(
	Camera_Movement direction, Camera& camera, Physics& physics, Player& player, 
	std::vector<glm::vec3>& collidedWith, float& deltaTime
)
{
	// bool isValid = true;
	glm::vec3 safePos = player.lastSafePosition;

	camera.ProcessKeyboard(direction, deltaTime, 0);

	for (unsigned int i = 0; i < collidedWith.size(); i++)
	{
		if (physics.CheckCollisionOnCamera(camera.Position, collidedWith[i], player.PLAYER_EYE_HEIGHT, 10))
		{
			std::cout << "INVALID::MOVE::COLLISION::DETECTED" << std::endl;
			//bool isValid = false;
			// camera.Position = safePos;
		}
		
	}
	/*if (isValid)
	{
		camera.Position = currPos;
		camera.ProcessKeyboard(direction, deltaTime, 0);
	}*/



}
