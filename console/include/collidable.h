#pragma once

#include <Box2D/Box2D.h>
#include <glm/glm.hpp>
#include "gameObject.h"
#include "gameLayer.h"
class Collidable : public Drawable
{
protected:
	b2Body * m_body;
public:
	void createStatic(glm::vec2 position, glm::vec2 size, int count, char * texture);
	void createDynamic(glm::vec2 position, glm::vec2 size, int count, char * texture);
	void onKeyPress(int keyPress) {};
	void onUpdate(float timestep) {};
	void onDelete() {};
};

void Collidable::createStatic(glm::vec2 position, glm::vec2 size, int count, char * texture)
{
	m_animatedMat.setPosition(view(position));
	m_animatedMat.setSize(view(size));
	m_animatedMat.setCount(count);
	m_animatedMat.setData(texture);

	m_currentFrame = 0;
	m_numFrames = 0;

	b2BodyDef bd;
	bd.type = b2_staticBody;
	bd.position.Set(position.x, position.y); 
	bd.angle = 0;

	b2PolygonShape boxShape;
	boxShape.SetAsBox(size.x, size.y);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	m_body->CreateFixture(&boxFixtureDef);

	m_body = GameLayer::world()->CreateBody(&bd);
}

void Collidable::createDynamic(glm::vec2 position, glm::vec2 size, int count, char * texture)
{
	m_animatedMat.setPosition(view(position));
	m_animatedMat.setSize(view(size));
	m_animatedMat.setCount(count);
	m_animatedMat.setData(texture);

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(position.x, position.y);
	bd.angle = 0;

	b2PolygonShape boxShape;
	boxShape.SetAsBox(size.x, size.y);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	m_body->CreateFixture(&boxFixtureDef);

	m_body = GameLayer::world()->CreateBody(&bd);
}