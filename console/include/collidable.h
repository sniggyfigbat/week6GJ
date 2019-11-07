#pragma once

#include "drawable.h"
#include <Box2D/Box2D.h>


class Collidable : public Drawable
{
protected:
	b2Body * m_body;
public:
	void createStatic(b2World* w,glm::vec2 position, glm::vec2 size, int count, char * texture);
	void createDynamic(b2World* w, glm::vec2 position, glm::vec2 size, int count, char * texture);
	void onKeyPress(int keyPress) {};
	void onUpdate(float timestep);
	void onDelete() {};
};


