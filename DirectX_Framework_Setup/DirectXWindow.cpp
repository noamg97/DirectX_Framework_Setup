#include "DirectXWindow.h"

DirectXWindow::DirectXWindow(HINSTANCE instanceHandle) : Win32Window(instanceHandle, "DirectX TryOut", "DirectX TryOut")
{
	// null out all the pointers. see that on the previous line we initialized the base class.
	m_pDevice = nullptr;
	m_pImmediateContext= nullptr;
	m_pSwapChain= nullptr;
	m_pRenderTargetView= nullptr;
}


bool DirectXWindow::Initialize()
{
	// initialize the window (base class) and the direct3d stuff, and return false if something fails
	if(!Win32Window::Initialize() || !InitializeDirect3D(false))
		return false;

	return true;
}

bool DirectXWindow::InitializeDirect3D(bool isFullScreen)
{
	// initialize the swapChain and the graphic device. returns false if failed
	if(InitializeSwapChainAndDevice(isFullScreen))
	{
		// create the render target view
		ID3D11Texture2D* m_pBackBufferTexture = 0;
		HR(m_pSwapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_pBackBufferTexture)));
		HR(m_pDevice->CreateRenderTargetView(m_pBackBufferTexture, nullptr, &m_pRenderTargetView));

		Memory::SafeRelease(m_pBackBufferTexture);

		// bind the render target view
		m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr); // third var is for depth stencil


		// viewport creation
		m_ViewPort.Width = static_cast<float>(m_ClientWidth);
		m_ViewPort.Height = static_cast<float>(m_ClientHeight);
		m_ViewPort.TopLeftX = 0;
		m_ViewPort.TopLeftY = 0;
		m_ViewPort.MinDepth = 0.0f;
		m_ViewPort.MaxDepth = 1.0f;

		// bind viewport
		m_pImmediateContext->RSSetViewports(1, &m_ViewPort);
		return true;
	}
	return false;
}

bool DirectXWindow::InitializeSwapChainAndDevice(bool isFullScreen)
{
	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif


	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,	// graphic card. The one we want.
		D3D_DRIVER_TYPE_WARP,		// ...maybe emulator
		D3D_DRIVER_TYPE_REFERENCE,	// ...not sure what this is
	};
	UINT numDriverTypes = 3; // driverTypes.Length;

	D3D_FEATURE_LEVEL featuresLevels[] = {
		// the directx version. we want dx11
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
	};
	UINT numFeatureLevels = 4; // featuresLevels.Length;


	// initialize the swap chains settings
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferCount = 1; // double buffer
	swapDesc.BufferDesc.Width = m_ClientWidth;
	swapDesc.BufferDesc.Height = m_ClientHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;	// 60 frames
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;	// per second
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = m_WindowHandle;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Windowed = !isFullScreen;
	swapDesc.SampleDesc.Count = 1;	// can smooth the geometry but it's a hard process
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // alt-enter fullscreen



	HRESULT result;
	for (int i = 0; i < numDriverTypes; ++i)
	{
		result = D3D11CreateDeviceAndSwapChain(NULL, driverTypes[i], NULL, createDeviceFlags, 
			featuresLevels, numFeatureLevels, D3D11_SDK_VERSION, &swapDesc, &m_pSwapChain, &m_pDevice,
			&m_FeatureLevel, &m_pImmediateContext);

		if(SUCCEEDED(result))
		{
			m_DriverType = driverTypes[i];
			return true;
		}
	}

	if(FAILED(result))
	{
		OutputDebugString("\nFailed To Create Device And Swap Chain\n\n");
		return false;
	}
	return false;
}



DirectXWindow::~DirectXWindow(void)
{
	// cleanup
	if(m_pImmediateContext) m_pImmediateContext->ClearState();
	Memory::SafeRelease(m_pRenderTargetView);
	Memory::SafeRelease(m_pSwapChain);
	Memory::SafeRelease(m_pImmediateContext);
	Memory::SafeRelease(m_pDevice);
}
