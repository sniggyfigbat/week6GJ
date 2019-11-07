#pragma once



class GameObject
{
protected:
	char * m_texture;
	bool m_markedForDeletion = 0;
public:
	virtual void onKeyPress(int keyPress) = 0;
	virtual void onUpdate(float timestep) = 0;
	virtual void onDelete() = 0;
	void markForDeletion() { m_markedForDeletion = true; }
};
