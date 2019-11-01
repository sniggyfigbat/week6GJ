#pragma once


#include <vector>
#include "components/component.h"


class GameObject
{
protected:
	std::vector<std::shared_ptr<Component>> m_components;
public:
	void addComponent(const std::shared_ptr<Component>& comp)
	{
		m_components.push_back(comp);
		comp->onAttach(this);
	}

	void onUpdate(float timestep)
	{
		for (auto& comp : m_components)
		{
			comp->onUpdate(timestep);
		}
	}

	std::vector<std::shared_ptr<Component>>::iterator begin() { return m_components.begin(); }
	std::vector<std::shared_ptr<Component>>::iterator end() { return m_components.end(); }
};
