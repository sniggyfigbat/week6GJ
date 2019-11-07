#pragma once

#include <Box2D/Box2D.h>
#include <glm/glm.hpp>
#include "gameObject.h"
#include "gameLayer.h"
class Collidable : public GameObject
{
protected:
	b2Body * m_body;
public:
	void createStatic(glm::vec2 position, glm::vec2 size);
	//void createDynamic();
	void onKeyPress(int keyPress) {};
	void onUpdate(float timestep) {};
	void onDelete() {};
};

void Collidable::createStatic(glm::vec2 position, glm::vec2 size)
{
	b2BodyDef bd;
	bd.type = b2_staticBody;
	bd.position.Set(position.x, position.y); 
	bd.angle = 0;
	m_body = GameLayer::world()->CreateBody(&bd);
}