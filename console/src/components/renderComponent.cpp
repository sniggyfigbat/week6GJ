#include "components/renderComponent.h"

RenderComponent::RenderComponent()
{
	m_material.setCount(0);
	m_material.setSize(glm::ivec2(0,0));
	m_material.setPosition(glm::ivec2(0, 0));
}

RenderComponent::~RenderComponent()
{
}

RenderComponent::RenderComponent(char* data, int size, int width, int height, int x, int y)
{
	m_material.setCount(width * height);
	m_material.setData(data);
	m_material.setSize(glm::ivec2(width, height));
	m_material.setPosition( glm::ivec2(x, y));
}