
#include "gameEngine.h"
#include "main.h"

#pragma comment(lib, "../debug/GameEngine.lib")

MyRenderInterface *g_Render = NULL;
MyInputInterface *g_InputSystem = NULL;

int g_arialID = -1;
int g_arial24ID = -1;
int g_arial36ID = -1;
int g_fontID = -1;

bool InitializeEngine()
{
	if(!CreateD3DRenderer(&g_Render)) return false;

	if(!g_Render->Initialize(WIN_WIDTH,WIN_HEIGHT,g_hwnd,FULLSCREEN,UGP_MS_SAMPLES_4)) return false;

	g_Render->SetClearCol(0,0,0);

	g_Render->CalculateProjMatrix(PI/4,0.1f,10000.0f);

	if (!g_Render->CreateText("Î¢ÈíÑÅºÚ", 0, true, 18, g_fontID))
		return false;
	if(!g_Render->CreateText("Arial",0,true,18,g_arialID)) 
		return false;
	if(!g_Render->CreateText("Arial",0,false,24,g_arial24ID)) 
		return false;
	if(!g_Render->CreateText("Arial",0,false,36,g_arial36ID)) 
		return false;

	if(!CreateDIInput(&g_InputSystem,g_hwnd,g_hInstance,false))
		return false;

	if(!g_InputSystem->Initialize())
		return false;

	return true;
}

void ShutdownEngine()
{
	if(g_Render)
	{
		g_Render->Shutdown();
		delete g_Render;
		g_Render = NULL;
	}
	if(g_InputSystem)
	{
		g_InputSystem->Shutdown();
		delete g_InputSystem;
		g_InputSystem = NULL;
	}

}