#include "gameLayer.h"


GameLayer::GameLayer()
{
	world = new b2World(b2Vec2(0.f, -9.81f));

	m_renderer.setClearChar(' ');
	m_camera = Camera(0,0,120,30);

}

void GameLayer::onUpdate(float timestep)
{
	// Render everything
	m_renderer.beginScene(m_camera);

	/*for (auto renderComp : m_renderComponents)
	{
		m_renderer.submit(renderComp.getMaterial());
	}*/

	m_renderer.endScene();
	m_renderer.flush();
}

bool GameLayer::onKeyPress(unsigned int keyCode)
{
	return false;
}
