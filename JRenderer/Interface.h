#pragma once
#include <Windows.h>
#include "Interface.h"

namespace JRenderer
{
	extern const unsigned int WINDOW_WIDTH;
	extern const unsigned int WINDOW_HEIGHT;

	HRESULT Initialise(HWND hInst);
}