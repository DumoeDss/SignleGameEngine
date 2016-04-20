#pragma once

bool InitializeMainMenu();
void MainMenuRender();
void MainMenuCallback(int id, int state);

enum GAME_GUI {	// GUI�б�
	GAME_MAIN_MENU_SCREEN = 0,	// ���˵�
	GAME_START_SCREEN,	// ��ʼ��Ϸ
	GAME_LOAD_SCREEN,	// ��ȡ��Ϸ
	GAME_CREDITS_SCREEN,	// ������Ϣ
	GAME_LOADING_SCREEN,	// �������
	GAME_GUI,	// ��Ϸ����GUI
};

enum GUI_CONTROLS {	// �ؼ�ID
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
