#pragma once

#include <cmath>
#include <glm/glm.hpp>

class GameObject
{
protected:
	char * m_texture;
	bool m_markedForDeletion = 0;
public:
	virtual void onKeyPress(int keyPress) = 0;
	virtual void onUpdate(float timestep) = 0;
	virtual void onDelete() = 0;
	void markForDeletion() { m_markedForDeletion = true; }
	static glm::ivec2 view(glm::vec2 vec) { return glm::ivec2(std::round(vec.x * 6.0f), std::round(vec.y * 3.f)); }
	static glm::ivec2 view(float x, float y) { return glm::ivec2(std::round(x * 6.0f), std::round(y * 3.f)); }
	static glm::vec2 invView(glm::ivec2 vec) { return glm::vec2((float)vec.x * 1.0f/6.0f, (float)vec.y * 1.0f/3.f); }
	static glm::vec2 invView(int x, int y) { return glm::vec2((float)x * 1.0f/6.0f, (float)y * 1.0f/3.f); }
};
