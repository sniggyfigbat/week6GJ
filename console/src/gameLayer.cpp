#include "gameLayer.h"


GameLayer::GameLayer()
{
	world = new b2World(b2Vec2(0.f, -9.81f));

	m_renderer.setClearChar(' ');
	m_camera = Camera(0,0,120,30);

	m_renderComponents.resize(5);
	m_renderComponents[0] = RenderComponent((char*)"XXXXXXXOXXXXXXX", 15, 5, 3, -2, 8);
	m_renderComponents[1] = RenderComponent((char*)"XXXXXXXOXXXXXXX", 15, 5, 3, 30, -1);
	m_renderComponents[2] = RenderComponent((char*)"XXXXXXXOXXXXXXX", 15, 5, 3, 30, 10);
	m_renderComponents[3] = RenderComponent((char*)"XXXXXXXOXXXXXXX", 15, 5, 3, 30, 29);
	m_renderComponents[4] = RenderComponent((char*)"XXXXXXXOXXXXXXX", 15, 5, 3, 119, 10);

	// Clearly this needs to be read from a file
	m_gameObjects.resize(5);
	int i = 0;
	for(auto& CGO : m_gameObjects)
	{
		CGO.addComponent(std::shared_ptr<Component>(&m_renderComponents[i]));
		i++;
	}

	m_gameObjects[2].addComponent(std::shared_ptr<Component>(&m_KBCtrlComponent));
}

void GameLayer::onUpdate(float timestep)
{
	// Render everything
	m_renderer.beginScene(m_camera);

	for (auto renderComp : m_renderComponents)
	{
		m_renderer.submit(renderComp.getMaterial());
	}

	m_renderer.endScene();
	m_renderer.flush();
}

bool GameLayer::onKeyPress(unsigned int keyCode)
{
	m_lastKeypress = keyCode;
	ComponentMessage msg(ComponentMessageType::KeyPressed, (void*)&keyCode);
	m_KBCtrlComponent.receiveMessage(msg);
	return false;
}
