#include "Game.h"

// create a static variable containing the programmer's pre-defined game info, used to initialize the DirectX and the Win32Window
static GameInfo* gameInfo = new GameInfo(60, false, 800, 600, "DirectX Tryout");



Game::Game(HINSTANCE instanceHandle) : DirectXWindow(instanceHandle, gameInfo)
{
	// Load game content and initialize
}

Game::~Game(void)
{
	Memory::SafeDelete(gameInfo);
}




void Game::Update(GameTime gameTime)
{
	// Update game
}

void Game::Draw(GameTime gameTime)
{
	// clear the window to a certain color
	DirectXWindow::Clear(DirectX::Colors::CornflowerBlue);



	// Render game



	// switch the buffers, thus rendering to the screen what was just drawn in this function
	DirectXWindow::Present();
}
