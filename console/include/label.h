#pragma once


#include "gameObject.h"
#include "consoleMaterial.h"

class Label : public GameObject
{
private:
	ConsoleMaterial m_material;
public:
	Label() {};
	Label(glm::vec2 position, glm::vec2 size, int count, char* texture)
	{
		//m_material.setPosition(((glm::vec2)position) * glm::vec2((1.f /6.0f), (1.f/3.0f)));
		m_material.setPosition(view(position));
		m_material.setSize(view(size));
		m_material.setCount(count);
		m_material.setData(texture);
	}
	void onKeyPress(int keyPress) {};
	void onUpdate(float timestep) {};
	void onDelete() {};
	inline ConsoleMaterial getMaterial() { return  m_material; }
};