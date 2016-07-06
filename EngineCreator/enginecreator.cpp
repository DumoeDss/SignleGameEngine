#include "enginecreator.h"
#include "mainwindow.h"
#include "gameEngine.h"
#include <map>
#include <QTimer>
#include <QKeyEvent> 
#include <QTime>
bool g_LMBDown = false;
int g_mouseX = 0, g_mouseY = 0;

#pragma comment(lib, "../debug/GameEngine.lib")
HWND g_hwnd = 0;
HINSTANCE g_hInstance = 0;

std::map<QString, int> guiId;
std::map<QString, int> xModelId;

EngineCreator::EngineCreator(QWidget *parent, int m_width, int m_height)
	: QWidget(parent)
{
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);
	this->setFixedSize(m_width, m_height);
	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	connect(timer, SIGNAL(timeout()), this, SLOT(timer_done()));
	timer->start(20);
	g_Camera = 0;
	ligntIndex = 0;
	m_light = 0;
	g_hwnd = (HWND)winId();
	g_hInstance = qWinAppInst();	
	InitEngine(width(), height(), g_hwnd, g_hInstance, 0, MY_MS_SAMPLES_4);
	m_gui_id = 0;
	InitGui();
	m_ini_file = new IniFile();
	m_ini_file->process_object_ini();
	changeWorld();
}

EngineCreator::~EngineCreator()
{
	ShutdownEngine();
}

void EngineCreator::timer_done() 
{
	processInput();
}

void EngineCreator::resizeEvent(QResizeEvent *e)
{
	//d3dResize();
}

void EngineCreator::paintEvent(QPaintEvent *e)
{
	d3dRender();
}

void EngineCreator::d3dRender()
{	
	if (!g_Render) 
		return;	
	g_Render->StartRender(1, 1, 0);
	if (worldCamera.size() > 0) {
		renderCamera();
	}
	if (worldSkyBox.size() > 0) {
		renderSkyBox();
	}
	if (worldTerrain.size() > 0) {
		renderTerrain();
	}
	if (worldLight.size() > 0) {
		renderLight();
	}
	if (worldParticle.size() > 0) {
		renderParticle();
	}
	if (worldSprite.size() > 0) {
		renderSprite();
	}
	if (worldButton.size() > 0) {
		renderButton();
	}
	if (worldText.size() > 0) {
		renderText();
	}
	if (worldxModel.size() > 0) {
		renderxModel();
	}
	if (worldCube.size() > 0) {
		renderCube();
	}
	if (worldSphere.size() > 0) {
		renderSphere();
	}
	if (worldFog.size() > 0) {
		renderFog();
	} else {
		g_Render->DisableFog();
	}
	g_Render->EndRendering();
}

void EngineCreator::changeWorld() {
	if (worldCamera.size() > 0) {	
		m_cameraType = (*worldCamera.begin()).second.type;
		m_cameraSpeed = (*worldCamera.begin()).second.speed;
		if (m_cameraType == 0) {
			g_Camera = new MyCamera(MyCamera::CameraType::LANDOBJECT);
		}else if(m_cameraType == 1){
			g_Camera = new MyCamera(MyCamera::CameraType::AIRCRAFT);
		}
		MyVector3 pos = MyVector3(
			static_cast<float>((*worldCamera.begin()).second.posX),
			static_cast<float>((*worldCamera.begin()).second.posY),
			static_cast<float>((*worldCamera.begin()).second.posZ)
			);
		g_Camera->setCameraPos(pos);				
	}
	if (worldSkyBox.size() > 0) {
		std::vector<char *> skyName;
		float skyLen = (*worldSkyBox.begin()).second.length;
		char *skyFront, *skyBack, *skyLeft, *skyRight, *skyTop;
		QByteArray baFront = (*worldSkyBox.begin()).second.skyFront.toLatin1();
		skyFront = baFront.data();
		QByteArray baBack = (*worldSkyBox.begin()).second.skyBack.toLatin1();
		skyBack = baBack.data();
		QByteArray baLeft = (*worldSkyBox.begin()).second.skyLeft.toLatin1();
		skyLeft = baLeft.data();
		QByteArray baRight = (*worldSkyBox.begin()).second.skyRight.toLatin1();
		skyRight = baRight.data();
		QByteArray baTop = (*worldSkyBox.begin()).second.skyTop.toLatin1();
		skyTop = baTop.data();
		skyName.push_back(skyFront);
		skyName.push_back(skyBack);
		skyName.push_back(skyLeft);
		skyName.push_back(skyRight);
		skyName.push_back(skyTop);
		g_Render->InitSkyBox(skyLen, skyName);
	}
	if (worldTerrain.size() > 0) {
		std::string rawFileName;
		std::string fileName;
		int numVertsPerRow, numVertsPerCol, cellSpacing;
		float heightScale;
		rawFileName = (*worldTerrain.begin()).second.rawFileName.toStdString();
		fileName = (*worldTerrain.begin()).second.fileName.toStdString();
		numVertsPerRow = (*worldTerrain.begin()).second.numVertsPerRow;
		numVertsPerCol = (*worldTerrain.begin()).second.numVertsPerCol;
		cellSpacing = (*worldTerrain.begin()).second.cellSpacing;
		heightScale = (*worldTerrain.begin()).second.heightScale;
		g_Render->InitTerrain(rawFileName, numVertsPerRow, numVertsPerCol, cellSpacing, heightScale, fileName);
	}
	if (worldLight.size() > 0) {
		int posX, posY, posZ, rotX, rotY, rotZ, colorR, colorG, colorB,type;
		posX = (*worldLight.begin()).second.posX;
		posY = (*worldLight.begin()).second.posY;
		posZ = (*worldLight.begin()).second.posZ;
		rotX = (*worldLight.begin()).second.rotX;
		rotY = (*worldLight.begin()).second.rotY;		
		rotZ = (*worldLight.begin()).second.rotZ;
		colorR = (*worldLight.begin()).second.colorR;
		colorG = (*worldLight.begin()).second.colorG;
		colorB = (*worldLight.begin()).second.colorB;
		type = (*worldLight.begin()).second.type;
		m_light = new myLight();
		m_light->lightType = type;
		m_light->color = D3DXCOLOR(colorR / 255, colorG / 255, colorB / 255, 255 / 255);
		m_light->posX = posX;
		m_light->posY = posY;
		m_light->posZ = posZ;
		m_light->dirX = rotX;
		m_light->dirY = rotY;
		m_light->dirZ = rotZ;
	}

	if(worldSprite.size() > 0) {
		
	}
	if (worldButton.size() > 0) {
		for (auto &wButton : worldButton) {
			int posX, posY, width, heiht;
			QString fileNameUp, fileNameDown, fileNameMove;
			fileNameUp = wButton.second.fileNameUp;
			fileNameDown = wButton.second.fileNameDown;
			fileNameMove = wButton.second.fileNameMove;
			posX = wButton.second.posX;
			posY = wButton.second.posY;
			QByteArray baUp = fileNameUp.toLatin1();
			QByteArray baDown = fileNameDown.toLatin1();
			QByteArray baMove = fileNameMove.toLatin1();
			char *up = baUp.data();
			char *down = baDown.data();
			char *move = baMove.data();
			g_Render->AddGUIButton(g_mainGui, m_gui_id, posX, posY, up, move, down);
			guiId.insert({ wButton.first,m_gui_id });
			m_gui_id++;
		}
	}
	if (worldText.size() > 0) {
		for (auto &wText : worldText) {
			int posX, posY,colorR,colorG,colorB;
			unsigned long col;
			QString qstrText;
			posX = wText.second.posX;
			posY = wText.second.posY;
			colorR = wText.second.colorR;
			colorG = wText.second.colorG;
			colorB = wText.second.colorB;
			qstrText = wText.second.text;
			col = D3DCOLOR_XRGB(colorR, colorG, colorB);
			QByteArray baText = qstrText.toLatin1();
			char *text = baText.data();
			g_Render->AddGUIStaticText(g_mainGui, m_gui_id, text, posX, posY, col, g_fontID);
			guiId.insert({ wText.first,m_gui_id });
			m_gui_id++;
		}
		
		
	}
	if (worldxModel.size() > 0) {
		for (auto &xModel : worldxModel) {
			int posX, posY, posZ, rotX, rotY, rotZ;
			float scaleX, scaleY, scaleZ;
			QString fileName;
			posX = xModel.second.posX;
			//posY = xModel.second.posY;
			posZ = xModel.second.posZ;
			rotX = xModel.second.rotX;
			rotY = xModel.second.rotY;
			rotZ = xModel.second.rotZ;
			scaleX = xModel.second.scaleX;
			scaleY = xModel.second.scaleY;
			scaleZ = xModel.second.scaleZ;
			fileName = xModel.second.fileName;
			if (worldTerrain.size() > 0) {
				float height = g_Render->getHeight(posX, posZ);
				posY = height;
			}
			QByteArray qbaName = fileName.toLatin1();
			char *name = qbaName.data();
			g_Render->AddXModel(name);
			xModelId.insert({ xModel.first,g_Render->getXModelNum() - 1 });
			MyMatrix4x4 trans, matRotX, matRotY, matRotZ, worldMat;

			trans.Translate(posX, posY, posZ);
			if (rotX)
				matRotX.Rotate(rotX, 1, 0, 0);
			if (rotY)
				matRotY.Rotate(rotY, 0, 1, 0);
			if (rotZ)
				matRotZ.Rotate(rotZ, 0, 0, 1);
			D3DXMATRIX matScal;
			D3DXMatrixScaling(&matScal, scaleX, scaleY, scaleZ);
			g_Render->SetXModelScaleMatrix(g_Render->getXModelNum() - 1, matScal);
			worldMat = trans * (matRotX * matRotY * matRotZ);
			g_Render->SetXModelMatrix(g_Render->getXModelNum() - 1, worldMat);
		}
		
	}
	if (worldCube.size() > 0) {
		int posX, posY, posZ, rotX, rotY, rotZ, colorR, colorG, colorB, type;
		float scaleX, scaleY, scaleZ;
		posX = (*worldCube.begin()).second.posX;
		posY = (*worldCube.begin()).second.posY;
		posZ = (*worldCube.begin()).second.posZ;
		rotX = (*worldCube.begin()).second.rotX;
		rotY = (*worldCube.begin()).second.rotY;
		rotZ = (*worldCube.begin()).second.rotZ;
		scaleX = (*worldCube.begin()).second.scaleX;
		scaleY = (*worldCube.begin()).second.scaleY;
		scaleZ = (*worldCube.begin()).second.scaleZ;
		colorR = (*worldCube.begin()).second.colorR;
		colorG = (*worldCube.begin()).second.colorG;
		colorB = (*worldCube.begin()).second.colorB;

		MyVector3 pos(posX, posY, posZ);
		MyVector3 rot(rotX, rotY, rotZ);
		MyVector3 scale(scaleX, scaleY, scaleZ);
		MyVector3 color(colorR, colorG, colorB);

		g_Render->InitObj( 0 ,pos, rot, scale, color);
	}
	if (worldSphere.size() > 0) {
		int posX, posY, posZ, rotX, rotY, rotZ, colorR, colorG, colorB, type;
		float scaleX, scaleY, scaleZ;
		posX = (*worldSphere.begin()).second.posX;
		posY = (*worldSphere.begin()).second.posY;
		posZ = (*worldSphere.begin()).second.posZ;
		rotX = (*worldSphere.begin()).second.rotX;
		rotY = (*worldSphere.begin()).second.rotY;
		rotZ = (*worldSphere.begin()).second.rotZ;
		scaleX = (*worldSphere.begin()).second.scaleX;
		scaleY = (*worldSphere.begin()).second.scaleY;
		scaleZ = (*worldSphere.begin()).second.scaleZ;
		colorR = (*worldSphere.begin()).second.colorR;
		colorG = (*worldSphere.begin()).second.colorG;
		colorB = (*worldSphere.begin()).second.colorB;

		MyVector3 pos(posX, posY, posZ);
		MyVector3 rot(rotX, rotY, rotZ);
		MyVector3 scale(scaleX, scaleY, scaleZ);
		MyVector3 color(colorR, colorG, colorB);

		g_Render->InitObj(1, pos, rot, scale, color);
	}
	if (worldParticle.size() > 0) {
		int type, numParticles, height, width, length;
		char *fileName;
		MyVector3 pos;
		type = (*worldParticle.begin()).second.type;
		height = (*worldParticle.begin()).second.height;
		width = (*worldParticle.begin()).second.length;
		length = (*worldParticle.begin()).second.width;
		pos = (*worldParticle.begin()).second.postion;
		QByteArray baFileName = (*worldParticle.begin()).second.fileName.toLatin1();
		fileName = baFileName.data();
		numParticles = (*worldParticle.begin()).second.num;
		g_Render->InitParticle(type, length, width, height, fileName, numParticles, pos);
	}

	if (worldFog.size() > 0) {

	}
	else {
		g_Render->DisableFog();
	}
}

void EngineCreator::changeWorld(QString name,int objType) {
	switch (objType) {
	case 1://My_Camera
		if ((*worldCamera.find(name)).first == name) {
			m_cameraType = (*worldCamera.begin()).second.type;
			m_cameraSpeed = (*worldCamera.begin()).second.speed;
			if (m_cameraType == 0) {
				g_Camera = new MyCamera(MyCamera::CameraType::LANDOBJECT);
			}
			else if (m_cameraType == 1) {
				g_Camera = new MyCamera(MyCamera::CameraType::AIRCRAFT);
			}
			MyVector3 pos = MyVector3(
				static_cast<float>((*worldCamera.begin()).second.posX),
				static_cast<float>((*worldCamera.begin()).second.posY),
				static_cast<float>((*worldCamera.begin()).second.posZ)
			);
			g_Camera->setCameraPos(pos);
		}
		break;
	case 2://My_SkyBox
		if ((*worldSkyBox.find(name)).first == name) {
			std::vector<char *> skyName;
			float skyLen = (*worldSkyBox.begin()).second.length;
			char *skyFront, *skyBack, *skyLeft, *skyRight, *skyTop;
			QByteArray baFront = (*worldSkyBox.begin()).second.skyFront.toLatin1();
			skyFront = baFront.data();
			QByteArray baBack = (*worldSkyBox.begin()).second.skyBack.toLatin1();
			skyBack = baBack.data();
			QByteArray baLeft = (*worldSkyBox.begin()).second.skyLeft.toLatin1();
			skyLeft = baLeft.data();
			QByteArray baRight = (*worldSkyBox.begin()).second.skyRight.toLatin1();
			skyRight = baRight.data();
			QByteArray baTop = (*worldSkyBox.begin()).second.skyTop.toLatin1();
			skyTop = baTop.data();
			skyName.push_back(skyFront);
			skyName.push_back(skyBack);
			skyName.push_back(skyLeft);
			skyName.push_back(skyRight);
			skyName.push_back(skyTop);
			g_Render->InitSkyBox(skyLen, skyName);
		}
		break;
	case 3://My_Terrain
		if ((*worldTerrain.find(name)).first == name) {
			std::string rawFileName;
			std::string fileName;
			int numVertsPerRow, numVertsPerCol, cellSpacing;
			float heightScale;
			rawFileName = (*worldTerrain.begin()).second.rawFileName.toStdString();
			fileName = (*worldTerrain.begin()).second.fileName.toStdString();
			numVertsPerRow = (*worldTerrain.begin()).second.numVertsPerRow;
			numVertsPerCol = (*worldTerrain.begin()).second.numVertsPerCol;
			cellSpacing = (*worldTerrain.begin()).second.cellSpacing;
			heightScale = (*worldTerrain.begin()).second.heightScale;
			g_Render->InitTerrain(rawFileName, numVertsPerRow, numVertsPerCol, cellSpacing, heightScale, fileName);
		}
		break;
	case 4://My_Light
		if ((*worldLight.find(name)).first == name) {
			int posX, posY, posZ, rotX, rotY, rotZ, colorR, colorG, colorB, type;
			posX = (*worldLight.begin()).second.posX;
			posY = (*worldLight.begin()).second.posY;
			posZ = (*worldLight.begin()).second.posZ;
			rotX = (*worldLight.begin()).second.rotX;
			rotY = (*worldLight.begin()).second.rotY;
			rotZ = (*worldLight.begin()).second.rotZ;
			colorR = (*worldLight.begin()).second.colorR;
			colorG = (*worldLight.begin()).second.colorG;
			colorB = (*worldLight.begin()).second.colorB;
			type = (*worldLight.begin()).second.type;
			m_light = new myLight();
			m_light->lightType = type;
			m_light->color = D3DXCOLOR(colorR / 255, colorG / 255, colorB / 255, 255 / 255);
			m_light->posX = posX;
			m_light->posY = posY;
			m_light->posZ = posZ;
			m_light->dirX = rotX;
			m_light->dirY = rotY;
			m_light->dirZ = rotZ;
		}
		break;
	case 5://My_Particle
		if ((*worldParticle.find(name)).first == name) {
			int type, numParticles, height, width, length;
			char *fileName;
			MyVector3 pos;
			type = (*worldParticle.begin()).second.type;
			height = (*worldParticle.begin()).second.height;
			width = (*worldParticle.begin()).second.length;
			length = (*worldParticle.begin()).second.width;
			pos = (*worldParticle.begin()).second.postion;
			QByteArray baFileName = (*worldParticle.begin()).second.fileName.toLatin1();
			fileName = baFileName.data();
			numParticles = (*worldParticle.begin()).second.num;
			g_Render->InitParticle(type, length, width, height, fileName, numParticles, pos);
		}
		break;
	case 6://My_Fog
		if (worldFog.size() > 0) {

		}
		else {
			g_Render->DisableFog();
		}
		break;
	case 7://My_Sprite
		break;
	case 8://My_Button
		if ((*worldButton.find(name)).first == name) {
				int posX, posY, width, heiht;
				QString fileNameUp, fileNameDown, fileNameMove;
				fileNameUp = (*worldButton.find(name)).second.fileNameUp;
				fileNameDown = (*worldButton.find(name)).second.fileNameDown;
				fileNameMove = (*worldButton.find(name)).second.fileNameMove;
				posX = (*worldButton.find(name)).second.posX;
				posY = (*worldButton.find(name)).second.posY;
				QByteArray baUp = fileNameUp.toLatin1();
				QByteArray baDown = fileNameDown.toLatin1();
				QByteArray baMove = fileNameMove.toLatin1();
				char *up = baUp.data();
				char *down = baDown.data();
				char *move = baMove.data();
				g_Render->AddGUIButton(g_mainGui, m_gui_id, posX, posY, up, move, down);
				guiId.insert({ (*worldButton.find(name)).first,m_gui_id });
				m_gui_id++;
		}
		break;
	case 9://My_Text
		if ((*worldText.find(name)).first == name) {
				int posX, posY, colorR, colorG, colorB;
				unsigned long col;
				QString qstrText;
				posX = (*worldText.find(name)).second.posX;
				posY = (*worldText.find(name)).second.posY;
				colorR = (*worldText.find(name)).second.colorR;
				colorG = (*worldText.find(name)).second.colorG;
				colorB = (*worldText.find(name)).second.colorB;
				qstrText = (*worldText.find(name)).second.text;
				col = D3DCOLOR_XRGB(colorR, colorG, colorB);
				QByteArray baText = qstrText.toLatin1();
				char *text = baText.data();
				g_Render->AddGUIStaticText(g_mainGui, m_gui_id, text, posX, posY, col, g_fontID);
				guiId.insert({ (*worldText.find(name)).first,m_gui_id });
				m_gui_id++;
		}
		break;
	case 10://My_xModel
		if ((*worldxModel.find(name)).first == name) {
			int posX, posY, posZ, rotX, rotY, rotZ;
			float scaleX, scaleY, scaleZ;
			QString fileName;
			posX = (*worldxModel.find(name)).second.posX;
			//posY = (*worldxModel.find(name)).second.posY;
			posZ = (*worldxModel.find(name)).second.posZ;
			rotX = (*worldxModel.find(name)).second.rotX;
			rotY = (*worldxModel.find(name)).second.rotY;
			rotZ = (*worldxModel.find(name)).second.rotZ;
			scaleX = (*worldxModel.find(name)).second.scaleX;
			scaleY = (*worldxModel.find(name)).second.scaleY;
			scaleZ = (*worldxModel.find(name)).second.scaleZ;
			fileName = (*worldxModel.find(name)).second.fileName;
			if (worldTerrain.size() > 0) {
				float height = g_Render->getHeight(posX, posZ);
				posY = height;
			}
			QByteArray qbaName = fileName.toLatin1();
			char *charFileName = qbaName.data();
			int id = 0;
			if (xModelId.find((*worldxModel.find(name)).first) == xModelId.end()) {
				id = g_Render->getXModelNum();
				xModelId.insert({ (*worldxModel.find(name)).first,id });	
				g_Render->AddXModel(charFileName);
			} else{
				id = (*xModelId.find((*worldxModel.find(name)).first)).second;
				g_Render->ChangeXModel(id, charFileName);
			}
			

			MyMatrix4x4 trans, matRotX, matRotY, matRotZ, worldMat;

			trans.Translate(posX, posY, posZ);
			if (rotX)
				matRotX.Rotate(rotX, 1, 0, 0);
			if (rotY)
				matRotY.Rotate(rotY, 0, 1, 0);
			if (rotZ)
				matRotZ.Rotate(rotZ, 0, 0, 1);

			worldMat = trans * (matRotX * matRotY * matRotZ);
			D3DXMATRIX matScal;
			D3DXMatrixScaling(&matScal, scaleX, scaleY, scaleZ);
			g_Render->SetXModelScaleMatrix(id, matScal);
			g_Render->SetXModelMatrix(id, worldMat);
		}
		break;
	case 11://My_Cube
		if ((*worldCube.find(name)).first == name) {
			int posX, posY, posZ, rotX, rotY, rotZ, colorR, colorG, colorB, type;
			float scaleX, scaleY, scaleZ;
			posX = (*worldCube.begin()).second.posX;
			posY = (*worldCube.begin()).second.posY;
			posZ = (*worldCube.begin()).second.posZ;
			rotX = (*worldCube.begin()).second.rotX;
			rotY = (*worldCube.begin()).second.rotY;
			rotZ = (*worldCube.begin()).second.rotZ;
			scaleX = (*worldCube.begin()).second.scaleX;
			scaleY = (*worldCube.begin()).second.scaleY;
			scaleZ = (*worldCube.begin()).second.scaleZ;
			colorR = (*worldCube.begin()).second.colorR;
			colorG = (*worldCube.begin()).second.colorG;
			colorB = (*worldCube.begin()).second.colorB;

			MyVector3 pos(posX, posY, posZ);
			MyVector3 rot(rotX, rotY, rotZ);
			MyVector3 scale(scaleX, scaleY, scaleZ);
			MyVector3 color(colorR, colorG, colorB);

			g_Render->InitObj(0, pos, rot, scale, color);
			return;
		}
		break;
	case 12://My_Sphere
		if ((*worldSphere.find(name)).first == name) {
			int posX, posY, posZ, rotX, rotY, rotZ, colorR, colorG, colorB, type;
			float scaleX, scaleY, scaleZ;
			posX = (*worldSphere.begin()).second.posX;
			posY = (*worldSphere.begin()).second.posY;
			posZ = (*worldSphere.begin()).second.posZ;
			rotX = (*worldSphere.begin()).second.rotX;
			rotY = (*worldSphere.begin()).second.rotY;
			rotZ = (*worldSphere.begin()).second.rotZ;
			scaleX = (*worldSphere.begin()).second.scaleX;
			scaleY = (*worldSphere.begin()).second.scaleY;
			scaleZ = (*worldSphere.begin()).second.scaleZ;
			colorR = (*worldSphere.begin()).second.colorR;
			colorG = (*worldSphere.begin()).second.colorG;
			colorB = (*worldSphere.begin()).second.colorB;

			MyVector3 pos(posX, posY, posZ);
			MyVector3 rot(rotX, rotY, rotZ);
			MyVector3 scale(scaleX, scaleY, scaleZ);
			MyVector3 color(colorR, colorG, colorB);

			g_Render->InitObj(1, pos, rot, scale, color);
			return;
		}
		break;
	}
}

void EngineCreator::renderCamera() {
	processInput();
	MyMatrix4x4 view;
	g_Camera->getViewMatrix(view);
	g_Render->SetViewMatrix(&view);
}

void EngineCreator::renderSkyBox() {
	
	//绘制天空盒
	D3DXMATRIX matSky, matTransSky, matRotSky;
	D3DXMatrixTranslation(&matTransSky, 0.0f, -130.0f, 0.0f);
	QDateTime time = QDateTime::currentDateTime();
	D3DXMatrixRotationY(&matRotSky, time.toTime_t() * (-0.00002f));   //旋转天空网格, 简单模拟云彩运动效果
	matSky = matTransSky*matRotSky;
	g_Render->RenderSkyBox(&matSky, false);
}

void EngineCreator::renderTerrain() {	
	g_Render->RenderTerrain(true);
}

void EngineCreator::renderLight() {
	for (int i = 0; i != worldLight.size(); ++i) {
		g_Render->SetLight(m_light, i);
	}
}

void EngineCreator::renderParticle() {
	g_Render->RenderParticle(0.1);
}

void EngineCreator::renderFog() {
	float fogStart, fogEnd;
	FogType fogType = FOG_VERTEX;
	int colorR, colorG, colorB;
	unsigned long fogColor;
	bool rangeFog = true;
	fogStart = (*worldFog.begin()).second.start;
	fogEnd = (*worldFog.begin()).second.end;
	colorR = (*worldFog.begin()).second.color_r;
	colorG = (*worldFog.begin()).second.color_g;
	colorB = (*worldFog.begin()).second.color_b;
	fogColor = D3DCOLOR_XRGB(colorR, colorG, colorB);
	g_Render->EnableFog(fogStart, fogEnd, fogType, fogColor, rangeFog);
}

void EngineCreator::renderSprite() {

}

void EngineCreator::renderButton() {
	g_Render->ProcessGUI(g_mainGui, g_LMBDown, g_mouseX, g_mouseY, MainMenuCallback);
}

void EngineCreator::renderText() {
	g_Render->ProcessGUI(g_mainGui, g_LMBDown, g_mouseX, g_mouseY, MainMenuCallback);
}

void EngineCreator::renderxModel() {
	static QTime fLastTime = QTime::currentTime();
	static QTime fCurrTime = QTime::currentTime();
	static FLOAT fTimeDelta = 0.0f;
	fCurrTime = QTime::currentTime();
	fTimeDelta = fLastTime.msecsTo(fCurrTime) / 1000.0f;
	fLastTime = fCurrTime;
	
	g_Render->UpdateXModelAnim(fTimeDelta);
	g_Render->RenderXModelAnim();
}

void EngineCreator::renderCube() {
	if (worldLight.size() > 0) {
		g_Render->SetLight(m_light, 0);
	}
	g_Render->RenderObj();
}

void EngineCreator::renderSphere() {
	g_Render->RenderObj();
}	

void EngineCreator::do_change_obj_pro(QString name) {
	int objType;
	objType = m_ini_file->process_object_ini(name);
	changeWorld(name, objType);
}

void EngineCreator::processInput() {
	if (!g_InputSystem) return;

	g_InputSystem->UpdateDevices();
	if (g_Camera) {
		if (g_InputSystem->IsKeyDown(DIK_W))
		{
			g_Camera->walk(m_cameraSpeed);
		}
		if (g_InputSystem->IsKeyDown(DIK_S))
		{
			g_Camera->walk(-1.0f*m_cameraSpeed);
		}
		if (g_InputSystem->IsKeyDown(DIK_A))
		{
			g_Camera->strafe(-1.0f*m_cameraSpeed);
		}
		if (g_InputSystem->IsKeyDown(DIK_D))
		{
			g_Camera->strafe(m_cameraSpeed);
		}
		static long oldX = 0, oldY = 0;
		long currentX, currentY, diffX, diffY;

		POINT temp = g_InputSystem->GetMousePos();
		currentY = temp.y;
		currentX = temp.x;

		diffY = currentY - oldY;
		diffX = currentX - oldX;
		if (abs(diffX) > abs(diffY)) {
			g_Camera->yaw(diffX*0.003);
		}
		else {
			g_Camera->pitch(diffY*0.003f);
		}
		oldX = currentX;
		oldY = currentY;
		if (m_cameraType == 0) {
			MyVector3 pos = g_Camera->getCameraPos();
			if (worldTerrain.size() > 0) {
				float height = g_Render->getHeight(pos.x, pos.z);
				pos.y = height + 20.0f;
			}
			g_Camera->setCameraPos(pos);
		}
		else {
			if (g_InputSystem->IsKeyDown(DIK_R))
				g_Camera->fly(m_cameraSpeed);
			if (g_InputSystem->IsKeyDown(DIK_F))
				g_Camera->fly(-1.0f*m_cameraSpeed);
			if (g_InputSystem->IsKeyDown(DIK_Q))
				g_Camera->roll(0.01f);
			if (g_InputSystem->IsKeyDown(DIK_E))
				g_Camera->roll(-0.01f);
		}
	}
	
	
	if (g_InputSystem->IsKeyUp(DIK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	POINT curPos = { 0,0 };
	GetCursorPos(&curPos);

	g_mouseX = curPos.x;
	g_mouseY = curPos.y-30;

	if (g_InputSystem->MouseButtonDown(MOUSE_LEFT_BUTTON))
		g_LMBDown = true;
	if (!g_InputSystem->MouseButtonDown(MOUSE_LEFT_BUTTON))
		g_LMBDown = false;
}

void MainMenuCallback(int id, int state)
{

	switch (id)
	{
	case 0:
		if (state == MOUSE_BUTTON_DOWN)
			PostQuitMessage(0);
		break;
	case 1:
		if (state == MOUSE_BUTTON_DOWN)
			PostQuitMessage(0);
		break;
	case 2:
		if (state == MOUSE_BUTTON_DOWN)
		{
			PostQuitMessage(0);
		}
		break;
	case 3:
		if (state == MOUSE_BUTTON_DOWN)
		{
			PostQuitMessage(0);
		}
		break;
	}
}

bool EngineCreator::InitGui() {
	if (!g_Render->CreateGUI(g_mainGui))
		return false;
	return true;
	
}
