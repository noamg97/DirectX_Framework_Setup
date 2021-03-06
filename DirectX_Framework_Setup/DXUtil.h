#pragma once
#include <d3d11.h>
#include <DirectXColors.h>
#include "dxerr.h"

#pragma comment(lib, "d3d11.lib")

// macro wrapper for the dxerr.h functions that shows a messagebox when an error occurs in a function that returns an HRESULT, and is wrapped by "HR(...)"
#ifdef _DEBUG
#ifndef HR
#define HR(x) { HRESULT hr = x; if(FAILED(hr)) DXTraceW(__FILEW__, __LINE__, hr, L#x, true); }
#endif
#endif
#ifndef _DEBUG
#ifndef HR
#define HR(x) x
#endif
#endif


namespace Memory
{
	template<class T> void SafeDelete(T& t)
	{
		if(t)
		{
			delete t;
			t = nullptr;
		}
	}

	template<class T> void SafeDeleteArray(T& t)
	{
		if(t)
		{
			delete[] t;
			t = nullptr;
		}
	}

	template<class T> void SafeRelease(T& t)
	{
		if(t)
		{
			t->Release();
			t = nullptr;
		}
	}
}

namespace Time
{
	// a GameTime object that contains all the time related data that should be passed to the Update & Draw methods
	struct GameTime
	{
	public: 
		// all milliseconds
		double TotalGameTime;
		double ElapsedTime;

		GameTime()
		{
			this->TotalGameTime = 0;
			this->ElapsedTime = 0;
		}

		GameTime(double TotalGameTime, double ElapsedTime)
		{
			this->TotalGameTime = TotalGameTime;
			this->ElapsedTime = ElapsedTime;
		}
	};
}

struct GameInfo
{
	int FramesPerSecond;
	bool StartAtFullScreen;
	int ResolutionWidth, ResolutionHeight;
	string Name;

	GameInfo(
		string Name,
		int FramesPerSecond = 60,
		int ResolutionWidth = 800,
		int ResolutionHeight = 600,
		bool StartAtFullScreen = false)
	{
		this->FramesPerSecond = FramesPerSecond;
		this->StartAtFullScreen = StartAtFullScreen;
		this->ResolutionWidth = ResolutionWidth;
		this->ResolutionHeight = ResolutionHeight;
		this->Name = Name;
	}
};