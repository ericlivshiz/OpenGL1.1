#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../Controls/Camera.h"
#include "Physics.h"
#include "../Controls/Player.h"
#include "../Util/Shader.h"

class Program {
public:
	void InitializeGLFW() const;
	void ConfigureGLFW() const;
	int LoadGLFunctionPointers() const;
	void HandlePositionAttrib() const;
	void HandleTexCoordAttrib() const;
	void SetVBOandVAO(unsigned int& VBO, unsigned int& VAO) const;
	void SetTexture(unsigned int& texture) const;
	void setProjectionOnAllObjects(Shader& f, Shader& c, Shader& mwdo, Shader& mwdt, Shader& swdo, Shader& swdt, Shader& ggs, glm::mat4& projection);
	void setViewOnAllObjects(Shader& f, Shader& c, Shader& mwdo, Shader& mwdt, Shader& swdo, Shader& swdt, Shader& ggs, glm::mat4& view);
	void activateAllShaders(Shader& f, Shader& c, Shader& mwdo, Shader& mwdt, Shader& swdo, Shader& swdt, Shader& ggs);
	void ValidateMoveAfterCollision(Camera_Movement direction, Camera& camera, Physics& physics, Player& player, std::vector<glm::vec3>& collidedWith, float& deltaTime);
	// void LoadImageTexture(const char* ImagePath, int& width, int& height, int& nrChannels) const;

private:
	void GenAndBindTexture(unsigned int& texture) const
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void SetTextureWrapping() const
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	void SetTextureFiltering() const
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void VBOandVAO_GenandBind(unsigned int& VBO, unsigned int& VAO) const
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	}


};