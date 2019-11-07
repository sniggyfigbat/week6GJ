#pragma once

//#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <memory>
#include <vector>
#include "layer.h"
#include "consoleRenderer.h"
#include "label.h"
#include "camera.h"
#include "drawable.h"
#include "collidable.h"

class GameLayer : public Layer
{
private:
	b2World* m_world;
	ConsoleRenderer m_renderer;
	Camera m_camera;
	std::vector<Label> m_labels;
	int m_lastKeypress;

	Drawable m_animation;

	Collidable m_staticBox;
	Collidable m_dynamicBox;
public:
	GameLayer();
	void onUpdate(float timestep) override;
	bool onKeyPress(unsigned int keyCode) override;

};