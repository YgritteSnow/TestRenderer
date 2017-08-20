#include <Windows.h>
#include <iostream>
#include <tchar.h>

#include "Interface.h"

const TCHAR* WINDOW_NAME = _T("jj");
const TCHAR* WINDOW_CAPTION = _T("JRenderer - by jj");
unsigned int WINDOW_POS_X = 100;
unsigned int WINDOW_POS_Y = 100;
HWND g_hwnd = NULL;

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_PAINT:
		//SceneManager::GetInstance()->Render();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wp) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		//default:
			//InputEventHandlerManager::GetInstance()->HandleKeyEvent(wp, true);
		}
		break;
	case WM_LBUTTONDOWN:
		//InputEventHandlerManager::GetInstance()->HandleMouseEvent(true);
		break;
	case WM_LBUTTONUP:
		//InputEventHandlerManager::GetInstance()->HandleMouseEvent(false);
		break;
	case WM_MOUSEMOVE:
		//InputEventHandlerManager::GetInstance()->HandleMouseMoveEvent(LOWORD(lp), HIWORD(lp));
		break;
	}
	return DefWindowProc(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR lpCmdLine, int nCmdLine) {
	WNDCLASSEX myWnd = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		//CS_HREDRAW | CS_VREDRAW,
		WinProc,
		0, 0,
		hInst,
		NULL,
		NULL,
		NULL,
		NULL,
		WINDOW_NAME,
		NULL
	};
	if (FAILED(RegisterClassEx(&myWnd))) {
		return E_FAIL;
	};

	g_hwnd = CreateWindowEx(
		NULL,
		WINDOW_NAME,
		WINDOW_CAPTION,
		WS_OVERLAPPEDWINDOW,// WS_VISIBLE | WS_POPUP,
		WINDOW_POS_X, WINDOW_POS_Y,
		JRenderer::WINDOW_WIDTH, JRenderer::WINDOW_HEIGHT,
		NULL, NULL, hInst, NULL);
	if (g_hwnd == NULL) {
		return E_FAIL;
	}

	if (FAILED(ShowWindow(g_hwnd, SW_SHOWDEFAULT))) {
		return E_FAIL;
	}

	if (SUCCEEDED(JRenderer::Initialise(g_hwnd)))
	{
		// Ö÷Ñ­»·
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (true) {
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT) {
					break;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
			}
		}
	}

	UnregisterClass(WINDOW_NAME, myWnd.hInstance);

	return S_OK;
}
