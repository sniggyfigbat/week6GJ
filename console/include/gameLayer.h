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
#include "terrain.h"

class GameLayer : public Layer
{
private:
	static b2World* m_world;
	ConsoleRenderer m_renderer;
	Camera m_camera;
	std::vector<Label> m_labels;
	int m_lastKeypress;

	Terrain * m_terrain;

	Drawable m_animation;
public:
	GameLayer();
	void onUpdate(float timestep) override;
	bool onKeyPress(unsigned int keyCode) override;
	static b2World* world() { return m_world; }

};