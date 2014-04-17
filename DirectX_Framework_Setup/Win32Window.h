#pragma once

// only include necessary stuff from window.h
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
using std::string;


class Win32Window
{
public:
	Win32Window(HINSTANCE instanceHandle, string ApplicationTitle, string WindowClassName, int Width, int Height);

	// the implementation to Run() in this class hundles the current windows message and returns it
	virtual MSG Run();
	// initializes the app's Win32 window
	virtual bool Initialize();


protected:
	//WIN32 Attributes
	HWND			m_WindowHandle;		// handle code to the app window
	HINSTANCE		m_InstanceHandle;	// handle code to the app instance
	UINT			m_ClientWidth;		// window width minus borders & title
	UINT			m_ClientHeight;		// window height minus borders & title
	string			m_ApplicationTitle;	// title displayed at the title bar
	string			m_WindowClassName;	// the name of the window's WindowClass
	DWORD			m_WindowStyle;		// window style [ DWORD == unassigned long ]


private:
	bool InitWindowClass();
	bool InitWindow();
};

