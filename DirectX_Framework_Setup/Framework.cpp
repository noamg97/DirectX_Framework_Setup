#include "Framework.h"


Framework::Framework(HINSTANCE instanceHandle, Game* game) : DirectXWindow(instanceHandle)
{
	m_pGame = game;
}



bool Framework::Initialize()
{
	using namespace FrameworkObjects;

	if(DirectXWindow::Initialize())
	{
		Device = m_pDevice;
		ImmediateContext = m_pImmediateContext;
		SwapChain = m_pSwapChain;
		RenderTargetView = m_pRenderTargetView;
		GpuDriverType = m_DriverType;
		FeatureLevel = m_FeatureLevel;
		ViewPort = m_ViewPort;


		return true;
	}
	return false;
}

MSG Framework::Run()
{
	StartTimeCounter();
	MSG msg = DirectXWindow::Run();


	// main loop method. Run the application as long as there isn't a Quit message	
	while(msg.message != WM_QUIT)
	{
		// get the current message and process it. Not blocking - returns null for no message
		msg = DirectXWindow::Run();

		// get the time past from the last loop run, and create a GameTime object to pass to the functions
		double elapsed = GetElapsedTime();
		Time::GameTime gameTime(TimeUntilLastFrame + elapsed, elapsed);

		// lock fps
		if(elapsed > 1000.0 / 60.0)
		{
			//  call our game's realtime update and draw methods (similar to XNA)
			m_pGame->Update(gameTime);
			m_pGame->Draw(gameTime);


			// set the time until last frame to the current time
			TimeUntilLastFrame += GetElapsedTime();
		}
	}

	// return the quit message
	return msg;
}



void Framework::StartTimeCounter()
{
	LARGE_INTEGER li;

	// get the frequency (ticks per second) and set it in milliseconds to the variable
	QueryPerformanceFrequency(&li);
	Frequency = double(li.QuadPart) / 1000.0;


	// get the current ticks and set the LastFrameTicks
	QueryPerformanceCounter(&li);
	TimeUntilLastFrame = (double)li.QuadPart / Frequency;
}

double Framework::GetElapsedTime()
{
	LARGE_INTEGER li;

	QueryPerformanceCounter(&li);
	return (double(li.QuadPart) / Frequency) - TimeUntilLastFrame;
}



Framework::~Framework(void)
{
	Memory::SafeDelete(m_pGame);
}