#pragma once
#include <d3d11.h>
#include <DirectXColors.h>
#include "dxerr.h"

#pragma comment(lib, "d3d11.lib")

// macro wrapper for the dxerr.h functions that shows a messagebox when an error has occured in a function that returns HRESULT and is wrapped by "HR(...)"
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