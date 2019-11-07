#pragma once

#include <Box2D/Box2D.h>
#include "drawable.h"

class Player : public Collidable
{
protected:
public:
	void onKeyPress(int keyPress) override
	{
		switch (keyPress)
		{
		case 237 :
			// Right
		{b2Vec2 vel = m_body->GetLinearVelocity();
		float desiredVel = 5;
		float velChange = desiredVel - vel.x;
		float impulse = m_body->GetMass() * velChange; //disregard time factor
		m_body->ApplyLinearImpulse(b2Vec2(impulse, 0), m_body->GetWorldCenter(), true); }
			break;
		case 235:
			// Left
		{b2Vec2 vel = m_body->GetLinearVelocity();
		float desiredVel = -5;
		float velChange = desiredVel - vel.x;
		float impulse = m_body->GetMass() * velChange; //disregard time factor
		m_body->ApplyLinearImpulse(b2Vec2(impulse, 0), m_body->GetWorldCenter(), true); }
			break;
		}
	}
};