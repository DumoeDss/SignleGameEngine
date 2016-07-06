#pragma once
#include <QSettings>
#include "ObjectStruct.h"

#define SYS_CONFIG "sys.ini"
class IniFile
{
public:
	IniFile();
	~IniFile();
	void process_object_ini();
	int process_object_ini(QString name);
	void add_object_ini(QString objName, proType objType);
	void del_object_ini(QString objName);
private:
	QSettings *ObjectList;
	QSettings *ObjectPro;
	std::vector<int> objTypeList;
	QStringList objNameList;
	Pro_Camera *cam;
	Pro_SkyBox *skybox;
	Pro_Terrain *terrain;
	Pro_Light *light;
	Pro_Particle *particle;
	Pro_Fog *fog;
	Pro_Sprite *sprite;
	Pro_Button *button;
	Pro_Text *text;
	Pro_xModel *xModel;
	Pro_Cube *cube;
	Pro_Sphere *sphere;
};
