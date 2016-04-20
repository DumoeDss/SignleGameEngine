
#include "menu.h"
#include "gameEngine.h"
#include "game.h"
#include "main.h"

int g_mainGui = -1;
int g_startGui = -1;
int g_creditsGui = -1;
int g_loadingGui = -1;
int g_currentGUI = GAME_MAIN_MENU_SCREEN;

int g_menuSound = -1;

bool InitializeMainMenu()
{
	if(!g_Render->CreateGUI(g_mainGui)) return false;
	if(!g_Render->CreateGUI(g_startGui)) return false;
	if(!g_Render->CreateGUI(g_creditsGui)) return false;
	if(!g_Render->CreateGUI(g_loadingGui)) return false;

	if(!g_Render->AddGUIBackdrop(g_mainGui,"GameMedia/maingui.jpg"))
		return false;
	if(!g_Render->AddGUIBackdrop(g_startGui,"GameMedia/startgui.jpg"))
		return false;
	if(!g_Render->AddGUIBackdrop(g_creditsGui,"GameMedia/optiongui.jpg"))
		return false;
	if(!g_Render->AddGUIBackdrop(g_loadingGui,"GameMedia/loadgui.jpg"))
		return false;

	if(!g_Render->AddGUIButton(g_mainGui,BUTTON_START_ID,
		1150, 500, "GameMedia/start_up.png",
		"GameMedia/start_over.png", "GameMedia/start_down.png")) return false;
	if (!g_Render->AddGUIButton(g_mainGui, BUTTON_LOAD_ID, 
		1150, 545, "GameMedia/load_up.png",
		"GameMedia/load_over.png", "GameMedia/load_down.png")) return false;
	if(!g_Render->AddGUIButton(g_mainGui,BUTTON_CREDITS_ID,
		1150, 590, "GameMedia/credits_up.png",
		"GameMedia/credits_over.png", "GameMedia/credits_down.png")) return false;
	if(!g_Render->AddGUIButton(g_mainGui,BUTTON_QUIT_ID,
		1150, 635, "GameMedia/quit_up.png",
		"GameMedia/quit_over.png", "GameMedia/quit_down.png")) return false;

	if(!g_Render->AddGUIButton(g_startGui,BUTTON_LEVEL_1_ID,
		860, 335, "GameMedia/level1_up.png", "GameMedia/level1_over.png",
		"GameMedia/level1_down.png")) return false;
	if (!g_Render->AddGUIButton(g_startGui, BUTTON_LEVEL_2_ID,
		464, 460, "GameMedia/level2_up.png", "GameMedia/level2_over.png",
		"GameMedia/level2_down.png")) return false;
	if (!g_Render->AddGUIButton(g_startGui, BUTTON_LEVEL_3_ID,
		164, 290, "GameMedia/level3_up.png", "GameMedia/level3_over.png",
		"GameMedia/level3_down.png")) return false;
	if (!g_Render->AddGUIButton(g_startGui, BUTTON_LEVEL_4_ID,
		588, 192, "GameMedia/level4_up.png", "GameMedia/level4_over.png",
		"GameMedia/level4_down.png")) return false;

	if(!g_Render->AddGUIButton(g_startGui,BUTTON_BACK_ID,
		1250, 700, "GameMedia/back_up.png", "GameMedia/back_over.png",
		"GameMedia/back_down.png")) return false;

	

	if(!g_Render->AddGUIButton(g_creditsGui,BUTTON_BACK_ID,
		1250, 700, "GameMedia/back_up.png", "GameMedia/back_over.png",
		"GameMedia/back_down.png")) return false;

	return true;
}

void MainMenuCallback(int id, int state)
{
	switch(id)
	{
	case BUTTON_START_ID:
		if(state == MOUSE_BUTTON_DOWN)
			g_currentGUI = GAME_START_SCREEN;
		break;
	case BUTTON_CREDITS_ID:
		if(state == MOUSE_BUTTON_DOWN)
			g_currentGUI = GAME_CREDITS_SCREEN;
		break;
	case BUTTON_LEVEL_1_ID:
		if(state == MOUSE_BUTTON_DOWN)
		{
			g_currentGUI = GAME_LOADING_SCREEN;
			g_gameState = GS_LEVEL_1_SWITCH;
		}
		break;
	case BUTTON_LEVEL_2_ID:
		if (state == MOUSE_BUTTON_DOWN)
		{
			g_currentGUI = GAME_LOADING_SCREEN;
			g_gameState = GS_LEVEL_2_SWITCH;
		}
		break;
	case BUTTON_LEVEL_3_ID:
		if (state == MOUSE_BUTTON_DOWN)
		{
			g_currentGUI = GAME_LOADING_SCREEN;
			g_gameState = GS_LEVEL_3_SWITCH;
		}
		break;
	case BUTTON_LEVEL_4_ID:
		if (state == MOUSE_BUTTON_DOWN)
		{
			g_currentGUI = GAME_LOADING_SCREEN;
			g_gameState = GS_LEVEL_4_SWITCH;
		}
		break;
	case BUTTON_BACK_ID:
		if(state == MOUSE_BUTTON_DOWN)
			g_currentGUI = GAME_MAIN_MENU_SCREEN;
		break;
	case BUTTON_QUIT_ID:
		if(state == MOUSE_BUTTON_DOWN)
		{
			GameReleaseAll();
			PostQuitMessage(0);
		}
		break;
	}
}

void MainMenuRender()
{
	if(!g_Render) return;

	g_Render->StartRender(1,1,0);

	if(g_currentGUI == GAME_MAIN_MENU_SCREEN)
		g_Render->ProcessGUI(g_mainGui,g_LMBDown,g_mouseX,g_mouseY,MainMenuCallback);
	else if(g_currentGUI == GAME_START_SCREEN)
		g_Render->ProcessGUI(g_startGui,g_LMBDown,g_mouseX,g_mouseY,MainMenuCallback);
	else if(g_currentGUI == GAME_CREDITS_SCREEN)
		g_Render->ProcessGUI(g_creditsGui,g_LMBDown,g_mouseX,g_mouseY,MainMenuCallback);
	else if(g_currentGUI == GAME_LOADING_SCREEN)
		g_Render->ProcessGUI(g_loadingGui,g_LMBDown,g_mouseX,g_mouseY,MainMenuCallback);

	g_Render->EndRendering();
}
