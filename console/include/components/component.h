#pragma once

#include <memory>

class GameObject;

enum class ComponentMessageType {
	None = 0,
	KeyPressed, SetPosition
};

class ComponentMessage
{
public:
	ComponentMessage(ComponentMessageType type, void * data) : m_msgType(type), m_msgData(data) {};
	ComponentMessageType m_msgType; //!< Message type
	void * m_msgData; //!< Data associated with the message 
};


class Component
{
protected:
	GameObject* m_owner = nullptr; // Owner of the component, using a raw pointer as their is no ownership
	void sendMessage(const ComponentMessage& msg);
public:
	virtual void onAttach(GameObject* owner) { m_owner = owner; };
	virtual void onDetach() { m_owner = nullptr; };
	virtual void onUpdate(float timestep) {};
	virtual void receiveMessage(const ComponentMessage& msg) = 0;
};


