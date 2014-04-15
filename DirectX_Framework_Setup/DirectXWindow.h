#pragma once
#include "Win32Window.h"
#include "DXUtil.h"

class DirectXWindow : public Win32Window
{
public:
	DirectXWindow(HINSTANCE instanceHandle);
	~DirectXWindow(void);

protected:
	bool Initialize() override;

	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pImmediateContext;
	IDXGISwapChain*			m_pSwapChain;
	ID3D11RenderTargetView*	m_pRenderTargetView;
	D3D_DRIVER_TYPE			m_DriverType;
	D3D_FEATURE_LEVEL		m_FeatureLevel;
	D3D11_VIEWPORT			m_ViewPort;

private:
	bool InitializeDirect3D(bool isFullScreen);
	bool InitializeSwapChainAndDevice(bool isFullScreen);
};

