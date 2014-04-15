#pragma once
#include "DirectXWindow.h"
#include "Game.h"

class Framework : DirectXWindow
{
public:
	Framework(HINSTANCE instanceHandle, Game* game);
	~Framework(void);
	bool Initialize() override;
	// main loop method
	MSG Run() override;

private:
	void StartTimeCounter();
	double GetElapsedTime();
private:
	Game* m_pGame;

	// time related:
	double Frequency;
	double TimeUntilLastFrame;
};