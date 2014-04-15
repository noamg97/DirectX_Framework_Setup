#pragma once
#include "DirectXWindow.h"

class Game : DirectXWindow
{
public:
	//Ctor & Dtor
	Game(HINSTANCE instanceHandle);
	~Game(void);

	// initializer
	bool Initialize() override;
	// main loop method
	MSG Run() override;
	// update method, called from Run()
	void Update(double deltaTime) override;
	// draw method, called from Run()
	void Draw(double deltaTime) override;
};

