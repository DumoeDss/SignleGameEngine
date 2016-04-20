#pragma once
#include "gameEngine.h"

#define MISSION_COMPLETE	1
#define MISSION_FAIL		2
#define MISSION_ONGOING		3

#define X_MESH			1
#define X_ANIMATED_MESH	2

bool GameInitialize();
void GameLoop();
void GameProcessInput();
void GameShutdown();
void GameReleaseAll();

struct stGameObject
{
	stGameObject():m_type(0),m_id(0),m_x(0),m_y(0),m_z(0),
		m_rotX(0),m_rotY(0),m_rotZ(0),m_visible(1){}

	int m_type;
	int m_id;
	float m_x, m_y, m_z;
	float m_rotX, m_rotY, m_rotZ;

	int m_visible;

	MyMatrix4x4 worldMat;
};

struct stGameWorld
{
	stGameWorld()
	{
		m_levelID = m_skyBoxID = -1;
		m_models = 0; m_totalModels = 0;
		m_artifacts = 0; m_totalArtifacts = 0;
		m_artifactsCollected = 0;
		m_totalTime = m_startTime = m_currentTime = 0;
		m_numArtifactsCollected = 0;
		m_levelStartTime = 0;

		m_characters = 0;
		m_characterSpot = 0;
		m_totalCharacters = 0;
		m_spottedCount = 0;
		g_totalEnemiesKilled = 0;

		m_missionStatus = MISSION_ONGOING;
	}

	void Shutdown()
	{
		m_levelID = m_skyBoxID = -1;
		if(m_models) delete[] m_models;
		m_models = 0; 
		m_totalModels = 0;

		if(m_artifacts) delete[] m_artifacts;
		m_artifacts = 0; 
		m_totalArtifacts = 0;

		if(m_artifactsCollected) delete[] m_artifactsCollected;
		m_artifactsCollected = 0;
		
		m_totalTime = m_startTime = m_currentTime = 0;
		m_numArtifactsCollected = 0;
		m_levelStartTime = 0;

		if(m_characters) delete[] m_characters;
		m_characters = 0;
		m_totalCharacters = 0;
		if(m_characterSpot) delete[] m_characterSpot;
		m_characterSpot = 0;
		
		m_spottedCount = 0;
		g_totalEnemiesKilled = 0;

		m_missionStatus = MISSION_ONGOING;
	}

	int m_levelID;
	int m_skyBoxID;

	stGameObject *m_models;
	int m_totalModels;

	stGameObject *m_artifacts;
	int *m_artifactsCollected;
	int m_totalArtifacts;
	int m_numArtifactsCollected;

	stGameObject *m_characters;
	int *m_characterSpot;
	int m_totalCharacters;
	int m_spottedCount;

	float m_totalTime;
	float m_startTime;
	float m_currentTime;
	float m_levelStartTime;

	int m_missionStatus;

	int g_totalEnemiesKilled;
};

enum GAME_STATE { 
	GS_MENU = 1,
	GS_LEVEL, 
	GS_LEVEL_1_SWITCH,
	GS_LEVEL_2_SWITCH,
	GS_LEVEL_3_SWITCH,
	GS_LEVEL_4_SWITCH
};

extern bool g_LMBDown;
extern int g_mouseX;
extern int g_mouseY;

extern stGameWorld g_gameWorld;
extern GAME_STATE g_gameState;

extern MyCamera g_camera;

extern MyRay g_viewRay;
extern int g_shotSound;
