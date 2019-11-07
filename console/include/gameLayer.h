#pragma once

//#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <memory>
#include <vector>
#include "layer.h"
#include "consoleRenderer.h"
#include "components/component.h"
#include "components/keyboardCtrlComponent.h"
#include "gameObject.h"
#include "camera.h"

class GameLayer : public Layer
{
private:
	b2World* world;
	ConsoleRenderer m_renderer;
	Camera m_camera;
	std::vector<GameObject> m_gameObjects;
	std::vector<RenderComponent> m_renderComponents;
	int m_lastKeypress;
	KeyboardCtrlComponent m_KBCtrlComponent;
public:
	GameLayer();
	void onUpdate(float timestep) override;
	bool onKeyPress(unsigned int keyCode) override;
};