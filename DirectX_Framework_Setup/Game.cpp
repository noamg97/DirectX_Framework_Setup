#include "Game.h"


Game::Game(HINSTANCE instanceHandle) : DirectXWindow(instanceHandle)
{
}



bool Game::Initialize()
{
	if(DirectXWindow::Initialize())
	{
		// Load Content And Stuff



		return true;
	}
	return false;
}

MSG Game::Run()
{
	MSG msg = DirectXWindow::Run();

	// main loop method. Run the application as long as there isn't a Quit message	
	while(msg.message != WM_QUIT)
	{
		// get the current message and process it. Not blocking - returns null for no message
		msg = DirectXWindow::Run();

		// call the realtime framework methods (similar to XNA)
		Update(0.0);
		Draw(0.0);
	}

	// return the quit message
	return msg;
}



void Game::Update(double deltaTime)
{
}

void Game::Draw(double deltaTime)
{
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::CornflowerBlue);


	HR(m_pSwapChain->Present(0,0));
}



Game::~Game(void)
{
}