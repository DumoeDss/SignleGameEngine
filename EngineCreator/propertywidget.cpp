#include <QVBoxLayout>
#include <QGroupBox>
#include <QObject>

#include "propertywidget.h"
#include "defines.h"
#include "mainwindow.h"
#include "Inifile.h"
#include "gameEngine.h"

#include "pro_skybox.h"
#include "pro_fog.h"
#include "pro_button.h"
#include "pro_cube.h"
#include "pro_light.h"
#include "pro_particle.h"
#include "pro_sphere.h"
#include "pro_sprite.h"
#include "pro_xmodel.h"
#include "pro_terrain.h"
#include "pro_text.h"
#include "pro_camera.h"

PropertyWidget::PropertyWidget(QWidget * parent, proType type) : QWidget(parent),
	fogWidget(0), skyboxWidget(0), particleWidget(0), cameraWidget(0),
	boardWidget(0), buttonWidget(0), cubeWidget(0), lightWidget(0), sphereWidget(0),
	spriteWidget(0), terrainWidget(0), textWidget(0), transformWidget(0), xModelWidget(0),
	nameWidget(0), m_cam(0), m_fog(0), m_button(0), m_cube(0), m_light(0), m_particle(0),
	m_sphere(0), m_skybox(0), m_sprite(0), m_terrain(0), m_text(0), m_xmodel(0), m_ini_file(0)
{
	
	m_type = type;
	mainLayout = new QVBoxLayout;
	switch (type) {
	case EmptyObject:

		break;
	case My_Camera:
		cameraWidget = new pro_camera();
		mainLayout->addWidget(cameraWidget->getGroupBox());
		mainLayout->addStretch();
		//修改名字,创建对象
		connect(cameraWidget, SIGNAL(btn_click()), this, SLOT(do_btn_ok_click()));
		//connect(cameraWidget, SIGNAL(btn_click()), this, SLOT(test()));
		break;
	case My_SkyBox:
		skyboxWidget = new pro_skyBox();
		mainLayout->addWidget(skyboxWidget->getGroupBox());
		mainLayout->addStretch();
		connect(skyboxWidget, SIGNAL(btn_click()), this, SLOT(do_btn_ok_click()));
		break;
	case My_Terrain:
		terrainWidget = new pro_terrain();
		mainLayout->addWidget(terrainWidget->getGroupBox());
		mainLayout->addStretch();
		connect(terrainWidget, SIGNAL(btn_click()), this, SLOT(do_btn_ok_click()));
		break;
	case My_Light:
		lightWidget = new pro_light();
		mainLayout->addWidget(lightWidget->getGroupBox());
		mainLayout->addStretch();
		connect(lightWidget, SIGNAL(btn_click()), this, SLOT(do_btn_ok_click()));
		break;
	case My_Particle:
		particleWidget = new pro_particle();
		mainLayout->addWidget(particleWidget->getGroupBox());
		mainLayout->addStretch();
		connect(particleWidget, SIGNAL(btn_click()), this, SLOT(do_btn_ok_click()));
		break;
	case My_Fog:
		fogWidget = new pro_fog();
		mainLayout->addWidget(fogWidget->getGroupBox());
		mainLayout->addStretch();
		connect(fogWidget, SIGNAL(btn_click()), this, SLOT(do_btn_ok_click()));
		break;
	case My_Sprite:
		spriteWidget = new pro_sprite();
		mainLayout->addWidget(spriteWidget->getGroupBox());
		mainLayout->addStretch();
		connect(spriteWidget, SIGNAL(btn_click()), this, SLOT(do_btn_ok_click()));
		break;
	case My_Button:
		buttonWidget = new pro_button();
		mainLayout->addWidget(buttonWidget->getGroupBox());
		mainLayout->addStretch();
		connect(buttonWidget, SIGNAL(btn_click()), this, SLOT(do_btn_ok_click()));
		break;
	case My_Text:
		textWidget = new pro_text();
		mainLayout->addWidget(textWidget->getGroupBox());
		mainLayout->addStretch();
		connect(textWidget, SIGNAL(btn_click()), this, SLOT(do_btn_ok_click()));
		break;
	case My_xModel:
		xModelWidget = new pro_xModel();
		mainLayout->addWidget(xModelWidget->getGroupBox());
		mainLayout->addStretch();
		connect(xModelWidget, SIGNAL(btn_click()), this, SLOT(do_btn_ok_click()));
		break;
	case My_Cube:
		cubeWidget = new pro_cube();
		mainLayout->addWidget(cubeWidget->getGroupBox());
		mainLayout->addStretch();
		connect(cubeWidget, SIGNAL(btn_click()), this, SLOT(do_btn_ok_click()));
		break;
	case My_Sphere:
		sphereWidget = new pro_sphere();
		mainLayout->addWidget(sphereWidget->getGroupBox());
		mainLayout->addStretch();
		connect(sphereWidget, SIGNAL(btn_click()), this, SLOT(do_btn_ok_click()));
		break;
	}
	
	setLayout(mainLayout);
	ui.setupUi(this);
}

PropertyWidget::~PropertyWidget() {

	SAFE_DELETE(fogWidget);
	SAFE_DELETE(skyboxWidget);
	SAFE_DELETE(particleWidget);
	SAFE_DELETE(cameraWidget);
	SAFE_DELETE(boardWidget);
	SAFE_DELETE(buttonWidget);
	SAFE_DELETE(cubeWidget);
	SAFE_DELETE(lightWidget);
	SAFE_DELETE(sphereWidget);
	SAFE_DELETE(spriteWidget);
	SAFE_DELETE(terrainWidget);
	SAFE_DELETE(textWidget);
	SAFE_DELETE(transformWidget);
	SAFE_DELETE(xModelWidget);
	SAFE_DELETE(nameWidget);
	SAFE_DELETE(mainLayout);

	
}

int PropertyWidget::getPosX() {
	int vaule = 0;
	switch (m_type) {
	case EmptyObject:
		break;
	case My_Camera:
		vaule = cameraWidget->getPosX();
		break;
	case My_Light:
		vaule = lightWidget->getPosX();
		break;
	case My_Particle:
		vaule = particleWidget->getPosX();
		break;
	case My_xModel:
		vaule = xModelWidget->getPosX();
		break;
	case My_Cube:
		vaule = cubeWidget->getPosX();
		break;
	case My_Sphere:
		vaule = sphereWidget->getPosX();
		break;
	case My_Sprite:
		vaule = spriteWidget->getPosX();
		break;
	case My_Button:
		vaule = buttonWidget->getPosX();
		break;
	default:
		vaule = 0;
		break;
	}
	return vaule;
}

int PropertyWidget::getPosY() {
	int vaule = 0;
	switch (m_type) {
	case EmptyObject:
		break;
	case My_Camera:
		vaule = cameraWidget->getPosY();
		break;
	case My_Light:
		vaule = lightWidget->getPosY();
		break;
	case My_Particle:
		vaule = particleWidget->getPosY();
		break;
	case My_xModel:
		vaule = xModelWidget->getPosY();
		break;
	case My_Cube:
		vaule = cubeWidget->getPosY();
		break;
	case My_Sphere:
		vaule = sphereWidget->getPosY();
		break;
	case My_Sprite:
		vaule = spriteWidget->getPosY();
		break;
	case My_Button:
		vaule = buttonWidget->getPosY();
		break;
	default:
		vaule = 0;
		break;
	}
	return vaule;
}

int PropertyWidget::getPosZ() {
	int vaule = 0;
	switch (m_type) {
	case EmptyObject:
		break;
	case My_Camera:
		vaule = cameraWidget->getPosZ();
		break;
	case My_Light:
		vaule = lightWidget->getPosZ();
		break;
	case My_Particle:
		vaule = particleWidget->getPosZ();
		break;
	case My_xModel:
		vaule = xModelWidget->getPosZ();
		break;
	case My_Cube:
		vaule = cubeWidget->getPosZ();
		break;
	case My_Sphere:
		vaule = sphereWidget->getPosZ();
		break;
	default:
		vaule = 0;
		break;
	}
	return vaule;
}

int PropertyWidget::getRotX() {
	int vaule = 0;
	switch (m_type) {
	case EmptyObject:
		break;
	case My_Light:
		vaule = lightWidget->getRotX();
		break;
	case My_xModel:
		vaule = xModelWidget->getRotX();
		break;
	case My_Cube:
		vaule = cubeWidget->getRotX();
		break;
	case My_Sphere:
		vaule = sphereWidget->getRotX();
		break;
	default:
		vaule = 0;
		break;
	}
	return vaule;
}

int PropertyWidget::getRotY() {
	int vaule = 0;
	switch (m_type) {
	case EmptyObject:
		break;
	case My_Light:
		vaule = lightWidget->getRotY();
		break;
	case My_xModel:
		vaule = xModelWidget->getRotY();
		break;
	case My_Cube:
		vaule = cubeWidget->getRotY();
		break;
	case My_Sphere:
		vaule = sphereWidget->getRotY();
		break;
	default:
		vaule = 0;
		break;
	}
	return vaule;
}

int PropertyWidget::getRotZ() {
	int vaule = 0;
	switch (m_type) {
	case EmptyObject:
		break;
	case My_Light:
		vaule = lightWidget->getRotZ();
		break;
	case My_xModel:
		vaule = xModelWidget->getRotZ();
		break;
	case My_Cube:
		vaule = cubeWidget->getRotZ();
		break;
	case My_Sphere:
		vaule = sphereWidget->getRotZ();
		break;
	default:
		vaule = 0;
		break;
	}
	return vaule;
}

int PropertyWidget::getCameraType() {
	if (cameraWidget)
		return cameraWidget->getCameraType();
	else return 0;
}

int PropertyWidget::getSpeed() {
	if (cameraWidget)
		return cameraWidget->getSpeed();
	else return 0;
}

int PropertyWidget::getSkyBoxLength() {
	if (skyboxWidget)
		return skyboxWidget->getSkyBoxLength();
	else return 0;
}

QString PropertyWidget::getSkyBoxFront() {
	if (skyboxWidget)
		return skyboxWidget->getSkyBoxFront();
	else return "";
}

QString PropertyWidget::getSkyBoxBack() {
	if (skyboxWidget)
		return skyboxWidget->getSkyBoxBack();
	else return "";
}

QString PropertyWidget::getSkyBoxLeft() {
	if (skyboxWidget)
		return skyboxWidget->getSkyBoxLeft();
	else return "";
}

QString PropertyWidget::getSkyBoxRight() {
	if (skyboxWidget)
		return skyboxWidget->getSkyBoxRight();
	else return "";
}

QString PropertyWidget::getSkyBoxTop() {
	if (skyboxWidget)
		return skyboxWidget->getSkyBoxTop();
	else return "";
}

int PropertyWidget::getFogType() {
	return fogWidget->getFogType();
}

int PropertyWidget::getFogStart() {
	return  fogWidget->getFogStart();
}

int PropertyWidget::getFogEnd() {
	return  fogWidget->getFogEnd();
}

int PropertyWidget::getFogColorR() {
	return  fogWidget->getFogColorR();
}

int PropertyWidget::getFogColorG() {
	return  fogWidget->getFogColorG();
}

int PropertyWidget::getFogColorB() {
	return  fogWidget->getFogColorB();
}

int PropertyWidget::getColorR() {
	int colorR;
	switch (m_type) {
	case My_Cube:
		colorR = cubeWidget->getColorR();
		break;
	case My_Sphere:
		colorR = sphereWidget->getColorR();
		break;
	}
	return  colorR;
}

int PropertyWidget::getColorG() {
	int colorG;
	switch (m_type) {
	case My_Cube:
		colorG = cubeWidget->getColorG();
		break;
	case My_Sphere:
		colorG = sphereWidget->getColorG();
		break;
	}
	return  colorG;
}

int PropertyWidget::getColorB() {
	int colorB;
	switch (m_type) {
	case My_Cube:
		colorB = cubeWidget->getColorB();
		break;
	case My_Sphere:
		colorB = sphereWidget->getColorB();
		break;
	}
	return  colorB;
}

int PropertyWidget::getLightColorR() {
	return  lightWidget->getColorR();
}

int PropertyWidget::getLightColorG() {
	return  lightWidget->getColorG();
}

int PropertyWidget::getLightColorB() {
	return  lightWidget->getColorB();
}

int PropertyWidget::getLightType() {
	return  lightWidget->getLightType();
}

QString PropertyWidget::get_up_name() {
	return buttonWidget->get_up_name();
}

QString PropertyWidget::get_down_name() {
	return buttonWidget->get_down_name();
}

QString PropertyWidget::get_move_name() {
	return buttonWidget->get_move_name();
}

int PropertyWidget::getTextColorR() {
	return textWidget->getColorR();
}

int PropertyWidget::getTextColorG() {
	return textWidget->getColorG();
}

int PropertyWidget::getTextColorB() {
	return textWidget->getColorB();
}

QString PropertyWidget::getText() {
	return textWidget->getText();
}

QString PropertyWidget::getXModelFile() {
	return xModelWidget->getFileName();
}

int PropertyWidget::getScaleX() {
	int value = 0;
	switch (m_type) {
	case My_xModel:
		value = xModelWidget->getScaleX();
		break;
	case My_Cube:
		value = cubeWidget->getScaleX();
		break;
	case My_Sphere:
		value = sphereWidget->getScaleX();
		break;
	}
	return value;
}

int PropertyWidget::getScaleY() {
	int value = 0;
	switch (m_type) {
	case My_xModel:
		value = xModelWidget->getScaleY();
		break;
	case My_Cube:
		value = cubeWidget->getScaleY();
		break;
	case My_Sphere:
		value = sphereWidget->getScaleY();
		break;
	}
	return value;
}

int PropertyWidget::getScaleZ() {
	int value = 0;
	switch (m_type) {
	case My_xModel:
		value = xModelWidget->getScaleZ();
		break;
	case My_Cube:
		value = cubeWidget->getScaleZ();
		break;
	case My_Sphere:
		value = sphereWidget->getScaleZ();
		break;
	}
	return value;
}

void PropertyWidget::setPosX(int x) {
	switch (m_type) {
	case EmptyObject:
		break;
	case My_Camera:
		cameraWidget->setPosX(x);
		break;
	case My_Light:
		lightWidget->setPosX(x);
		break;
	case My_Particle:
		particleWidget->setPosX(x);
		break;
	case My_xModel:
		xModelWidget->setPosX(x);
		break;
	case My_Cube:
		cubeWidget->setPosX(x);
		break;
	case My_Sphere:
		sphereWidget->setPosX(x);
		break;
	case My_Sprite:
		spriteWidget->setPosX(x);
		break;
	case My_Button:
		buttonWidget->setPosX(x);
		break;
	case My_Text:
		textWidget->setPosX(x);
		break;
	default:

		break;
	}
}

void PropertyWidget::setPosY(int y) {
	switch (m_type) {
	case EmptyObject:
		break;
	case My_Camera:
		cameraWidget->setPosY(y);
		break;
	case My_Light:
		lightWidget->setPosY(y);
		break;
	case My_Particle:
		particleWidget->setPosY(y);
		break;
	case My_xModel:
		xModelWidget->setPosY(y);
		break;
	case My_Cube:
		cubeWidget->setPosY(y);
		break;
	case My_Sphere:
		sphereWidget->setPosY(y);
		break;
	case My_Sprite:
		spriteWidget->setPosY(y);
		break;
	case My_Button:
		buttonWidget->setPosY(y);
		break;
	case My_Text:
		textWidget->setPosY(y);
		break;
	default:

		break;
	}
}

void PropertyWidget::setPosZ(int z) {
	switch (m_type) {
	case EmptyObject:
		break;
	case My_Camera:
		cameraWidget->setPosZ(z);
		break;
	case My_Light:
		lightWidget->setPosZ(z);
		break;
	case My_Particle:
		particleWidget->setPosZ(z);
		break;
	case My_xModel:
		xModelWidget->setPosZ(z);
		break;
	case My_Cube:
		cubeWidget->setPosZ(z);
		break;
	case My_Sphere:
		sphereWidget->setPosZ(z);
		break;
	default:

		break;
	}
}

void PropertyWidget::setRotX(int x) {
	switch (m_type) {
	case EmptyObject:
		break;
	case My_Light:
		lightWidget->setRotX(x);
		break;
	case My_xModel:
		xModelWidget->setRotX(x);
		break;
	case My_Cube:
		cubeWidget->setRotX(x);
		break;
	case My_Sphere:
		sphereWidget->setRotX(x);
		break;
	default:

		break;
	}
}

void PropertyWidget::setRotY(int y) {
	switch (m_type) {
	case EmptyObject:
		break;
	case My_Light:
		lightWidget->setRotY(y);
		break;
	case My_xModel:
		xModelWidget->setRotY(y);
		break;
	case My_Cube:
		cubeWidget->setRotY(y);
		break;
	case My_Sphere:
		sphereWidget->setRotY(y);
		break;
	default:

		break;
	}
}

void PropertyWidget::setRotZ(int z) {
	switch (m_type) {
	case EmptyObject:
		break;
	case My_Light:
		lightWidget->setRotZ(z);
		break;
	case My_xModel:
		xModelWidget->setRotZ(z);
		break;
	case My_Cube:
		cubeWidget->setRotZ(z);
		break;
	case My_Sphere:
		sphereWidget->setRotZ(z);
		break;
	default:

		break;
	}
}

void PropertyWidget::setCameraType(int type) {
	cameraWidget->setCameraType(type);
}

void PropertyWidget::setSpeed(int speed) {
	cameraWidget->setSpeed(speed);
}

void PropertyWidget::setSkyBoxLength(int length) {
	if (skyboxWidget)
		skyboxWidget->setSkyBoxLength(length);
}

void PropertyWidget::setSkyBoxFront(QString front) {
	if (skyboxWidget)
		skyboxWidget->setSkyBoxFront(front);
}

void PropertyWidget::setSkyBoxBack(QString back) {
	if (skyboxWidget)
		skyboxWidget->setSkyBoxBack(back);
}

void PropertyWidget::setSkyBoxLeft(QString left) {
	if (skyboxWidget)
		skyboxWidget->setSkyBoxLeft(left);
}

void PropertyWidget::setSkyBoxRight(QString right) {
	if (skyboxWidget)
		skyboxWidget->setSkyBoxRight(right);
}

void PropertyWidget::setSkyBoxTop(QString top) {
	if (skyboxWidget)
		skyboxWidget->setSkyBoxTop(top);
}

void PropertyWidget::setFogType(int type) {
	fogWidget->setFogType(type);
}

void PropertyWidget::setFogStart(int start) {
	fogWidget->setFogStart(start);
}

void PropertyWidget::setFogEnd(int end) {
	fogWidget->setFogEnd(end);
}

void PropertyWidget::setFogColorR(int r) {
	fogWidget->setFogColorR(r);
}

void PropertyWidget::setFogColorG(int g) {
	fogWidget->setFogColorG(g);
}

void PropertyWidget::setFogColorB(int b) {
	fogWidget->setFogColorB(b);
}

void PropertyWidget::setColorR(int r) {
	switch (m_type) {
	case My_Cube:
		cubeWidget->setColorR(r);
		break;
	case My_Sphere:
		sphereWidget->setColorR(r);
		break;
	}
}

void PropertyWidget::setColorG(int g) {
	switch (m_type) {
	case My_Cube:
		cubeWidget->setColorG(g);
		break;
	case My_Sphere:
		sphereWidget->setColorG(g);
		break;
	}
}

void PropertyWidget::setColorB(int b) {
	switch (m_type) {
	case My_Cube:
		cubeWidget->setColorB(b);
		break;
	case My_Sphere:
		sphereWidget->setColorB(b);
		break;
	}
}

void PropertyWidget::setLightColorR(int r) {
	lightWidget->setColorR(r);
}

void PropertyWidget::setLightColorG(int g) {
	lightWidget->setColorG(g);
}

void PropertyWidget::setLightColorB(int b) {
	lightWidget->setColorB(b);
}

void PropertyWidget::setLightType(int type) {
	lightWidget->setLightType(type);
}

void PropertyWidget::set_up_name(QString up) {
	buttonWidget->set_up_name(up);
}

void PropertyWidget::set_down_name(QString down) {
	buttonWidget->set_down_name(down);
}

void PropertyWidget::set_move_name(QString move) {
	buttonWidget->set_move_name(move);
}

void PropertyWidget::setTextColorR(int r) {
	textWidget->setColorR(r);
}

void PropertyWidget::setTextColorG(int g) {
	textWidget->setColorG(g);
}

void PropertyWidget::setTextColorB(int b) {
	textWidget->setColorB(b);
}

void PropertyWidget::setText(QString text) {
	textWidget->setText(text);
}

void PropertyWidget::setXModelFile(QString fileName) {
	if (fileName == "") {
		
		return;
	}
	xModelWidget->setFileName(fileName);
}

void PropertyWidget::setScaleX(int x) {
	switch (m_type) {
	case My_xModel:
		xModelWidget->setScaleX(x);
		break;
	case My_Cube:
		cubeWidget->setScaleX(x);
		break;
	case My_Sphere:
		sphereWidget->setScaleX(x);
		break;
	}
}

void PropertyWidget::setScaleY(int y) {
	switch (m_type) {
	case My_xModel:
		xModelWidget->setScaleY(y);
		break;
	case My_Cube:
		cubeWidget->setScaleY(y);
		break;
	case My_Sphere:
		sphereWidget->setScaleY(y);
		break;
	}
}

void PropertyWidget::setScaleZ(int z) {
	switch (m_type) {
	case My_xModel:
		xModelWidget->setScaleZ(z);
		break;
	case My_Cube:
		cubeWidget->setScaleZ(z);
		break;
	case My_Sphere:
		sphereWidget->setScaleZ(z);
		break;
	}
}


void PropertyWidget::do_btn_ok_click() {
	
	QString name;
	switch (m_type) {
	case EmptyObject:
		
		break;
	case My_Camera:
		name = u8"wCamera";
		if (worldCamera.size() == 0) {
			//创建对象
			m_cam = new Pro_Camera();
			m_cam->posX = cameraWidget->getPosX();
			m_cam->posY = cameraWidget->getPosY();
			m_cam->posZ = cameraWidget->getPosZ();
			m_cam->speed = cameraWidget->getSpeed();
			m_cam->type = cameraWidget->getCameraType();
			//加入静态物体列表
			worldCamera.insert({ name ,*m_cam });
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Camera);
			SAFE_DELETE(m_ini_file);
		} else {
			//修改属性
			m_cam = &(*worldCamera.find(name)).second;
			m_cam->posX = cameraWidget->getPosX();
			m_cam->posY = cameraWidget->getPosY();
			m_cam->posZ = cameraWidget->getPosZ();
			m_cam->speed = cameraWidget->getSpeed();
			m_cam->type = cameraWidget->getCameraType();
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Camera);
			SAFE_DELETE(m_ini_file);
		}

		break;
	case My_SkyBox:
		name = u8"wSkyBox";
		if (worldSkyBox.size() == 0) {
			//创建对象
			m_skybox = new Pro_SkyBox();
			m_skybox->length = skyboxWidget->getSkyBoxLength();
			m_skybox->skyBack = skyboxWidget->getSkyBoxBack();
			m_skybox->skyFront = skyboxWidget->getSkyBoxFront();
			m_skybox->skyLeft = skyboxWidget->getSkyBoxLeft();
			m_skybox->skyRight = skyboxWidget->getSkyBoxRight();
			m_skybox->skyTop = skyboxWidget->getSkyBoxTop();
			//加入静态物体列表
			worldSkyBox.insert({ name ,*m_skybox });
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_SkyBox);
		} else{
			//修改属性
			m_skybox = &(*worldSkyBox.find(name)).second;
			m_skybox->length = skyboxWidget->getSkyBoxLength();
			m_skybox->skyBack = skyboxWidget->getSkyBoxBack();
			m_skybox->skyFront = skyboxWidget->getSkyBoxFront();
			m_skybox->skyLeft = skyboxWidget->getSkyBoxLeft();
			m_skybox->skyRight = skyboxWidget->getSkyBoxRight();
			m_skybox->skyTop = skyboxWidget->getSkyBoxTop();
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_SkyBox);
			
		}
		break;
	case My_Terrain:
		name = u8"wTerrain";
		if (worldTerrain.size() == 0) {
			//创建对象
			m_terrain = new Pro_Terrain();
			m_terrain->rawFileName = terrainWidget->getRawFileName();
			m_terrain->fileName = terrainWidget->getFileName();
			m_terrain->cellSpacing = terrainWidget->getCellSpacing();
			m_terrain->numVertsPerCol = terrainWidget->getNumVertsPerCol();
			m_terrain->numVertsPerRow = terrainWidget->getNumVertsPerRow();
			m_terrain->heightScale = terrainWidget->getHeightScale();
			//加入静态物体列表
			worldTerrain.insert({ name ,*m_terrain });
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Terrain);
			SAFE_DELETE(m_ini_file);
		} else{
			m_terrain = &(*worldTerrain.find(name)).second;
			m_terrain->rawFileName = terrainWidget->getRawFileName();
			m_terrain->fileName = terrainWidget->getFileName();
			m_terrain->cellSpacing = terrainWidget->getCellSpacing();
			m_terrain->numVertsPerCol = terrainWidget->getNumVertsPerCol();
			m_terrain->numVertsPerRow = terrainWidget->getNumVertsPerRow();
			m_terrain->heightScale = terrainWidget->getHeightScale();
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Terrain);
			SAFE_DELETE(m_ini_file);
		}
		break;
	case My_Light:
		name = lightWidget->getName();
		emit(list_change_name(name, m_type));
		if (worldLight.find(name) == worldLight.end()) {
			//创建对象
			m_light = new Pro_Light();
			
		}
		else {
			m_light = &(*worldLight.find(name)).second;
		
		}
		m_light->type = lightWidget->getLightType();
		m_light->posX = lightWidget->getPosX();
		m_light->posY = lightWidget->getPosY();
		m_light->posZ = lightWidget->getPosZ();
		m_light->rotX = lightWidget->getRotX();
		m_light->posY = lightWidget->getRotY();
		m_light->rotZ = lightWidget->getRotZ();
		m_light->colorR = lightWidget->getColorR();
		m_light->colorG = lightWidget->getColorG();
		m_light->colorB = lightWidget->getColorB();
		if (worldLight.find(name) == worldLight.end()) {
			//加入静态物体列表
			worldLight.insert({ name ,*m_light });
		}
		//写入脚本文件中
		m_ini_file = new IniFile();
		m_ini_file->add_object_ini(name, My_Light);
		SAFE_DELETE(m_ini_file);
		break;
	case My_Particle:
		name = particleWidget->getName();
		emit(list_change_name(name, m_type));

		if (worldParticle.find(name) == worldParticle.end()) {
			//创建对象
			m_particle = new Pro_Particle();
			m_particle->fileName = particleWidget->getFileName();
			m_particle->type = particleWidget->getType();
			m_particle->height = particleWidget->getHeight();
			m_particle->length = particleWidget->getLength();
			m_particle->num = particleWidget->getNum();
			m_particle->width = particleWidget->getWidth();
			m_particle->postion.x = particleWidget->getPosX();
			m_particle->postion.y = particleWidget->getPosY();
			m_particle->postion.z = particleWidget->getPosZ();
			//加入静态物体列表
			worldParticle.insert({ name ,*m_particle });
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Particle);
			SAFE_DELETE(m_ini_file);
		}
		else {
			m_particle = &(*worldParticle.find(name)).second;
			m_particle->fileName = particleWidget->getFileName();
			m_particle->type = particleWidget->getType();
			m_particle->height = particleWidget->getHeight();
			m_particle->length = particleWidget->getLength();
			m_particle->num = particleWidget->getNum();
			m_particle->width = particleWidget->getWidth();
			m_particle->postion.x = particleWidget->getPosX();
			m_particle->postion.y = particleWidget->getPosY();
			m_particle->postion.z = particleWidget->getPosZ();
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Particle);
			SAFE_DELETE(m_ini_file);
		}
		break;
	case My_Fog:
		name = u8"wFog";
		if (worldFog.size() == 0) {
			//创建对象
			m_fog = new Pro_Fog();
			m_fog->type = fogWidget->getFogType();
			m_fog->start = fogWidget->getFogStart();
			m_fog->end = fogWidget->getFogEnd();
			m_fog->color_r = fogWidget->getFogColorR();
			m_fog->color_g = fogWidget->getFogColorG();
			m_fog->color_b = fogWidget->getFogColorB();
			//加入静态物体列表
			worldFog.insert({ name ,*m_fog });
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Fog);
			SAFE_DELETE(m_ini_file);
		}
		else {
			m_fog = &(*worldFog.find(name)).second;
			m_fog->type = fogWidget->getFogType();
			m_fog->start = fogWidget->getFogStart();
			m_fog->end = fogWidget->getFogEnd();
			m_fog->color_r = fogWidget->getFogColorR();
			m_fog->color_g = fogWidget->getFogColorG();
			m_fog->color_b = fogWidget->getFogColorB();
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Fog);
			SAFE_DELETE(m_ini_file);
		}
		break;
	case My_Sprite:
		name = spriteWidget->getName();
		emit(list_change_name(name, m_type));
		if (worldSprite.find(name) == worldSprite.end()) {
			//创建对象
			m_sprite = new Pro_Sprite();
			m_sprite->fileName = spriteWidget->getFileName();
			m_sprite->posX = spriteWidget->getPosX();
			m_sprite->posY = spriteWidget->getPosY();
			//加入静态物体列表
			worldSprite.insert({ name ,*m_sprite });
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Sprite);
			SAFE_DELETE(m_ini_file);
		}
		else {
			m_sprite = &(*worldSprite.find(name)).second;
			m_sprite->fileName = spriteWidget->getFileName();
			m_sprite->posX = spriteWidget->getPosX();
			m_sprite->posY = spriteWidget->getPosY();
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Sprite);
			SAFE_DELETE(m_ini_file);
		}
		break;
	case My_Button:
		name = buttonWidget->getName();
		emit(list_change_name(name, m_type));
		if (worldButton.find(name) == worldButton.end()) {
			//创建对象
			m_button = new Pro_Button();
			m_button->fileNameUp = buttonWidget->get_up_name();
			m_button->fileNameDown = buttonWidget->get_down_name();
			m_button->fileNameMove = buttonWidget->get_move_name();
			m_button->posX = buttonWidget->getPosX();
			m_button->posY = buttonWidget->getPosY();
			//加入静态物体列表
			worldButton.insert({ name ,*m_button });
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Button);
			SAFE_DELETE(m_ini_file);
		}
		else {
			m_button = &(*worldButton.find(name)).second;
			m_button->fileNameUp = buttonWidget->get_up_name();
			m_button->fileNameDown = buttonWidget->get_down_name();
			m_button->fileNameMove = buttonWidget->get_move_name();
			m_button->posX = buttonWidget->getPosX();
			m_button->posY = buttonWidget->getPosY();
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Button);
			SAFE_DELETE(m_ini_file);
		}
		break;
	case My_Text:
		name = textWidget->getName();
		emit(list_change_name(name, m_type));
		if (worldText.find(name) == worldText.end()) {
			//创建对象
			m_text = new Pro_Text();
			m_text->text = textWidget->getText();
			m_text->posX = textWidget->getPosX();
			m_text->posY = textWidget->getPosY();
			m_text->colorR = textWidget->getColorR();
			m_text->colorG = textWidget->getColorG();
			m_text->colorB = textWidget->getColorB();

			//加入静态物体列表
			worldText.insert({ name ,*m_text });
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Text);
			SAFE_DELETE(m_ini_file);
		}
		else {
			m_text = &(*worldText.find(name)).second;
			m_text->text = textWidget->getText();
			m_text->posX = textWidget->getPosX();
			m_text->posY = textWidget->getPosY();
			m_text->colorR = textWidget->getColorR();
			m_text->colorG = textWidget->getColorG();
			m_text->colorB = textWidget->getColorB();
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Text);
			SAFE_DELETE(m_ini_file);
		}
		break;
	case My_xModel:
		name = xModelWidget->getName();
		emit(list_change_name(name, m_type));
		if (worldxModel.find(name) == worldxModel.end()) {
			//创建对象
			m_xmodel = new Pro_xModel();
			m_xmodel->fileName = xModelWidget->getFileName();
			if (m_xmodel->fileName == "") {
				g_gameLog->AppendLog("[错误：]未输入正确的文件名");
				
			}
			m_xmodel->rotX = xModelWidget->getRotX();
			m_xmodel->rotY = xModelWidget->getRotY();
			m_xmodel->rotZ = xModelWidget->getRotZ();
			m_xmodel->scaleX = xModelWidget->getScaleX();
			m_xmodel->scaleY = xModelWidget->getScaleY();
			m_xmodel->scaleZ = xModelWidget->getScaleZ();
			m_xmodel->posX = xModelWidget->getPosX();
			m_xmodel->posY = xModelWidget->getPosY();
			m_xmodel->posZ = xModelWidget->getPosZ();
			//加入静态物体列表
			worldxModel.insert({ name ,*m_xmodel });
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_xModel);
			SAFE_DELETE(m_ini_file);
		}
		else {
			m_xmodel = &(*worldxModel.find(name)).second;
			m_xmodel->fileName = xModelWidget->getFileName();
			if (m_xmodel->fileName == "") {
				g_gameLog->AppendLog("[错误：]未输入正确的文件名");
				return;
			}
			m_xmodel->rotX = xModelWidget->getRotX();
			m_xmodel->rotY = xModelWidget->getRotY();
			m_xmodel->rotZ = xModelWidget->getRotZ();
			m_xmodel->scaleX = xModelWidget->getScaleX();
			m_xmodel->scaleY = xModelWidget->getScaleY();
			m_xmodel->scaleZ = xModelWidget->getScaleZ();
			m_xmodel->posX = xModelWidget->getPosX();
			m_xmodel->posY = xModelWidget->getPosY();
			m_xmodel->posZ = xModelWidget->getPosZ();
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_xModel);
			SAFE_DELETE(m_ini_file);
		}
		break;
	case My_Cube:
		name = cubeWidget->getName();
		emit(list_change_name(name, m_type));
		if (worldCube.find(name) == worldCube.end()) {
			//创建对象
			m_cube = new Pro_Cube();
			m_cube->rotX = cubeWidget->getRotX();
			m_cube->rotY = cubeWidget->getRotY();
			m_cube->rotZ = cubeWidget->getRotZ();
			m_cube->scaleX = cubeWidget->getScaleX();
			m_cube->scaleY = cubeWidget->getScaleY();
			m_cube->scaleZ = cubeWidget->getScaleZ();
			m_cube->posX = cubeWidget->getPosX();
			m_cube->posY = cubeWidget->getPosY();
			m_cube->posZ = cubeWidget->getPosZ();
			//加入静态物体列表
			worldCube.insert({ name ,*m_cube });
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Cube);
			SAFE_DELETE(m_ini_file);
		}
		else {
			m_cube = &(*worldCube.find(name)).second;
			m_cube->rotX = cubeWidget->getRotX();
			m_cube->rotY = cubeWidget->getRotY();
			m_cube->rotZ = cubeWidget->getRotZ();
			m_cube->scaleX = cubeWidget->getScaleX();
			m_cube->scaleY = cubeWidget->getScaleY();
			m_cube->scaleZ = cubeWidget->getScaleZ();
			m_cube->posX = cubeWidget->getPosX();
			m_cube->posY = cubeWidget->getPosY();
			m_cube->posZ = cubeWidget->getPosZ();
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Cube);
			SAFE_DELETE(m_ini_file);
		}
		break;
	case My_Sphere:
		name = sphereWidget->getName();
		emit(list_change_name(name, m_type));
		if (worldSphere.find(name) == worldSphere.end()) {
			//创建对象
			m_sphere = new Pro_Sphere();
			m_sphere->rotX = sphereWidget->getRotX();
			m_sphere->rotY = sphereWidget->getRotY();
			m_sphere->rotZ = sphereWidget->getRotZ();
			m_sphere->scaleX = sphereWidget->getScaleX();
			m_sphere->scaleY = sphereWidget->getScaleY();
			m_sphere->scaleZ = sphereWidget->getScaleZ();
			m_sphere->posX = sphereWidget->getPosX();
			m_sphere->posY = sphereWidget->getPosY();
			m_sphere->posZ = sphereWidget->getPosZ();
			//加入静态物体列表
			worldSphere.insert({ name ,*m_sphere });
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Sphere);
			SAFE_DELETE(m_ini_file);
		}
		else {
			m_sphere = &(*worldSphere.find(name)).second;
			m_sphere->rotX = sphereWidget->getRotX();
			m_sphere->rotY = sphereWidget->getRotY();
			m_sphere->rotZ = sphereWidget->getRotZ();
			m_sphere->scaleX = sphereWidget->getScaleX();
			m_sphere->scaleY = sphereWidget->getScaleY();
			m_sphere->scaleZ = sphereWidget->getScaleZ();
			m_sphere->posX = sphereWidget->getPosX();
			m_sphere->posY = sphereWidget->getPosY();
			m_sphere->posZ = sphereWidget->getPosZ();
			//写入脚本文件中
			m_ini_file = new IniFile();
			m_ini_file->add_object_ini(name, My_Sphere);
			SAFE_DELETE(m_ini_file);
		}
		break;
	}
	emit(obj_change_pro(name));
}

QString PropertyWidget::getRawFileName() {
	return terrainWidget->getRawFileName();
}

QString PropertyWidget::getFileName() {
	QString name="";
	switch (m_type) {
	case My_Particle:
		name = particleWidget->getFileName();
		break;
	case My_Terrain:
		name = terrainWidget->getFileName();
		break;
	default:

		break;
	}
	return name;
}

int PropertyWidget::getNumVertsPerRow() {
	return terrainWidget->getNumVertsPerRow();
}

int PropertyWidget::getNumVertsPerCol() {
	return terrainWidget->getNumVertsPerCol();
}

int PropertyWidget::getCellSpacing() {
	return terrainWidget->getCellSpacing();
}

float PropertyWidget::getHeightScale() {
	return terrainWidget->getHeightScale();
}

void PropertyWidget::setFileName(QString name) {
	if (name == "") {
		g_gameLog->AppendLog("[错误：]未输入正确的文件名");
		return;
	}
	switch (m_type) {
	case My_Particle:
		particleWidget->setFileName(name);
		break;
	case My_Terrain:
		terrainWidget->setFileName(name);
		break;
	case My_Sprite:
		spriteWidget->setFileName(name);
		break;
	case My_xModel:		
		xModelWidget->setFileName(name);
		break;
	default:

		break;
	}
	
}

void PropertyWidget::setNumVertsPerRow(int numVertsPerRow) {
	terrainWidget->setNumVertsPerRow(numVertsPerRow);
}

void PropertyWidget::setNumVertsPerCol(int numVertsPerCol) {
	terrainWidget->setNumVertsPerCol(numVertsPerCol);
}

void PropertyWidget::setCellSpacing(int cellSpacing) {
	terrainWidget->setCellSpacing(cellSpacing);
}

void PropertyWidget::setRawFileName(QString name) {
	terrainWidget->setRawFileName(name);
}

void PropertyWidget::setHeightScale(float heightScale) {
	terrainWidget->setHeightScale(heightScale);
}

int PropertyWidget::getLength() {
	return particleWidget->getLength();
}

int PropertyWidget::getWidth() {
	return particleWidget->getWidth();
}

int PropertyWidget::getHeight() {
	return particleWidget->getHeight();
}

int PropertyWidget::getNum() {
	return particleWidget->getNum();
}

int PropertyWidget::getParType() {
	return particleWidget->getType();
}


void PropertyWidget::setLength(int length) {
	particleWidget->setLength(length);
}

void PropertyWidget::setWidth(int width) {
	particleWidget->setWidth(width);
}

void PropertyWidget::setHeight(int height) {
	particleWidget->setHeight(height);
}

void PropertyWidget::setNum(int num) {
	particleWidget->setNum(num);
}

void PropertyWidget::setParType(int type) {
	particleWidget->setType(type);
}


void PropertyWidget::setName(QString name) {
	switch (m_type) {
	case My_Light:
		lightWidget->setName(name);
		break;
	case My_Particle:
		particleWidget->setName(name);
		break;
	case My_Sprite:
		spriteWidget->setName(name);
		break;
	case My_Button:
		buttonWidget->setName(name);
		break;
	case My_Text:
		textWidget->setName(name);
		break;
	case My_xModel:
		xModelWidget->setName(name);
		break;
	case My_Cube:
		cubeWidget->setName(name);
		break;
	case My_Sphere:
		sphereWidget->setName(name);
		break;
	}
}

QString PropertyWidget::getName() {
	QString name;
	switch (m_type) {
	case My_Light:
		name = lightWidget->getName();
		break;
	case My_Particle:
		name = particleWidget->getName();
		break;
	case My_Sprite:
		name = spriteWidget->getName();
		break;
	case My_Button:
		name = buttonWidget->getName();
		break;
	case My_Text:
		name = textWidget->getName();
		break;
	case My_xModel:
		name = xModelWidget->getName();
		break;
	case My_Cube:
		name = cubeWidget->getName();
		break;
	case My_Sphere:
		name = sphereWidget->getName();
		break;
	}
	return name;
}




