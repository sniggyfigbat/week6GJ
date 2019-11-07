#include "collidable.h"

void Collidable::createDynamic(b2World* w, glm::vec2 position, glm::vec2 size, int count, char * texture)
{
	m_animatedMat.setPosition(view(position));
	m_animatedMat.setSize(view(size));
	m_animatedMat.setCount(count);
	m_animatedMat.setData(texture);

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(position.x, position.y);
	bd.angle = 0;

	m_body = w->CreateBody(&bd);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(size.x, size.y);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	boxFixtureDef.restitution = 0.6f;
	m_body->CreateFixture(&boxFixtureDef);
}

void Collidable::onUpdate(float timestep)
{
	auto pos = m_body->GetPosition();
	m_animatedMat.setPosition(glm::ivec2(GameObject::view(pos.x, pos.y)));
}

void Collidable::createStatic(b2World* w, glm::vec2 position, glm::vec2 size, int count, char * texture)
{
	m_animatedMat.setPosition(view(position));
	m_animatedMat.setSize(view(size));
	m_animatedMat.setCount(count);
	m_animatedMat.setData(texture);

	m_currentFrame = 0;
	m_numFrames = 0;

	b2BodyDef bd;
	bd.type = b2_staticBody;
	bd.position.Set(position.x + size.x*0.5f, position.y + size.y*0.5f);
	bd.angle = 0;

	m_body = w->CreateBody(&bd);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(size.x*0.5f, size.y*0.5f);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	m_body->CreateFixture(&boxFixtureDef);
}