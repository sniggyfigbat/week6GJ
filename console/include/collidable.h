#pragma once

#include "drawable.h"
#include "world.h"

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


