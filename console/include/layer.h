#pragma once

class Layer
{
private:
public:
	virtual void onUpdate(float timestep) = 0;
	virtual bool onKeyPress(unsigned int keyCode) = 0;
};