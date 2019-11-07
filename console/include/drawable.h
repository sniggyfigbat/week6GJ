#pragma once

#include "label.h"
#include<glm/glm.hpp>
#include <vector>

class Drawable : public GameObject
{
protected:

	
	ConsoleMaterial m_animatedMat;
	int m_numFrames, m_currentFrame;
	std::vector<char*> m_Textures;

public:
	Drawable() {};
	Drawable(glm::vec2 position, glm::vec2 size, int count, char* texture);

	void onKeyPress(int keyPress);
	void onUpdate(float timestep);
	void onDelete();
	void addFrame(char* texture);
	inline ConsoleMaterial getMaterial() { return  m_animatedMat; }

};