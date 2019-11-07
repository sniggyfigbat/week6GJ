
#include "drawable.h"

Drawable::Drawable(glm::vec2 position, glm::vec2 size, int count, char* texture)
{
	//m_animatedMat.setPosition(((glm::vec2)position) * glm::vec2((1.f /6.0f), (1.f/3.0f)));
	m_animatedMat.setPosition(view(position));
	m_animatedMat.setSize(view(size));
	m_animatedMat.setCount(count);
	m_animatedMat.setData(texture);

	m_currentFrame = 0;
	m_numFrames = 0;
}

void Drawable::onKeyPress(int keyPress) 
{
}
void Drawable::onUpdate(float timestep) 
{
	m_animatedMat.setTexture(m_Textures[m_currentFrame]);
	m_currentFrame++;
	if (m_currentFrame >= m_numFrames)
	{
		m_currentFrame = 0;
	}
}
void Drawable::onDelete() 
{
}

void Drawable::addFrame(char * texture)
{
	m_Textures.push_back(texture);
	m_numFrames++;
}
