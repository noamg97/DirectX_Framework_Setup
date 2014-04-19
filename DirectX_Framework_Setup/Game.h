#pragma once
#include "DirectXWindow.h"

class Game : public DirectXWindow
{
public:
	//Ctor & Dtor
	Game(HINSTANCE instanceHandle);
	~Game(void);


	void Update(GameTime gameTime) override;
	void Draw(GameTime gameTime) override;
};