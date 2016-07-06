#include "gameEngine.h"

#pragma comment(lib, "../debug/GameEngine.lib")
//渲染引擎对象
MyD3DRender *g_Render = NULL;
//输入引擎对象
MyInputInterface *g_InputSystem = NULL;
MyLogSystem *g_gameLog;
//字体ID
int g_arialID = -1;
int g_arial24ID = -1;
int g_arial36ID = -1;
int g_fontID = -1;
int g_mainGui = -1;

//初始化引擎
bool InitEngine(int width, int height, HWND hwnd,HINSTANCE hinstance, bool fullScreen, MultiSampleType msType)
{
	//创建并初始化渲染引擎
	if(!CreateD3DRender(&g_Render)) 
		return false;
	if(!g_Render->InitRender(width, height, hwnd, fullScreen, msType))
		return false;
	g_gameLog = new MyLogSystem("GameLog.log");
	g_gameLog->AppendLog("创建并初始化渲染引擎成功.");
	g_Render->SetClearCol(0,0,0);
	g_Render->CalculateProjMatrix(PI/4,0.1f,50000.0f);
	//创建字体
	if (!g_Render->CreateText("Calibri", 0, false, 40, g_fontID))
		return false;
	if(!g_Render->CreateText("Arial",0,true,18,g_arialID)) 
		return false;
	if(!g_Render->CreateText("Arial",0,false,24,g_arial24ID)) 
		return false;
	if(!g_Render->CreateText("Arial",0,false,36,g_arial36ID)) 
		return false;
	//创建并初始化输入引擎
	if(!CreateInput(&g_InputSystem, hwnd,hinstance,false))
		return false;
	if(!g_InputSystem->InitInput())
		return false;
	g_gameLog->AppendLog("创建并初始化输入引擎成功.");
	return true;
}

void ShutdownEngine()
{
	if(g_Render)
	{
		g_Render->Shutdown();
		delete g_Render;
		g_Render = 0;
	}
	if(g_InputSystem)
	{
		g_InputSystem->Shutdown();
		delete g_InputSystem;
		g_InputSystem = 0;
	}
	g_gameLog->AppendLog("关闭引擎.");
	delete g_gameLog;
	g_gameLog = 0;
}