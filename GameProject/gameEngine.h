#pragma once

#include "../GameEngine/GameEngine.h"

bool InitializeEngine();
void ShutdownEngine();

extern MyRenderInterface *g_Render;
extern MyInputInterface *g_InputSystem;

extern int g_arialID;
extern int g_arial24ID;
extern int g_arial36ID;
extern int g_fontID;
