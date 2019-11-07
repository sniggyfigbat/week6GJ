﻿#include "gameLayer.h"

b2World* GameLayer::m_world = new b2World(b2Vec2(0.f, -9.81f));

GameLayer::GameLayer()
{
	m_renderer.setClearChar(' ');
	m_camera = Camera(0,0,120,30);

	m_labels.resize(2);

	char ch[15] = {
		'X','X','X','X','X',
		'X','X',char(206),'X','X',
		'X','X','X','X','X' };
		


	m_labels[0] = Label(glm::vec2(10.f, 5.f), GameObject::invView(5, 3), 15, ch);
	m_labels[1] = Label(glm::vec2(3.3f, 1.65f),  GameObject::invView(3,3), 15, "___===---");

	m_animation = Drawable(glm::vec2(10.f, 5.f), GameObject::invView(6,5), 30, "        ''  o_()_o  /\\   d  b ");

	m_animation.addFrame("        ''  o_()_o  /\\   d  b ");
	m_animation.addFrame("        ''  o_()_o  /\\   d  b ");
	//m_animation.addFrame("XXXXXXXXXX0XXXXX");
	//m_animation.addFrame("XXXXXXXXXXX0XXXX");
	//m_animation.addFrame("XXXXXXXXXXXX0XXX");
}

void GameLayer::onUpdate(float timestep)
{
	//Update everything

	m_animation.onUpdate(timestep);
	// Render everything
	m_renderer.beginScene(m_camera);

	for (auto label : m_labels)
	{
		m_renderer.submit(label.getMaterial());
	}

	m_renderer.submit(m_animation.getMaterial());

	m_renderer.endScene();
	m_renderer.flush();
}

bool GameLayer::onKeyPress(unsigned int keyCode)
{
	return false;
}
