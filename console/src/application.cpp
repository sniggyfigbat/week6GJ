#include "application.h"



void Application::init()
{
	m_keyPressThread = std::thread(
	[this]()
	{
		while (m_running)
		{
			unsigned char ch1 = _getch();
			std::lock_guard<std::mutex> lock{ keyBufferMutex };
			unsigned char ch2 = _getch();
			int keycode = ch1 | ch2;
			m_keyBuffer.push_back(keycode);
		}
	}
	);

	m_gameLayer.reset(new GameLayer);
	m_frameStart = std::chrono::high_resolution_clock::now();
}

void Application::run()
{
	float m_timeElapsed = 0.f;
	while (m_running)
	{
		m_frameEnd = std::chrono::high_resolution_clock::now();
		m_timeElapsed = std::chrono::duration<float>(m_frameEnd - m_frameStart).count();

		if (m_timeElapsed > m_frameTime)
		{
			// Check for key presses
			{
				std::lock_guard<std::mutex> lock{ keyBufferMutex };
				while (m_keyBuffer.size() > 0)
				{
					unsigned int keyCode = m_keyBuffer.front();
					m_keyBuffer.pop_front();
					onKeyPress(keyCode);
					
				}
			}

			m_gameLayer->onUpdate(m_timeElapsed);

			// Reset timer
			m_frameStart = std::chrono::high_resolution_clock::now();
		}
	}
	m_keyPressThread.join();
}

bool Application::onKeyPress(unsigned int keyCode)
{
	if (keyCode == 27)
	{
		m_running = false;
		return true;
	}
	return m_gameLayer->onKeyPress(keyCode);
}
