#pragma once
#include "Win32Window.h"
#include "DXUtil.h"

using namespace Time;

class DirectXWindow : public Win32Window
{
public:
	DirectXWindow(HINSTANCE instanceHandle, GameInfo* gameInfo);
	~DirectXWindow(void);
	bool Initialize() override;
	MSG Run() override;

protected:
	// Framework Methods
	virtual void Update(GameTime gameTime) = 0;
	virtual void Draw(GameTime gameTime) = 0;
	
	// Utility Methods
	void Present();
	void Clear(const FLOAT color[4]);
	
private:
	// initialize helpers:
	bool InitializeDirect3D(bool isFullScreen);
	bool InitializeSwapChainAndDevice(bool isFullScreen);

	// run helpers:
	void StartTimeCounter();
	double GetElapsedTime();
	double m_TicksToMilliseconds; // (ticks / milliseconds) ratio
	double m_TimeUntilCurrentFrameStarted; // counts the total time since StartTimeCounter() was called. Is set to the current time at the end of each frame.
	double m_TotalGameTime; // milliseconds
	// Game Info:
	GameInfo*				m_pGameInfo;

	// Direct3D variables:
	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pImmediateContext;
	IDXGISwapChain*			m_pSwapChain;
	ID3D11RenderTargetView*	m_pRenderTargetView;
	D3D_DRIVER_TYPE			m_DriverType;
	D3D_FEATURE_LEVEL		m_FeatureLevel;
	D3D11_VIEWPORT			m_ViewPort;

};