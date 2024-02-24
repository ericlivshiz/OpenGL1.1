#pragma once

class RunTimeEditor {
public:
	void drawWireFrames() const;
	void drawFilled() const;
	void takeInput() const;
	void Toggle_NoClip();

	void ToggleOff_Editor();
	void ToggleOff_NoClip();


	bool EDITOR_MODE = true;
	bool NO_CLIP_STATE = true;
};