#pragma once
#include <QWidget>
#include "ui_propertywidget.h"

#include "ObjectStruct.h"

class QCheckBox;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QListWidget;
class QRadioButton;
class QStackedLayout;
class QGridLayout;
class QVBoxLayout;
class QPushButton;

class pro_fog;
class pro_skyBox;
class pro_particle;
class pro_camera;
class pro_board;
class pro_button;
class pro_cube;
class pro_light;
class pro_sphere;
class pro_sprite;
class pro_terrain;
class pro_text;
class pro_transform;
class pro_xModel;
class pro_name;
class IniFile;

class PropertyWidget : public QWidget {
	Q_OBJECT

public:
	PropertyWidget(QWidget * parent = Q_NULLPTR, proType type = EmptyObject);
	~PropertyWidget();
	//位置
	int getPosX();
	int getPosY();
	int getPosZ();
	int getRotX();
	int getRotY();
	int getRotZ();
	//摄像机
	int getCameraType();
	int getSpeed();
	//天空盒
	int getSkyBoxLength();
	QString getSkyBoxFront();
	QString getSkyBoxBack();
	QString getSkyBoxLeft();
	QString getSkyBoxRight();
	QString getSkyBoxTop();
	//雾效
	int getFogType();
	int getFogStart();
	int getFogEnd();
	int getFogColorR();
	int getFogColorG();
	int getFogColorB();
	//灯光
	int getLightColorR();
	int getLightColorG();
	int getLightColorB();
	int getLightType();
	//按钮
	QString get_up_name();
	QString get_down_name();
	QString get_move_name();
	//文字
	int getTextColorR();
	int getTextColorG();
	int getTextColorB();
	QString getText();
	//模型
	QString getXModelFile();
	int getScaleX();
	int getScaleY();
	int getScaleZ();
	//地形
	QString getRawFileName();
	QString getFileName();
	int getNumVertsPerRow();
	int getNumVertsPerCol();
	int getCellSpacing();	
	float getHeightScale();
	//粒子
	int getLength();
	int getWidth();
	int getHeight();
	int getNum();
	int getParType();
	QString getName();
	//立方体
	int getColorR();
	int getColorG();
	int getColorB();
	
	//位置
	void setPosX(int x);
	void setPosY(int y);
	void setPosZ(int z);
	void setRotX(int x);
	void setRotY(int y);
	void setRotZ(int z);
	//摄像机
	void setCameraType(int type);
	void setSpeed(int speed);
	//天空盒
	void setSkyBoxLength(int length);
	void setSkyBoxFront(QString front);
	void setSkyBoxBack(QString back);
	void setSkyBoxLeft(QString left);
	void setSkyBoxRight(QString right);
	void setSkyBoxTop(QString top);
	//雾效
	void setFogType(int type);
	void setFogStart(int start);
	void setFogEnd(int end);
	void setFogColorR(int r);
	void setFogColorG(int g);
	void setFogColorB(int b);
	//灯光
	void setLightColorR(int r);
	void setLightColorG(int g);
	void setLightColorB(int b);
	void setLightType(int type);
	//按钮
	void set_up_name(QString up);
	void set_down_name(QString down);
	void set_move_name(QString move);
	//文字
	void setTextColorR(int r);
	void setTextColorG(int g);
	void setTextColorB(int b);
	void setText(QString fileName);
	//模型
	void setXModelFile(QString fileName);
	void setScaleX(int x);
	void setScaleY(int y);
	void setScaleZ(int z);
	//地形
	void setFileName(QString name);
	void setNumVertsPerRow(int numVertsPerRow);
	void setNumVertsPerCol(int numVertsPerCol);
	void setCellSpacing(int cellSpacing);
	void setRawFileName(QString name);
	void setHeightScale(float heightScale);
	//粒子
	void setLength(int length);
	void setWidth(int width);
	void setHeight(int height);
	void setNum(int num);
	void setParType(int type);
	void setName(QString name);

	void setColorR(int r);
	void setColorG(int g);
	void setColorB(int b);

	proType getType() {
		return m_type;
	}

private:
	Ui::PropertyWidget ui;
	proType m_type;	//类型
	QVBoxLayout *mainLayout;	//主布局
	pro_fog *fogWidget;
	pro_skyBox *skyboxWidget;
	pro_particle *particleWidget;
	pro_camera *cameraWidget;
	pro_board *boardWidget;
	pro_button *buttonWidget;
	pro_cube *cubeWidget;
	pro_light *lightWidget;
	pro_sphere *sphereWidget;
	pro_sprite *spriteWidget;
	pro_terrain *terrainWidget;
	pro_text *textWidget;
	pro_transform *transformWidget;
	pro_xModel *xModelWidget;
	pro_name *nameWidget;

	Pro_Camera *m_cam;
	Pro_Fog *m_fog;
	Pro_Button *m_button;
	Pro_Cube *m_cube;
	Pro_Light *m_light;
	Pro_Particle *m_particle;
	Pro_Sphere *m_sphere;
	Pro_SkyBox *m_skybox;
	Pro_Sprite *m_sprite;
	Pro_Terrain *m_terrain;
	Pro_Text *m_text;
	Pro_xModel *m_xmodel;
	IniFile *m_ini_file;

private slots:
	void do_btn_ok_click();
signals:
	void list_change_name(QString name,proType type);
	void obj_change_pro(QString name);
};


