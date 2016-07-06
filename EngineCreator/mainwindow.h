#pragma once
#include <QWidget>
#include "ui_mainwindow.h"
#include "ObjectStruct.h"

class QFileSystemModel;
class QHBoxLayout;
class QVBoxLayout;
class QListWidget;
class QStackedLayout;
class EngineCreator;
class PropertyWidget;
class QPushButton;
class QLabel;
class IniFile;
class QListWidgetItem;

class MainWindow : public QWidget {
	Q_OBJECT

public:
	MainWindow(QWidget * parent = Q_NULLPTR);
	~MainWindow();
	 void contextMenuEvent(QContextMenuEvent *event);
	 void LoadObject();

private:
	Ui::MainWindow ui;
	
	QFileSystemModel *m_dirModel;
	QHBoxLayout *mainLayout;	//主布局
	QVBoxLayout *leftLayout;	//左边布局
	QVBoxLayout *rightLayout;	//右边布局
	QVBoxLayout *midleLayout;	//中间的垂直布局，用来放置项目文件与文件列表
	QListWidget *listWidget;	//对象列表
	QStackedLayout *stackedLayout;	//对象属性面板
	std::vector<PropertyWidget *> m_vecProWidgets;
	QPushButton *btn_Add;
	QPushButton *btn_Del;
	EngineCreator *ec;
	QLabel *lb_objectList;
	QLabel *lb_objectPro;	

	QListWidgetItem *m_current_item;

	IniFile *m_ini_file;

private slots:	
	void do_add_xModel();
	void do_add_cube();
	void do_add_sphere();
	void do_add_cylinder();
	void do_add_torus();
	void do_add_teaPot();
	void do_add_sprite();
	void do_add_button();
	void do_add_text();
	void do_add_particle();
	void do_add_fog();
	void do_add_light();
	void do_add_skyBox();
	void do_add_terrain();
	void do_add_camera();
	void do_del_object();

	void do_change_list_name(QString name,proType type);
	
};

extern std::map<QString, Pro_SkyBox> worldSkyBox;
extern std::map<QString, Pro_Camera> worldCamera;
extern std::map<QString, Pro_Terrain> worldTerrain;
extern std::map<QString, Pro_Light> worldLight;
extern std::map<QString, Pro_Particle> worldParticle;
extern std::map<QString, Pro_Fog> worldFog;
extern std::map<QString, Pro_Sprite> worldSprite;
extern std::map<QString, Pro_Button> worldButton;
extern std::map<QString, Pro_Text> worldText;
extern std::map<QString, Pro_xModel> worldxModel;
extern std::map<QString, Pro_Cube> worldCube;
extern std::map<QString, Pro_Sphere> worldSphere;