#pragma once

// only include necessary stuff from window.h
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
using std::string;

class Win32Window
{
public:
	Win32Window(HINSTANCE instanceHandle, string ApplicationTitle, string WindowClassName);

	virtual MSG Run();
	virtual bool Initialize();


protected:
	//WIN32 Attributes
	HWND			m_WindowHandle;		// handle to the app window
	HINSTANCE		m_InstanceHandle;	// handle to the app instance
	UINT			m_ClientWidth;		// draw space width, not window width
	UINT			m_ClientHeight;		// same
	string			m_ApplicationTitle;	// title displayed at the title bar
	string			m_WindowClassName;	// the name of the window's window class
	DWORD			m_WindowStyle;		// window style [ DWORD == unassigned long ]


private:
	bool InitWindowClass();
	bool InitWindow();
};

