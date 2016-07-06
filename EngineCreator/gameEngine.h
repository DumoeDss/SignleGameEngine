#pragma once

#include "../GameEngine/GameEngine.h"

bool InitEngine(int width, int height, HWND hwnd,HINSTANCE hinstance, bool fullScreen, MultiSampleType msType);
void ShutdownEngine();

extern MyD3DRender *g_Render;
extern MyInputInterface *g_InputSystem;
extern MyLogSystem *g_gameLog;

extern int g_arialID;
extern int g_arial24ID;
extern int g_arial36ID;
extern int g_fontID;
extern int g_mainGui;
