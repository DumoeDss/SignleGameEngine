#include "main.h"
#include <stdio.h>
#include "gameEngine.h"
#include "game.h"
#include "menu.h"
#include "level.h"
#include "resource.h"

#pragma comment(lib, "winmm.lib")

HWND g_hwnd = 0;
HINSTANCE g_hInstance = 0;

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	}

	return DefWindowProc(hWnd,msg,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE h,
				HINSTANCE p,
				LPTSTR cmd,
				int show)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = MsgProc;
	wc.lpszMenuName = 0;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(h, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.hIcon = LoadIcon(h, MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = LoadIcon(h, MAKEINTRESOURCE(IDI_ICON1));
	wc.hInstance = h;
	wc.lpszClassName = WINDOW_CLASS;

	RegisterClassEx(&wc);

	if(FULLSCREEN)
	{
		g_hwnd = CreateWindowEx(NULL,WINDOW_CLASS,WINDOW_TITLE,
			WS_POPUP|WS_SYSMENU|WS_VISIBLE,
			NULL,NULL,WIN_WIDTH,WIN_HEIGHT,NULL,NULL,h,NULL);
	}
	else
	{
		g_hwnd = CreateWindowEx(NULL,WINDOW_CLASS,WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW|WS_VISIBLE,
			NULL,NULL,WIN_WIDTH,WIN_HEIGHT,NULL,NULL,h,NULL);
	}

	if(g_hwnd)
	{
		ShowWindow(g_hwnd,SW_SHOWDEFAULT);
		UpdateWindow(g_hwnd);
	}

	g_hInstance = wc.hInstance;

	if(InitializeEngine())
	{
		if(GameInitialize())
		{
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));

			while(msg.message != WM_QUIT)
			{
				if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					GameLoop();
				}
			}
		}
	}

	GameShutdown();
	ShutdownEngine();

	UnregisterClass(WINDOW_CLASS,h);
}