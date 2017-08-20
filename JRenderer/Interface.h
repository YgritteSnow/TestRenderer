#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <d3dx11.h>

namespace JRenderer
{
	extern const unsigned int WINDOW_WIDTH;
	extern const unsigned int WINDOW_HEIGHT;

	HRESULT Initialize(HWND hInst);
	void Render();
	void CleanupDevice();
}