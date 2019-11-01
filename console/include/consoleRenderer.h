#pragma once

#include <stdlib.h>
#include <string>
#include <glm/glm.hpp>

#include "components/renderComponent.h"
#include "camera.h"

class ConsoleRenderer
{
private:
	static int const m_consoleWidth = 120;
	static int const m_consoleHeight = 30;
	static int const m_frameBufferSize = m_consoleWidth * m_consoleHeight;
	char m_frameBuffer[m_frameBufferSize];
	char m_clearChar = ' ';
	Camera m_camera;
public:
	void beginScene(const Camera& camera);
	void submit(const ConsoleMaterial& mat);
	void endScene();
	void flush();
	void setClearChar(char ch);
};