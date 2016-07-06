#include "gameEngine.h"

#pragma comment(lib, "../debug/GameEngine.lib")
//��Ⱦ�������
MyD3DRender *g_Render = NULL;
//�����������
MyInputInterface *g_InputSystem = NULL;
MyLogSystem *g_gameLog;
//����ID
int g_arialID = -1;
int g_arial24ID = -1;
int g_arial36ID = -1;
int g_fontID = -1;
int g_mainGui = -1;

//��ʼ������
bool InitEngine(int width, int height, HWND hwnd,HINSTANCE hinstance, bool fullScreen, MultiSampleType msType)
{
	//��������ʼ����Ⱦ����
	if(!CreateD3DRender(&g_Render)) 
		return false;
	if(!g_Render->InitRender(width, height, hwnd, fullScreen, msType))
		return false;
	g_gameLog = new MyLogSystem("GameLog.log");
	g_gameLog->AppendLog("��������ʼ����Ⱦ����ɹ�.");
	g_Render->SetClearCol(0,0,0);
	g_Render->CalculateProjMatrix(PI/4,0.1f,50000.0f);
	//��������
	if (!g_Render->CreateText("Calibri", 0, false, 40, g_fontID))
		return false;
	if(!g_Render->CreateText("Arial",0,true,18,g_arialID)) 
		return false;
	if(!g_Render->CreateText("Arial",0,false,24,g_arial24ID)) 
		return false;
	if(!g_Render->CreateText("Arial",0,false,36,g_arial36ID)) 
		return false;
	//��������ʼ����������
	if(!CreateInput(&g_InputSystem, hwnd,hinstance,false))
		return false;
	if(!g_InputSystem->InitInput())
		return false;
	g_gameLog->AppendLog("��������ʼ����������ɹ�.");
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
	g_gameLog->AppendLog("�ر�����.");
	delete g_gameLog;
	g_gameLog = 0;
}