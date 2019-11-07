#include "collidable.h"

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

	m_body = World::world->CreateBody(&bd);
}

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

	m_body = World::world->CreateBody(&bd);
}