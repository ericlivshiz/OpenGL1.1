#include "RunTimeEditor.h"
#include <GLFW/glfw3.h>
#include <iostream>

void RunTimeEditor::drawWireFrames() const 
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void RunTimeEditor::drawFilled() const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void RunTimeEditor::takeInput() const
{
	if (EDITOR_MODE != 1)
		std::cout << "EDITOR::TAKEINPUT::ERROR::EDITOR_MODE::IS::OFF" << std::endl;

	else {
		std::cout << "Welcome to the Run Time Editor" << std::endl;
	}
}

void RunTimeEditor::Toggle_NoClip()
{
	NO_CLIP_STATE = true;
}

void RunTimeEditor::ToggleOff_Editor()
{
	EDITOR_MODE = false;
}

void RunTimeEditor::ToggleOff_NoClip() 
{
	NO_CLIP_STATE = false;
}