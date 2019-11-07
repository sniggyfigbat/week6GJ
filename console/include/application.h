#pragma once

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <thread>
#include <mutex>
#include <chrono>

#include "layer.h"
#include "gameLayer.h"


class Application
{
private:
	std::thread m_keyPressThread;
	std::list<unsigned int> m_keyBuffer;
	std::mutex keyBufferMutex;
	static float s_frameTime;
	const float m_frameTime = 1.f / 60.f;
	
	std::chrono::high_resolution_clock::time_point m_frameStart;
	std::chrono::high_resolution_clock::time_point m_frameEnd;

	bool m_running = true;

	std::shared_ptr<Layer> m_gameLayer;


public:
	void init();
	void run();
	inline static float getFrameTime() { return s_frameTime; }
	inline bool isRunning() { return m_running; }
	bool onKeyPress(unsigned int keyCode);
};