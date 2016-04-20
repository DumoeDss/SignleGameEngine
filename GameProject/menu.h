#pragma once

bool InitializeMainMenu();
void MainMenuRender();
void MainMenuCallback(int id, int state);

enum GAME_GUI {	// GUI列表
	GAME_MAIN_MENU_SCREEN = 0,	// 主菜单
	GAME_START_SCREEN,	// 开始游戏
	GAME_LOAD_SCREEN,	// 读取游戏
	GAME_CREDITS_SCREEN,	// 制作信息
	GAME_LOADING_SCREEN,	// 载入界面
	GAME_GUI,	// 游戏内置GUI
};

enum GUI_CONTROLS {	// 控件ID
	STATIC_TEXT_ID = 1,
	BUTTON_START_ID,
	BUTTON_LOAD_ID,
	BUTTON_CREDITS_ID,
	BUTTON_QUIT_ID,
	BUTTON_BACK_ID,
	BUTTON_LEVEL_1_ID,
	BUTTON_LEVEL_2_ID,
	BUTTON_LEVEL_3_ID,
	BUTTON_LEVEL_4_ID
};

extern int g_mainGui;
extern int g_startGui;
extern int g_creditsGui;
extern int g_loadingGui;
extern int g_currentGUI;

extern int g_menuSound;
