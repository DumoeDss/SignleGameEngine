#include "game.h"
#include "menu.h"
#include "level.h"

bool g_LMBDown = false;
int g_mouseX = 0, g_mouseY = 0;
bool g_OverLevel = false;

stGameWorld g_gameWorld;
GAME_STATE g_gameState = GS_MENU;

MyCamera g_camera;
MyRay g_viewRay;
int g_shotSound = -1;

bool GameInitialize()
{
	if(!InitializeMainMenu()) return false;
}

void GameLoop()
{
	GameProcessInput();
	switch (g_gameState) {
	case GS_LEVEL:
		LevelRender();
		break;
	case GS_MENU:
		MainMenuRender();
		break;
	case GS_LEVEL_1_SWITCH:
		MainMenuRender();
		GameReleaseAll();

		if (LoadLevel("maps/level/level1.lvl"))
			g_gameState = GS_LEVEL;
		
		break;
	case GS_LEVEL_2_SWITCH:
			MainMenuRender();
			GameReleaseAll();

			if (LoadLevel("maps/level/level2.lvl"))
				g_gameState = GS_LEVEL;
			
		
		break;
	case GS_LEVEL_3_SWITCH:
			MainMenuRender();
			GameReleaseAll();

			if (LoadLevel("maps/level/level3.lvl"))
				g_gameState = GS_LEVEL;
			
		break;
	case GS_LEVEL_4_SWITCH:
			MainMenuRender();
			GameReleaseAll();

			if (LoadLevel("maps/level/level4.lvl"))
				g_gameState = GS_LEVEL;
			
		break;
	}


	if(g_gameState == GS_LEVEL)
	{
		int time = (int)(g_gameWorld.m_totalTime - g_gameWorld.m_currentTime);

		if(time <= 0)
			g_gameWorld.m_missionStatus = MISSION_FAIL;

		if(g_gameWorld.m_numArtifactsCollected >= g_gameWorld.m_totalArtifacts)
			g_gameWorld.m_missionStatus = MISSION_COMPLETE;
	}
}

void GameShutdown()
{
	GameReleaseAll();
}

bool ObjectsTestCollision(int i)
{
	MyBoundingSphere sphere;
	int index = g_gameWorld.m_models[i].m_id;

	g_Render->GetXModelBoundingSphere(index, &sphere.m_center, &sphere.m_radius);

	MyMatrix4x4 *worldMat = &g_gameWorld.m_models[i].worldMat;
	sphere.m_center = worldMat->VectorMatrixMultiply(sphere.m_center);

	sphere.m_radius -= 0.5f;

	if(sphere.isPointInside(g_camera.m_pos))
		return true;

	return false;
}

bool CharacterTestCollision(int i)
{
	MyBoundingSphere sphere;
	int index = g_gameWorld.m_characters[i].m_id;

	if(!g_gameWorld.m_characters[i].m_visible)
		return false;

	g_Render->GetXModelBoundingSphere(index, &sphere.m_center, &sphere.m_radius);

	MyMatrix4x4 *worldMat = &g_gameWorld.m_characters[i].worldMat;
	sphere.m_center = worldMat->VectorMatrixMultiply(sphere.m_center);

	if(sphere.isPointInside(g_camera.m_pos))
		return true;

	return false;
}

bool CharacterTestCollision(int i, MyRay &ray)
{
	MyBoundingSphere sphere;
	int index = g_gameWorld.m_characters[i].m_id;

	if(!g_gameWorld.m_characters[i].m_visible)
		return false;

	g_Render->GetXModelBoundingSphere(index, &sphere.m_center, &sphere.m_radius);

	MyMatrix4x4 *worldMat = &g_gameWorld.m_characters[i].worldMat;
	sphere.m_center = worldMat->VectorMatrixMultiply(sphere.m_center);

	if(ray.Intersect(sphere.m_center, sphere.m_radius, NULL))
		return true;

	return false;
}

bool CharacterProcess(int i)
{
	MyBoundingSphere sphere;
	int index = g_gameWorld.m_characters[i].m_id;

	if(!g_gameWorld.m_characters[i].m_visible)
		return false;

	g_Render->GetXModelBoundingSphere(index, &sphere.m_center, &sphere.m_radius);

	MyMatrix4x4 *worldMat = &g_gameWorld.m_characters[i].worldMat;
	sphere.m_center = worldMat->VectorMatrixMultiply(sphere.m_center);

	sphere.m_radius *= 5;

	if(sphere.isPointInside(g_camera.m_pos))
		return true;

	return false;
}

void GameProcessInput()
{
	if(!g_InputSystem) return;

	g_InputSystem->UpdateDevices();

	if(g_InputSystem->IsKeyUp(DIK_ESCAPE))
	{
		if(g_gameState == GS_MENU)
		{
			switch(g_currentGUI)
			{
			case GAME_MAIN_MENU_SCREEN:
				PostQuitMessage(0);
				break;
			default:
				g_currentGUI = GAME_MAIN_MENU_SCREEN;
				break;
			}
		}
		else if(g_gameState == GS_LEVEL)
		{
			GameReleaseAll();

			InitializeMainMenu();
			g_gameState = GS_MENU;
			g_currentGUI = GAME_MAIN_MENU_SCREEN;
		}
	}

	if(g_gameState == GS_LEVEL && g_gameWorld.m_missionStatus == MISSION_ONGOING )
	{
		if(g_InputSystem->IsKeyDown(DIK_UP))
		{
			g_camera.MoveCamera(0.04f);
			
			for(int i=0; i<g_gameWorld.m_totalModels;i++)
				if(ObjectsTestCollision(i))
				{
					g_camera.MoveCamera(-0.04f);
					break;
				}

			for(int i= 0; i < g_gameWorld.m_totalCharacters; i++)
			{
				if(CharacterProcess(i))
				{
					if(!g_gameWorld.m_characterSpot[i])
						g_gameWorld.m_spottedCount++;

					g_gameWorld.m_characterSpot[i] = 1;

					if(CharacterTestCollision(i))
					{
						g_camera.MoveCamera(-0.04f);
						break;
					}
				}
			}
		}
		if(g_InputSystem->IsKeyDown(DIK_DOWN))
		{
			g_camera.MoveCamera(-0.04f);
			
			for(int i=0; i<g_gameWorld.m_totalModels;i++)
				if(ObjectsTestCollision(i))
				{
					g_camera.MoveCamera(0.04f);
					break;
				}

			for(int i= 0; i < g_gameWorld.m_totalCharacters; i++)
			{
				if(CharacterProcess(i))
				{
					if(!g_gameWorld.m_characterSpot[i])
						g_gameWorld.m_spottedCount++;

					g_gameWorld.m_characterSpot[i] = 1;

					if(CharacterTestCollision(i))
					{
						g_camera.MoveCamera(0.04f);
						break;
					}
				}
			}
		}
		if(g_InputSystem->IsKeyDown(DIK_LEFT))
		{
			g_camera.RotateCamera(-0.008f,0,1,0);
		}
		if(g_InputSystem->IsKeyDown(DIK_RIGHT))
		{
			g_camera.RotateCamera(0.008f,0,1,0);
		}
		//// 沿摄像机各分量移动视角  
		//if (g_InputSystem->IsKeyDown(DIK_A))  g_camera.MoveAlongRightVec(-1.0f);
		//if (g_InputSystem->IsKeyDown(DIK_D))  g_camera.MoveAlongRightVec(1.0f);
		//if (g_InputSystem->IsKeyDown(DIK_W))  g_camera.MoveAlongLookVec(1.0f);
		//if (g_InputSystem->IsKeyDown(DIK_S))  g_camera.MoveAlongLookVec(-1.0f);
		//if (g_InputSystem->IsKeyDown(DIK_R))  g_camera.MoveAlongUpVec(1.0f);
		//if (g_InputSystem->IsKeyDown(DIK_F))  g_camera.MoveAlongUpVec(-1.0f);

		////沿摄像机各分量旋转视角  
		//if (g_InputSystem->IsKeyDown(DIK_LEFT))  g_camera.RotationUpVec(-0.003f);
		//if (g_InputSystem->IsKeyDown(DIK_RIGHT)) g_camera.RotationUpVec(0.003f);
		//if (g_InputSystem->IsKeyDown(DIK_UP))  g_camera.RotationRightVec(-0.003f);
		//if (g_InputSystem->IsKeyDown(DIK_DOWN))  g_camera.RotationRightVec(0.003f);
		//if (g_InputSystem->IsKeyDown(DIK_Q)) g_camera.RotationLookVec(0.001f);
		//if (g_InputSystem->IsKeyDown(DIK_E)) g_camera.RotationLookVec(-0.001f);

		////鼠标控制右向量和上向量的旋转  
		//g_camera.RotationUpVec(g_InputSystem->GetMousePos().x* 0.0003f);
		//g_camera.RotationRightVec(g_InputSystem->GetMousePos().y* 0.0003f);

		////鼠标滚轮控制观察点收缩操作  
		//static FLOAT fPosZ = 0.0f;
		//fPosZ += g_InputSystem->GetMouseWheelPos()*0.03f;

	}

	g_viewRay.m_origin = g_camera.m_pos;
	g_viewRay.m_direction = g_camera.m_view - g_camera.m_pos;
	g_viewRay.m_direction.Normal();

	if(g_InputSystem->MouseButtonUp(MOUSE_LEFT_BUTTON))
	{

		for(int i=0; i<g_gameWorld.m_totalCharacters; i++)
		{
			if(g_gameWorld.m_characters[i].m_visible)
			{
				if(CharacterTestCollision(i, g_viewRay))
				{
					g_gameWorld.m_characters[i].m_visible = 0;
					g_gameWorld.g_totalEnemiesKilled++;
				}
			}
		}
	}

	POINT pos = {0,0};
	GetCursorPos(&pos);

	g_mouseX = pos.x;
	g_mouseY = pos.y;

	if(g_InputSystem->MouseButtonDown(MOUSE_LEFT_BUTTON))
		g_LMBDown = true;
	if(!g_InputSystem->MouseButtonDown(MOUSE_LEFT_BUTTON))
		g_LMBDown = false;
}

void GameReleaseAll()
{
	if(!g_Render) return;

	g_Render->ReleaseAllStaticBuffers();
	g_Render->ReleaseAllXModels();
	g_Render->ReleaseAllGUIs();

	g_gameWorld.m_levelID = -1;
	g_gameWorld.m_skyBoxID = -1;

	if(g_gameWorld.m_models)
		delete[] g_gameWorld.m_models;
	g_gameWorld.m_models = NULL;
	g_gameWorld.m_totalModels = 0;

	g_mainGui = -1;
	g_startGui = -1;
	g_creditsGui = -1;
	g_currentGUI = GAME_MAIN_MENU_SCREEN;

}