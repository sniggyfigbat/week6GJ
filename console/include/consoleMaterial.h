#pragma once

#include <memory>
#include <cstring>
#include <glm/glm.hpp>

class ConsoleMaterial
{
private:
	char* m_data;
	int m_count;
	glm::ivec2 m_position;
	glm::ivec2 m_size;
public:
	void setData(char* d)
	{
		m_data = (char *)malloc(m_count);
		memcpy(m_data, d, m_count);
	}
	void setTexture(char * d){ 
		memcpy(m_data, d, m_count);
	}
	void setCount(int count) { m_count = count; }
	void setPosition(glm::ivec2 pos) { m_position = pos; }
	void setSize(glm::ivec2 size) { m_size = size; }
	inline glm::ivec2 position() { return m_position; }
	inline glm::ivec2 size() { return m_size; }
	inline int left() const { return m_position.x; }
	inline int top() const { return m_position.y; }
	inline int right() const { return m_position.x + m_size.x; }
	inline int bottom() const { return m_position.y + m_size.y; }
	inline int width() const { return m_size.x; }
	inline int height() const { return m_size.y; }
	inline char* data() const { return m_data; }
}; 
