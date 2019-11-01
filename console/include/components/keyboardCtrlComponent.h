#pragma once

#include "component.h"
#include <glm/glm.hpp>

class KeyboardCtrlComponent : public Component
{
private:
	glm::ivec2 m_data;
public:
	void receiveMessage(const ComponentMessage& msg)
	{
		if (msg.m_msgType == ComponentMessageType::KeyPressed)
		{
			int* addr = (int*)msg.m_msgData;
			int keyCode = *addr;

			switch (keyCode)
			{
			case 232:
				m_data.x = 0;
				m_data.y = -1;
				sendMessage(ComponentMessage(ComponentMessageType::SetPosition, (void*)&m_data));
				break;
			case 237:
				m_data.x = 1;
				m_data.y = 0;
				sendMessage(ComponentMessage(ComponentMessageType::SetPosition, (void*)&m_data));
				break;
			case 240:
				m_data.x = 0;
				m_data.y = 1;
				sendMessage(ComponentMessage(ComponentMessageType::SetPosition, (void*)&m_data));
				break;
			case 235:
				m_data.x = -1;
				m_data.y = 0;
				sendMessage(ComponentMessage(ComponentMessageType::SetPosition, (void*)&m_data));
				break;
			}
		}
	}
};