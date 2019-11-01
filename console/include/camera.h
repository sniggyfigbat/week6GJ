#pragma once

#include <glm/glm.hpp>

class Camera
{
private:
	glm::ivec2 m_position;
	glm::ivec2 m_size;
public:
	Camera() : m_position(glm::ivec2(0)), m_size(glm::ivec2(0)) {}
	Camera(int x, int y, int width, int height)
	{
		m_position.x = x;
		m_position.y = y;
		m_size.x = width;
		m_size.y = height;
	}
	inline int left() { return m_position.x; }
	inline int top() { return m_position.y; }
	inline int right() { return m_position.x + m_size.x; }
	inline int bottom() { return m_position.y + m_size.y; }
	inline int width() { return m_size.x; }
	inline int height() { return m_size.y; }
};