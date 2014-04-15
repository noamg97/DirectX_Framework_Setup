#include "Game.h"


Game::Game()
{
	// Load Content And Initialize
}


void Game::Update(GameTime gameTime)
{
}

void Game::Draw(GameTime gameTime)
{
	ImmediateContext->ClearRenderTargetView(RenderTargetView, DirectX::Colors::CornflowerBlue);


	HR(SwapChain->Present(0,0));
}


Game::~Game(void)
{
}