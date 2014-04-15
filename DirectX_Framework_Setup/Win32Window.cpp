#include "Win32Window.h"

LRESULT CALLBACK MsgProc(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// a function that is being called by the OS everytime a message is sent. Must exist.
	switch (msg)
	{
	case WM_DESTROY: 
		// if the window is destroyed post a quit message that Run() will catch.
		PostQuitMessage(0); 
		return 0;
	default: 
		return DefWindowProc(windowHandle, msg, wParam, lParam);
	}
}



//Ctor
Win32Window::Win32Window(HINSTANCE instanceHandle, string ApplicationTitle, string WindowClassName)
{
	m_InstanceHandle = instanceHandle;
	m_WindowHandle = NULL;				// since we didn't create a window yet
	m_ClientWidth = 800;
	m_ClientHeight = 600;
	m_ApplicationTitle = ApplicationTitle;
	m_WindowClassName = WindowClassName;
	m_WindowStyle = WS_OVERLAPPEDWINDOW;
}


//Run
MSG Win32Window::Run()
{
	MSG msg = {0}; // set all to zero

	// PeekMessage() puts the current message in msg, and returns true if it's not null
	if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
	{
		// if there is a message we have to call these two functions.
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// return the current message, so we'd know when we should stop the app
	return msg;
}


//Initializers
bool Win32Window::Initialize()
{
	// create and register a window class, then continue if registered successfully
	if(InitWindowClass())
	{
		// create and register a window class, then continue if registered successfully
		if(InitWindow())
		{
			ShowWindow(m_WindowHandle, SW_SHOW);
			return true;
		}
	}
	return false;
}

bool Win32Window::InitWindowClass()
{
	// from microsoft MSDN: A window class is a set of attributes that the system uses as a template to create a window


	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

	// thing that don't really matter:
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW; // doesn't matter since we're using directx to draw

	// things that somewhat matter:
	windowClass.hInstance = m_InstanceHandle;
	windowClass.lpfnWndProc = MsgProc;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = m_WindowClassName.c_str();
	windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// try to register our window class. If fails to do sogoes inside the if.
	if(!RegisterClassEx(&windowClass))
	{
		OutputDebugString("\nFailed To Create Window Class\n\n");
		return false; // as the initialization failed
	}
	return true;
}

bool Win32Window::InitWindow()
{
	// get actual window size from the defined size + titlebar and borders
	RECT windowRect = {0, 0, m_ClientWidth, m_ClientHeight}; // {x0, y0, x1, y1}
	AdjustWindowRect(&windowRect, m_WindowStyle, false);

	// get the width and height from the adjusted rectangle
	UINT width = windowRect.right - windowRect.left;
	UINT height = windowRect.bottom - windowRect.top;

	// get the location of the window, in which it will be in the center of the screen
	UINT x = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
	UINT y = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;

	// create the window and set our window handle code.
	m_WindowHandle = CreateWindow(m_WindowClassName.c_str(), m_ApplicationTitle.c_str(), m_WindowStyle, 
		x, y, width, height, NULL, NULL, m_InstanceHandle, NULL);


	// if the window wasn't created
	if(!m_WindowHandle)
	{
		OutputDebugString("\nFailed To Create Window\n\n");
		return false;
	}

	return true;
}