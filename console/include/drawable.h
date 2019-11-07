#pragma once

#include "label.h"
#include<glm/glm.hpp>
#include <vector>
#include <map>

class Drawable : public GameObject
{
protected:

	
	ConsoleMaterial m_animatedMat;
	int m_numFrames, m_currentFrame;
	std::vector<char*> m_Textures;

public:
	Drawable() {};
	Drawable(glm::vec2 position, glm::vec2 size, int count, char* texture);

	virtual void onKeyPress(int keyPress);
	virtual void onUpdate(float timestep);
	void onDelete();
	void addFrame(char* texture);
	void addFrame(char* texture, const std::map<unsigned int, char>& specialChars);
	inline ConsoleMaterial getMaterial() { return  m_animatedMat; }

};