#pragma once
#include "DXUtil.h"

using namespace Time;
using namespace FrameworkObjects;

class Game
{
public:
	//Ctor & Dtor
	Game();
	~Game(void);

	void Update(GameTime gameTime);
	void Draw(GameTime gameTime);
};

