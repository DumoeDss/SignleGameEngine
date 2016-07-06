#include "Inifile.h"
#include "defines.h"
#include "mainwindow.h"
#include "gameEngine.h"
IniFile::IniFile():ObjectList(0), ObjectPro(0),cam(0), skybox(0),
	terrain(0), light(0), particle(0), fog(0), sprite(0), button(0), 
	text(0), xModel(0), cube(0), sphere(0){

}

IniFile::~IniFile() {
	SAFE_DELETE(ObjectList);
	SAFE_DELETE(ObjectPro);
}

void IniFile::process_object_ini() {
	ObjectList = new QSettings(SYS_CONFIG, QSettings::IniFormat);
	ObjectPro = new QSettings(SYS_CONFIG, QSettings::IniFormat);
	//获取游戏对象列表
	ObjectList->beginGroup("Object");
	//获取游戏对象名字列表
	objNameList = ObjectList->allKeys();
	for (auto obj : objNameList) {	
		//创建游戏对象类型列表
		objTypeList.push_back(ObjectList->value(obj).toInt());
	}
	//遍历游戏对象列表,将游戏对象添加到静态游戏对象列表中
	for (int i = 0; i != objNameList.size(); ++i) {
		switch (objTypeList[i]) {
		case 1:	//My_Camera
			if (worldCamera.find(objNameList[i]) == worldCamera.end()) {
				cam = new Pro_Camera();
			}
			else {
				cam = &(*worldCamera.find(objNameList[i])).second;
			}				
			ObjectPro->beginGroup(objNameList[i]);
			cam->posX = ObjectPro->value("posX").toInt();
			cam->posY = ObjectPro->value("posY").toInt();
			cam->posZ = ObjectPro->value("posZ").toInt();
			cam->speed = ObjectPro->value("speed").toInt();
			cam->type = ObjectPro->value("type").toInt();
			ObjectPro->endGroup();
			if (worldCamera.find(objNameList[i]) == worldCamera.end()) {
				worldCamera.insert({ objNameList[i],*cam });
			}			
			break;
		case 2:	//My_SkyBox
			if (worldSkyBox.find(objNameList[i]) == worldSkyBox.end()) {
				skybox = new Pro_SkyBox();
			}
			else {
				skybox = &(*worldSkyBox.find(objNameList[i])).second;
			}
			
			ObjectPro->beginGroup(objNameList[i]);
			skybox->length = ObjectPro->value("length").toInt();
			skybox->skyFront = ObjectPro->value("skyFront").toString();
			skybox->skyBack = ObjectPro->value("skyBack").toString();
			skybox->skyLeft = ObjectPro->value("skyLeft").toString();
			skybox->skyRight = ObjectPro->value("skyRight").toString();
			skybox->skyTop = ObjectPro->value("skyTop").toString();
			ObjectPro->endGroup();
			if (worldSkyBox.find(objNameList[i]) == worldSkyBox.end()) {
				worldSkyBox.insert({ objNameList[i],*skybox });
			}
			break;
		case 3:	//My_Terrain
			if (worldTerrain.find(objNameList[i]) == worldTerrain.end()) {
				terrain = new Pro_Terrain();
			}
			else {
				terrain = &(*worldTerrain.find(objNameList[i])).second;
			}
			
			ObjectPro->beginGroup(objNameList[i]);
			terrain->rawFileName = ObjectPro->value("rawFileName").toString();
			terrain->fileName = ObjectPro->value("fileName").toString();
			terrain->numVertsPerCol = ObjectPro->value("numVertsPerCol").toInt();
			terrain->numVertsPerRow = ObjectPro->value("numVertsPerRow").toInt();
			terrain->cellSpacing = ObjectPro->value("cellSpacing").toInt();
			terrain->heightScale = ObjectPro->value("heightScale").toFloat();
			ObjectPro->endGroup();
			if (worldTerrain.find(objNameList[i]) == worldTerrain.end()) {
				worldTerrain.insert({ objNameList[i],*terrain });
			}
			break;
		case 4:	//My_Light
			if (worldLight.find(objNameList[i]) == worldLight.end()) {
				light = new Pro_Light();
			}
			else {
				light = &(*worldLight.find(objNameList[i])).second;
			}
			ObjectPro->beginGroup(objNameList[i]);
			light->type = ObjectPro->value("type").toInt();
			light->posX = ObjectPro->value("posX").toInt();
			light->posY = ObjectPro->value("posY").toInt();
			light->posZ = ObjectPro->value("posZ").toInt();
			light->rotX = ObjectPro->value("rotX").toInt();
			light->rotY = ObjectPro->value("rotY").toInt();
			light->rotZ = ObjectPro->value("rotZ").toInt();
			light->colorR = ObjectPro->value("colorR").toInt();
			light->colorG = ObjectPro->value("colorG").toInt();
			light->colorB = ObjectPro->value("colorB").toInt();
			ObjectPro->endGroup();
			if (worldLight.find(objNameList[i]) == worldLight.end()) {
				worldLight.insert({ objNameList[i],*light });
			}
			break;
		case 5:	//My_Particle
			if (worldParticle.find(objNameList[i]) == worldParticle.end()) {
				particle = new Pro_Particle();
			}
			else {
				particle = &(*worldParticle.find(objNameList[i])).second;
			}
			
			ObjectPro->beginGroup(objNameList[i]);
			particle->fileName = ObjectPro->value("fileName").toString();
			particle->height = ObjectPro->value("height").toInt();
			particle->length = ObjectPro->value("length").toInt();
			particle->width = ObjectPro->value("width").toInt();
			particle->num = ObjectPro->value("num").toInt();
			particle->type = ObjectPro->value("type").toInt();
			particle->postion.x = ObjectPro->value("posX").toInt();
			particle->postion.y = ObjectPro->value("posY").toInt();
			particle->postion.z = ObjectPro->value("posZ").toInt();
			ObjectPro->endGroup();
			if (worldParticle.find(objNameList[i]) == worldParticle.end()) {
				worldParticle.insert({ objNameList[i],*particle });
			}
			break;
		case 6:	//My_Fog
			if (worldFog.find(objNameList[i]) == worldFog.end()) {
				fog = new Pro_Fog();
			}
			else {
				fog = &(*worldFog.find(objNameList[i])).second;
			}
			
			ObjectPro->beginGroup(objNameList[i]);
			fog->type = ObjectPro->value("type").toInt();
			fog->start = ObjectPro->value("start").toInt();
			fog->end = ObjectPro->value("end").toInt();
			fog->color_r = ObjectPro->value("color_r").toInt();
			fog->color_g = ObjectPro->value("color_g").toInt();
			fog->color_b = ObjectPro->value("color_b").toInt();
			ObjectPro->endGroup();
			if (worldFog.find(objNameList[i]) == worldFog.end()) {
				worldFog.insert({ objNameList[i],*fog });
			}
			break;
		case 7:	//My_Sprite
			if (worldSprite.find(objNameList[i]) == worldSprite.end()) {
				sprite = new Pro_Sprite();
			}
			else {
				sprite = &(*worldSprite.find(objNameList[i])).second;
			}
			
			ObjectPro->beginGroup(objNameList[i]);
			sprite->posX = ObjectPro->value("posX").toInt();
			sprite->posY = ObjectPro->value("posY").toInt();
			sprite->fileName = ObjectPro->value("fileName").toString();
			ObjectPro->endGroup();
			if (worldSprite.find(objNameList[i]) == worldSprite.end()) {
				worldSprite.insert({ objNameList[i],*sprite });
			}
			break;
		case 8:	//My_Button
			if (worldButton.find(objNameList[i]) == worldButton.end()) {
				button = new Pro_Button();
			}
			else {
				button = &(*worldButton.find(objNameList[i])).second;
			}
			
			ObjectPro->beginGroup(objNameList[i]);
			button->posX = ObjectPro->value("posX").toInt();
			button->posY = ObjectPro->value("posY").toInt();
			button->fileNameUp = ObjectPro->value("fileNameUp").toString();
			button->fileNameDown = ObjectPro->value("fileNameDown").toString();
			button->fileNameMove = ObjectPro->value("fileNameMove").toString();
			ObjectPro->endGroup();
			if (worldButton.find(objNameList[i]) == worldButton.end()) {
				worldButton.insert({ objNameList[i],*button });
			}
			break;
		case 9:	//My_Text
			if (worldText.find(objNameList[i]) == worldText.end()) {
				text = new Pro_Text();
			}
			else {
				text = &(*worldText.find(objNameList[i])).second;
			}		
			ObjectPro->beginGroup(objNameList[i]);
			text->posX = ObjectPro->value("posX").toInt();
			text->posY = ObjectPro->value("posY").toInt();
			text->text = ObjectPro->value("text").toString();
			text->colorR = ObjectPro->value("colorR").toInt();
			text->colorG = ObjectPro->value("colorG").toInt();
			text->colorB = ObjectPro->value("colorB").toInt();
			ObjectPro->endGroup();
			if (worldText.find(objNameList[i]) == worldText.end()) {
				worldText.insert({ objNameList[i],*text });
			}
			break;
		case 10:	//My_xModel
			if (worldxModel.find(objNameList[i]) == worldxModel.end()) {
				xModel = new Pro_xModel();
			}
			else {
				xModel = &(*worldxModel.find(objNameList[i])).second;
			}			
			ObjectPro->beginGroup(objNameList[i]);
			xModel->posX = ObjectPro->value("posX").toInt();
			xModel->posY = ObjectPro->value("posY").toInt();
			xModel->posZ = ObjectPro->value("posZ").toInt();
			xModel->rotX = ObjectPro->value("rotX").toInt();
			xModel->rotY = ObjectPro->value("rotY").toInt();
			xModel->rotZ = ObjectPro->value("rotZ").toInt();
			xModel->scaleX = ObjectPro->value("scaleX").toFloat();
			xModel->scaleY = ObjectPro->value("scaleY").toFloat();
			xModel->scaleZ = ObjectPro->value("scaleZ").toFloat();
			xModel->fileName = ObjectPro->value("fileName").toString();
			ObjectPro->endGroup();
			if (worldxModel.find(objNameList[i]) == worldxModel.end()) {
				worldxModel.insert({ objNameList[i],*xModel });
			}
			break;
		case 11:	//My_Cube
			if (worldCube.find(objNameList[i]) == worldCube.end()) {
				cube = new Pro_Cube();
			}
			else {
				cube = &(*worldCube.find(objNameList[i])).second;
			}
			
			ObjectPro->beginGroup(objNameList[i]);
			cube->posX = ObjectPro->value("posX").toInt();
			cube->posY = ObjectPro->value("posY").toInt();
			cube->posZ = ObjectPro->value("posZ").toInt();
			cube->rotX = ObjectPro->value("rotX").toInt();
			cube->rotY = ObjectPro->value("rotY").toInt();
			cube->rotZ = ObjectPro->value("rotZ").toInt();
			cube->scaleX = ObjectPro->value("scaleX").toFloat();
			cube->scaleY = ObjectPro->value("scaleY").toFloat();
			cube->scaleZ = ObjectPro->value("scaleZ").toFloat();
			cube->colorR = ObjectPro->value("colorR").toFloat();
			cube->colorG = ObjectPro->value("colorG").toFloat();
			cube->colorB = ObjectPro->value("colorB").toFloat();
			ObjectPro->endGroup();
			if (worldCube.find(objNameList[i]) == worldCube.end()) {
				worldCube.insert({ objNameList[i],*cube });
			}
			break;
		case 12:	//My_Sphere
			if (worldSphere.find(objNameList[i]) == worldSphere.end()) {
				sphere = new Pro_Sphere();
			}
			else {
				sphere = &(*worldSphere.find(objNameList[i])).second;
			}			
			ObjectPro->beginGroup(objNameList[i]);
			sphere->posX = ObjectPro->value("posX").toInt();
			sphere->posY = ObjectPro->value("posY").toInt();
			sphere->posZ = ObjectPro->value("posZ").toInt();
			sphere->rotX = ObjectPro->value("rotX").toInt();
			sphere->rotY = ObjectPro->value("rotY").toInt();
			sphere->rotZ = ObjectPro->value("rotZ").toInt();
			sphere->scaleX = ObjectPro->value("scaleX").toFloat();
			sphere->scaleY = ObjectPro->value("scaleY").toFloat();
			sphere->scaleZ = ObjectPro->value("scaleZ").toFloat();
			sphere->colorR = ObjectPro->value("colorR").toInt();
			sphere->colorG = ObjectPro->value("colorG").toInt();
			sphere->colorB = ObjectPro->value("colorB").toInt();
			ObjectPro->endGroup();
			
			if (worldSphere.find(objNameList[i]) == worldSphere.end()) {
				worldSphere.insert({ objNameList[i],*sphere });
			}
			break;
		}
	}
	ObjectList->endGroup();
	SAFE_DELETE(ObjectPro);
	SAFE_DELETE(ObjectList);

}

int IniFile::process_object_ini(QString name) {
	ObjectList = new QSettings(SYS_CONFIG, QSettings::IniFormat);
	ObjectPro = new QSettings(SYS_CONFIG, QSettings::IniFormat);
	//获取游戏对象列表
	ObjectList->beginGroup("Object");
	//获取游戏对象名字列表
	int objType = ObjectList->value(name).toInt();

		switch (objType) {
		case 1:	//My_Camera
			if (worldCamera.find(name) == worldCamera.end()) {
				cam = new Pro_Camera();
			}
			else {
				cam = &(*worldCamera.find(name)).second;
			}
			ObjectPro->beginGroup(name);
			cam->posX = ObjectPro->value("posX").toInt();
			cam->posY = ObjectPro->value("posY").toInt();
			cam->posZ = ObjectPro->value("posZ").toInt();
			cam->speed = ObjectPro->value("speed").toInt();
			cam->type = ObjectPro->value("type").toInt();
			ObjectPro->endGroup();
			if (worldCamera.find(name) == worldCamera.end()) {
				worldCamera.insert({ name,*cam });
			}
			break;
		case 2:	//My_SkyBox
			if (worldSkyBox.find(name) == worldSkyBox.end()) {
				skybox = new Pro_SkyBox();
			}
			else {
				skybox = &(*worldSkyBox.find(name)).second;
			}

			ObjectPro->beginGroup(name);
			skybox->length = ObjectPro->value("length").toInt();
			skybox->skyFront = ObjectPro->value("skyFront").toString();
			skybox->skyBack = ObjectPro->value("skyBack").toString();
			skybox->skyLeft = ObjectPro->value("skyLeft").toString();
			skybox->skyRight = ObjectPro->value("skyRight").toString();
			skybox->skyTop = ObjectPro->value("skyTop").toString();
			ObjectPro->endGroup();
			if (worldSkyBox.find(name) == worldSkyBox.end()) {
				worldSkyBox.insert({ name,*skybox });
			}
			break;
		case 3:	//My_Terrain
			if (worldTerrain.find(name) == worldTerrain.end()) {
				terrain = new Pro_Terrain();
			}
			else {
				terrain = &(*worldTerrain.find(name)).second;
			}

			ObjectPro->beginGroup(name);
			terrain->rawFileName = ObjectPro->value("rawFileName").toString();
			terrain->fileName = ObjectPro->value("fileName").toString();
			terrain->numVertsPerCol = ObjectPro->value("numVertsPerCol").toInt();
			terrain->numVertsPerRow = ObjectPro->value("numVertsPerRow").toInt();
			terrain->cellSpacing = ObjectPro->value("cellSpacing").toInt();
			terrain->heightScale = ObjectPro->value("heightScale").toFloat();
			ObjectPro->endGroup();
			if (worldTerrain.find(name) == worldTerrain.end()) {
				worldTerrain.insert({ name,*terrain });
			}
			break;
		case 4:	//My_Light
			if (worldLight.find(name) == worldLight.end()) {
				light = new Pro_Light();
			}
			else {
				light = &(*worldLight.find(name)).second;
			}
			ObjectPro->beginGroup(name);
			light->type = ObjectPro->value("type").toInt();
			light->posX = ObjectPro->value("posX").toInt();
			light->posY = ObjectPro->value("posY").toInt();
			light->posZ = ObjectPro->value("posZ").toInt();
			light->rotX = ObjectPro->value("rotX").toInt();
			light->rotY = ObjectPro->value("rotY").toInt();
			light->rotZ = ObjectPro->value("rotZ").toInt();
			light->colorR = ObjectPro->value("colorR").toInt();
			light->colorG = ObjectPro->value("colorG").toInt();
			light->colorB = ObjectPro->value("colorB").toInt();
			ObjectPro->endGroup();
			if (worldLight.find(name) == worldLight.end()) {
				worldLight.insert({ name,*light });
			}
			break;
		case 5:	//My_Particle
			if (worldParticle.find(name) == worldParticle.end()) {
				particle = new Pro_Particle();
			}
			else {
				particle = &(*worldParticle.find(name)).second;
			}

			ObjectPro->beginGroup(name);
			particle->fileName = ObjectPro->value("fileName").toString();
			particle->height = ObjectPro->value("height").toInt();
			particle->length = ObjectPro->value("length").toInt();
			particle->width = ObjectPro->value("width").toInt();
			particle->num = ObjectPro->value("num").toInt();
			particle->type = ObjectPro->value("type").toInt();
			particle->postion.x = ObjectPro->value("posX").toInt();
			particle->postion.y = ObjectPro->value("posY").toInt();
			particle->postion.z = ObjectPro->value("posZ").toInt();
			ObjectPro->endGroup();
			if (worldParticle.find(name) == worldParticle.end()) {
				worldParticle.insert({ name,*particle });
			}
			break;
		case 6:	//My_Fog
			if (worldFog.find(name) == worldFog.end()) {
				fog = new Pro_Fog();
			}
			else {
				fog = &(*worldFog.find(name)).second;
			}

			ObjectPro->beginGroup(name);
			fog->type = ObjectPro->value("type").toInt();
			fog->start = ObjectPro->value("start").toInt();
			fog->end = ObjectPro->value("end").toInt();
			fog->color_r = ObjectPro->value("color_r").toInt();
			fog->color_g = ObjectPro->value("color_g").toInt();
			fog->color_b = ObjectPro->value("color_b").toInt();
			ObjectPro->endGroup();
			if (worldFog.find(name) == worldFog.end()) {
				worldFog.insert({ name,*fog });
			}
			break;
		case 7:	//My_Sprite
			if (worldSprite.find(name) == worldSprite.end()) {
				sprite = new Pro_Sprite();
			}
			else {
				sprite = &(*worldSprite.find(name)).second;
			}

			ObjectPro->beginGroup(name);
			sprite->posX = ObjectPro->value("posX").toInt();
			sprite->posY = ObjectPro->value("posY").toInt();
			sprite->fileName = ObjectPro->value("fileName").toString();
			ObjectPro->endGroup();
			if (worldSprite.find(name) == worldSprite.end()) {
				worldSprite.insert({ name,*sprite });
			}
			break;
		case 8:	//My_Button
			if (worldButton.find(name) == worldButton.end()) {
				button = new Pro_Button();
			}
			else {
				button = &(*worldButton.find(name)).second;
			}

			ObjectPro->beginGroup(name);
			button->posX = ObjectPro->value("posX").toInt();
			button->posY = ObjectPro->value("posY").toInt();
			button->fileNameUp = ObjectPro->value("fileNameUp").toString();
			button->fileNameDown = ObjectPro->value("fileNameDown").toString();
			button->fileNameMove = ObjectPro->value("fileNameMove").toString();
			ObjectPro->endGroup();
			if (worldButton.find(name) == worldButton.end()) {
				worldButton.insert({ name,*button });
			}
			break;
		case 9:	//My_Text
			if (worldText.find(name) == worldText.end()) {
				text = new Pro_Text();
			}
			else {
				text = &(*worldText.find(name)).second;
			}
			ObjectPro->beginGroup(name);
			text->posX = ObjectPro->value("posX").toInt();
			text->posY = ObjectPro->value("posY").toInt();
			text->text = ObjectPro->value("text").toString();
			text->colorR = ObjectPro->value("colorR").toInt();
			text->colorG = ObjectPro->value("colorG").toInt();
			text->colorB = ObjectPro->value("colorB").toInt();
			ObjectPro->endGroup();
			if (worldText.find(name) == worldText.end()) {
				worldText.insert({ name,*text });
			}
			break;
		case 10:	//My_xModel
			if (worldxModel.find(name) == worldxModel.end()) {
				xModel = new Pro_xModel();
			}
			else {
				xModel = &(*worldxModel.find(name)).second;
			}
			ObjectPro->beginGroup(name);
			xModel->posX = ObjectPro->value("posX").toInt();
			xModel->posY = ObjectPro->value("posY").toInt();
			xModel->posZ = ObjectPro->value("posZ").toInt();
			xModel->rotX = ObjectPro->value("rotX").toInt();
			xModel->rotY = ObjectPro->value("rotY").toInt();
			xModel->rotZ = ObjectPro->value("rotZ").toInt();
			xModel->scaleX = ObjectPro->value("scaleX").toFloat();
			xModel->scaleY = ObjectPro->value("scaleY").toFloat();
			xModel->scaleZ = ObjectPro->value("scaleZ").toFloat();
			xModel->fileName = ObjectPro->value("fileName").toString();
			ObjectPro->endGroup();
			if (worldxModel.find(name) == worldxModel.end()) {
				worldxModel.insert({ name,*xModel });
			}
			break;
		case 11:	//My_Cube
			if (worldCube.find(name) == worldCube.end()) {
				cube = new Pro_Cube();
			}
			else {
				cube = &(*worldCube.find(name)).second;
			}

			ObjectPro->beginGroup(name);
			cube->posX = ObjectPro->value("posX").toInt();
			cube->posY = ObjectPro->value("posY").toInt();
			cube->posZ = ObjectPro->value("posZ").toInt();
			cube->rotX = ObjectPro->value("rotX").toInt();
			cube->rotY = ObjectPro->value("rotY").toInt();
			cube->rotZ = ObjectPro->value("rotZ").toInt();
			cube->scaleX = ObjectPro->value("scaleX").toFloat();
			cube->scaleY = ObjectPro->value("scaleY").toFloat();
			cube->scaleZ = ObjectPro->value("scaleZ").toFloat();
			cube->colorR = ObjectPro->value("colorR").toFloat();
			cube->colorG = ObjectPro->value("colorG").toFloat();
			cube->colorB = ObjectPro->value("colorB").toFloat();
			ObjectPro->endGroup();
			if (worldCube.find(name) == worldCube.end()) {
				worldCube.insert({ name,*cube });
			}
			break;
		case 12:	//My_Sphere
			if (worldSphere.find(name) == worldSphere.end()) {
				sphere = new Pro_Sphere();
			}
			else {
				sphere = &(*worldSphere.find(name)).second;
			}
			ObjectPro->beginGroup(name);
			sphere->posX = ObjectPro->value("posX").toInt();
			sphere->posY = ObjectPro->value("posY").toInt();
			sphere->posZ = ObjectPro->value("posZ").toInt();
			sphere->rotX = ObjectPro->value("rotX").toInt();
			sphere->rotY = ObjectPro->value("rotY").toInt();
			sphere->rotZ = ObjectPro->value("rotZ").toInt();
			sphere->scaleX = ObjectPro->value("scaleX").toFloat();
			sphere->scaleY = ObjectPro->value("scaleY").toFloat();
			sphere->scaleZ = ObjectPro->value("scaleZ").toFloat();
			sphere->colorR = ObjectPro->value("colorR").toInt();
			sphere->colorG = ObjectPro->value("colorG").toInt();
			sphere->colorB = ObjectPro->value("colorB").toInt();
			ObjectPro->endGroup();

			if (worldSphere.find(name) == worldSphere.end()) {
				worldSphere.insert({ name,*sphere });
			}
			break;
		}
	
	ObjectList->endGroup();
	SAFE_DELETE(ObjectPro);
	SAFE_DELETE(ObjectList);
	return objType;
}

void IniFile::add_object_ini(QString objName, proType objType) {
	ObjectList = new QSettings(SYS_CONFIG, QSettings::IniFormat);
	ObjectPro = new QSettings(SYS_CONFIG, QSettings::IniFormat);
	switch (objType) {
	case My_Camera:
		cam = &(*worldCamera.find(objName)).second;
		ObjectList->beginGroup("Object");
		ObjectList->setValue(objName, 1);
		ObjectList->endGroup();
		ObjectPro->beginGroup(objName);
		ObjectPro->setValue("posX", cam->posX);
		ObjectPro->setValue("posY", cam->posY);
		ObjectPro->setValue("posZ", cam->posZ);
		ObjectPro->setValue("speed", cam->speed);
		ObjectPro->setValue("type", cam->type);
		ObjectPro->endGroup();
		SAFE_DELETE(ObjectList);
		SAFE_DELETE(ObjectPro);		
		g_gameLog->AppendLog("添加摄像机.");
		break;
	case My_SkyBox:
		skybox = &(*worldSkyBox.find(objName)).second;
		ObjectList->beginGroup("Object");
		ObjectList->setValue(objName, 2);
		ObjectList->endGroup();
		ObjectPro->beginGroup(objName);
		ObjectPro->setValue("length", skybox->length);
		ObjectPro->setValue("skyFront", skybox->skyFront);
		ObjectPro->setValue("skyBack", skybox->skyBack);
		ObjectPro->setValue("skyLeft", skybox->skyLeft);
		ObjectPro->setValue("skyRight", skybox->skyRight);
		ObjectPro->setValue("skyTop", skybox->skyTop);
		ObjectPro->endGroup();
		SAFE_DELETE(ObjectList);
		SAFE_DELETE(ObjectPro);
		g_gameLog->AppendLog("添加天空.");
		break;
	case My_Terrain:
		terrain = &(*worldTerrain.find(objName)).second;
		ObjectList->beginGroup("Object");
		ObjectList->setValue(objName, 3);
		ObjectList->endGroup();
		ObjectPro->beginGroup(objName);
		ObjectPro->setValue("rawFileName", terrain->rawFileName);
		ObjectPro->setValue("fileName", terrain->fileName);
		ObjectPro->setValue("numVertsPerCol", terrain->numVertsPerCol);
		ObjectPro->setValue("numVertsPerRow", terrain->numVertsPerRow);
		ObjectPro->setValue("cellSpacing", terrain->cellSpacing);
		ObjectPro->setValue("heightScale", terrain->heightScale);
		ObjectPro->endGroup();
		SAFE_DELETE(ObjectList);
		SAFE_DELETE(ObjectPro);
		g_gameLog->AppendLog("添加地形.");
		break;
	case My_Light:
		light = &(*worldLight.find(objName)).second;
		ObjectList->beginGroup("Object");
		ObjectList->setValue(objName, 4);
		ObjectList->endGroup();
		ObjectPro->beginGroup(objName);
		ObjectPro->setValue("posX", light->posX);
		ObjectPro->setValue("posY", light->posY);
		ObjectPro->setValue("posZ", light->posZ);
		ObjectPro->setValue("rotX", light->rotX);
		ObjectPro->setValue("rotY", light->rotY);
		ObjectPro->setValue("rotZ", light->rotZ);
		ObjectPro->setValue("type", light->type);
		ObjectPro->setValue("colorR", light->colorR);
		ObjectPro->setValue("colorG", light->colorG);
		ObjectPro->setValue("colorB", light->colorB);
		ObjectPro->endGroup();
		SAFE_DELETE(ObjectList);
		SAFE_DELETE(ObjectPro);
		g_gameLog->AppendLog("添加灯光.");
		break;
	case My_Particle:
		particle = &(*worldParticle.find(objName)).second;
		ObjectList->beginGroup("Object");
		ObjectList->setValue(objName, 5);
		ObjectList->endGroup();
		ObjectPro->beginGroup(objName);
		ObjectPro->setValue("fileName", particle->fileName);
		ObjectPro->setValue("height", particle->height);
		ObjectPro->setValue("length", particle->length);
		ObjectPro->setValue("width", particle->width);
		ObjectPro->setValue("num", particle->num);
		ObjectPro->setValue("type", particle->type);
		ObjectPro->setValue("posX", particle->postion.x);
		ObjectPro->setValue("posY", particle->postion.y);
		ObjectPro->setValue("posZ", particle->postion.z);
		ObjectPro->endGroup();
		SAFE_DELETE(ObjectList);
		SAFE_DELETE(ObjectPro);
		g_gameLog->AppendLog("添加粒子.");
		break;
	case My_Fog:
		fog = &(*worldFog.find(objName)).second;
		ObjectList->beginGroup("Object");
		ObjectList->setValue(objName, 6);
		ObjectList->endGroup();
		ObjectPro->beginGroup(objName);
		ObjectPro->setValue("type", fog->type);
		ObjectPro->setValue("start", fog->start);
		ObjectPro->setValue("end", fog->end);
		ObjectPro->setValue("color_r", fog->color_r);
		ObjectPro->setValue("color_g", fog->color_g);
		ObjectPro->setValue("color_b", fog->color_b);
		ObjectPro->endGroup();
		SAFE_DELETE(ObjectList);
		SAFE_DELETE(ObjectPro);
		g_gameLog->AppendLog("添加雾效.");
		break;
	case My_Sprite:
		sprite = &(*worldSprite.find(objName)).second;
		ObjectList->beginGroup("Object");
		ObjectList->setValue(objName, 7);
		ObjectList->endGroup();
		ObjectPro->beginGroup(objName);
		ObjectPro->setValue("posX", sprite->posX);
		ObjectPro->setValue("posY", sprite->posY);
		ObjectPro->setValue("fileName", sprite->fileName);
		ObjectPro->endGroup();
		SAFE_DELETE(ObjectList);
		SAFE_DELETE(ObjectPro);
		break;
	case My_Button:
		button = &(*worldButton.find(objName)).second;
		ObjectList->beginGroup("Object");
		ObjectList->setValue(objName, 8);
		ObjectList->endGroup();
		ObjectPro->beginGroup(objName);
		ObjectPro->setValue("posX", button->posX);
		ObjectPro->setValue("posY", button->posY);
		ObjectPro->setValue("fileNameUp", button->fileNameUp);
		ObjectPro->setValue("fileNameDown", button->fileNameDown);		
		ObjectPro->setValue("fileNameMove", button->fileNameMove);
		ObjectPro->endGroup();
		SAFE_DELETE(ObjectList);
		SAFE_DELETE(ObjectPro);
		g_gameLog->AppendLog("添加按钮.");
		break;
	case My_Text:
		text = &(*worldText.find(objName)).second;
		ObjectList->beginGroup("Object");
		ObjectList->setValue(objName, 9);
		ObjectList->endGroup();
		ObjectPro->beginGroup(objName);
		ObjectPro->setValue("posX", text->posX);
		ObjectPro->setValue("posY", text->posY);
		ObjectPro->setValue("text", text->text);
		ObjectPro->setValue("colorR", text->colorR);
		ObjectPro->setValue("colorG", text->colorG);
		ObjectPro->setValue("colorB", text->colorB);
		ObjectPro->endGroup();
		SAFE_DELETE(ObjectList);
		SAFE_DELETE(ObjectPro);
		g_gameLog->AppendLog("添加文字.");
		break;
	case My_xModel:
		xModel = &(*worldxModel.find(objName)).second;
		ObjectList->beginGroup("Object");
		ObjectList->setValue(objName, 10);
		ObjectList->endGroup();
		ObjectPro->beginGroup(objName);
		ObjectPro->setValue("posX", xModel->posX);
		ObjectPro->setValue("posY", xModel->posY);
		ObjectPro->setValue("posZ", xModel->posZ);
		ObjectPro->setValue("rotX", xModel->rotX);
		ObjectPro->setValue("rotY", xModel->rotY);
		ObjectPro->setValue("rotZ", xModel->rotZ);
		ObjectPro->setValue("scaleX", xModel->scaleX);
		ObjectPro->setValue("scaleY", xModel->scaleY);
		ObjectPro->setValue("scaleZ", xModel->scaleZ);
		ObjectPro->setValue("fileName", xModel->fileName);
		ObjectPro->endGroup();
		SAFE_DELETE(ObjectList);
		SAFE_DELETE(ObjectPro);
		g_gameLog->AppendLog("添加模型.");
		break;
	case My_Cube:
		cube = &(*worldCube.find(objName)).second;
		ObjectList->beginGroup("Object");
		ObjectList->setValue(objName, 11);
		ObjectList->endGroup();
		ObjectPro->beginGroup(objName);
		ObjectPro->setValue("posX", cube->posX);
		ObjectPro->setValue("posY", cube->posY);
		ObjectPro->setValue("posZ", cube->posZ);
		ObjectPro->setValue("rotX", cube->rotX);
		ObjectPro->setValue("rotY", cube->rotY);
		ObjectPro->setValue("rotZ", cube->rotZ);
		ObjectPro->setValue("scaleX", cube->scaleX);
		ObjectPro->setValue("scaleY", cube->scaleY);
		ObjectPro->setValue("scaleZ", cube->scaleZ);
		ObjectPro->setValue("colorR", cube->colorR);
		ObjectPro->setValue("colorG", cube->colorG);
		ObjectPro->setValue("colorB", cube->colorB);
		ObjectPro->endGroup();
		SAFE_DELETE(ObjectList);
		SAFE_DELETE(ObjectPro);
		break;
	case My_Sphere:
		sphere = &(*worldSphere.find(objName)).second;
		ObjectList->beginGroup("Object");
		ObjectList->setValue(objName, 12);
		ObjectList->endGroup();
		ObjectPro->beginGroup(objName);
		ObjectPro->setValue("posX", sphere->posX);
		ObjectPro->setValue("posY", sphere->posY);
		ObjectPro->setValue("posZ", sphere->posZ);
		ObjectPro->setValue("rotX", sphere->rotX);
		ObjectPro->setValue("rotY", sphere->rotY);
		ObjectPro->setValue("rotZ", sphere->rotZ);
		ObjectPro->setValue("scaleX", sphere->scaleX);
		ObjectPro->setValue("scaleY", sphere->scaleY);
		ObjectPro->setValue("scaleZ", sphere->scaleZ);
		ObjectPro->setValue("colorR", sphere->colorR);
		ObjectPro->setValue("colorG", sphere->colorG);
		ObjectPro->setValue("colorB", sphere->colorB);
		ObjectPro->endGroup();
		SAFE_DELETE(ObjectList);
		SAFE_DELETE(ObjectPro);
		break;
	}
}

void IniFile::del_object_ini(QString objName) {
	ObjectList = new QSettings(SYS_CONFIG, QSettings::IniFormat);
	ObjectPro = new QSettings(SYS_CONFIG, QSettings::IniFormat);
	ObjectList->beginGroup("Object");
	ObjectList->remove(objName);
	SAFE_DELETE(ObjectList);
	SAFE_DELETE(ObjectPro);
}
