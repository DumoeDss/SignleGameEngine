#include "mainwindow.h"
#include "enginecreator.h"
#include "propertywidget.h"
#include "Inifile.h"
#include "defines.h"
#include <QGridLayout>
#include <QListWidget>
#include <QStackedLayout>
#include <QFileSystemModel>
#include <QTimer>
#include <QPushButton>
#include <QLabel>

std::map< QString,Pro_SkyBox> worldSkyBox;
std::map< QString,Pro_Camera> worldCamera;
std::map<QString, Pro_Terrain> worldTerrain;
std::map<QString, Pro_Light> worldLight;
std::map<QString, Pro_Particle> worldParticle;
std::map<QString, Pro_Fog> worldFog;
std::map<QString, Pro_Sprite> worldSprite;
std::map<QString, Pro_Button> worldButton;
std::map<QString, Pro_Text> worldText;
std::map<QString, Pro_xModel> worldxModel;
std::map<QString, Pro_Cube> worldCube;
std::map<QString, Pro_Sphere> worldSphere;

MainWindow::MainWindow(QWidget * parent) : QWidget(parent){

	
	mainLayout = new QHBoxLayout;
	midleLayout = new QVBoxLayout;
	leftLayout = new QVBoxLayout;
	rightLayout = new QVBoxLayout;
	listWidget = new QListWidget;
	stackedLayout = new QStackedLayout;
	lb_objectList = new QLabel(u8"游戏对象");
	lb_objectPro = new QLabel(u8"对象属性");
	
	ec = new EngineCreator(this, 900, 640);
	LoadObject();

	leftLayout->addWidget(ec);
	leftLayout->addStretch();

	midleLayout->addWidget(lb_objectList);
	midleLayout->addWidget(listWidget);

	rightLayout->addWidget(lb_objectPro);
	rightLayout->addLayout(stackedLayout);
	//切换物体对象时同步切换属性面板
	connect(listWidget, SIGNAL(currentRowChanged(int)), stackedLayout, SLOT(setCurrentIndex(int)));
	listWidget->setCurrentRow(0);

	//设置主布局
	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(midleLayout);
	mainLayout->addLayout(rightLayout);
	mainLayout->addStretch();
	setLayout(mainLayout);	
}

MainWindow::~MainWindow() {
	//SAFE_DELETE(m_current_item);
	for (int i = 0; i != m_vecProWidgets.size(); ++i) {
		SAFE_DELETE(m_vecProWidgets[i]);
	}

}
//更改对象列表名字
void MainWindow::do_change_list_name(QString name,proType type) {
	switch (type) {
	case My_Light:
		if (worldLight.find(name) != worldLight.end()) {
			return;
		}
		break;
	case My_Particle:
		if (worldParticle.find(name) != worldParticle.end()) {
			return;
		}
		break;
	case My_Sprite:
		if (worldSprite.find(name) != worldSprite.end()) {
			return;
		}
		break;
	case My_Button:
		if (worldButton.find(name) != worldButton.end()) {
			return;
		}
		break;
	case My_Text:
		if (worldText.find(name) != worldText.end()) {
			return;
		}
		break;
	case My_xModel:
		if (worldxModel.find(name) != worldxModel.end()) {
			return;
		}
		break;
	case My_Cube:
		if (worldCube.find(name) != worldCube.end()) {
			return;
		}
		break;
	case My_Sphere:
		if (worldSphere.find(name) != worldSphere.end()) {
			return;
		}
		break;
	defalut :
		return;
	}
	m_current_item = listWidget->currentItem();
	m_current_item->setText(name);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
	//右键菜单
	if (cursor().pos().x()<=midleLayout->contentsRect().right() && cursor().pos().x()>=midleLayout->contentsRect().left()) {
		midleLayout->contentsRect().bottomLeft();
		QMenu *mainMenu = new QMenu(this);	//主菜单
		QMenu *modelMenu;	//3D模型的二级菜单
		QMenu *uiMenu;	//UI的二级菜单
		QMenu *effectMenu;	//特效的二级菜单
		//添加3D模型的二级菜单
		modelMenu = mainMenu->addMenu(u8"添加3D模型");
		QAction *add_xModel = new QAction(u8"导入X模型", this);		
		//QAction *add_cube = new QAction(u8"创建立方体", this);
		//QAction *add_sphere = new QAction(u8"创建球体", this);
		/*QAction *add_cylinder = new QAction(u8"创建圆柱体", this);
		QAction *add_torus = new QAction(u8"创建圆环体", this);
		QAction *add_teaPot = new QAction(u8"创建茶壶", this);*/
		modelMenu->addAction(add_xModel);	
		//modelMenu->addAction(add_cube);
		//modelMenu->addAction(add_sphere);
	/*	modelMenu->addAction(add_cylinder);
		modelMenu->addAction(add_torus);
		modelMenu->addAction(add_teaPot);*/
		//添加UI的二级菜单
		uiMenu = mainMenu->addMenu(u8"添加UI");
		//QAction *add_sprite = new QAction(u8"添加精灵", this);
		QAction *add_button = new QAction(u8"添加按钮", this);
		QAction *add_text = new QAction(u8"添加文字", this);
		//uiMenu->addAction(add_sprite);
		uiMenu->addAction(add_button);
		uiMenu->addAction(add_text);
		//特效的二级菜单
		effectMenu = mainMenu->addMenu(u8"添加特效");
		QAction *add_particle = new QAction(u8"添加粒子", this);
		QAction *add_fog = new QAction(u8"添加雾", this);
		//QAction *add_water = new QAction(u8"添加水", this);
		effectMenu->addAction(add_particle);
		effectMenu->addAction(add_fog);
		//effectMenu->addAction(add_water);
		//主菜单
		//QAction *add_light = new QAction(u8"添加光照", this);
		QAction *add_skyBox = new QAction(u8"添加天空盒", this);
		QAction *add_terrian = new QAction(u8"添加地形", this);
		QAction *add_camera = new QAction(u8"添加摄像机", this);
		QAction *del_action = new QAction(u8"删除", this);
		//mainMenu->addAction(add_light);
		mainMenu->addAction(add_skyBox);
		mainMenu->addAction(add_terrian);
		mainMenu->addAction(add_camera);
		mainMenu->addAction(del_action);

		connect(add_xModel, SIGNAL(triggered()), this, SLOT(do_add_xModel()));
		//connect(add_cube, SIGNAL(triggered()), this, SLOT(do_add_cube()));
		//connect(add_sphere, SIGNAL(triggered()), this, SLOT(do_add_sphere()));
		/*connect(add_cylinder, SIGNAL(triggered()), this, SLOT(do_add_cylinder()));
		connect(add_torus, SIGNAL(triggered()), this, SLOT(do_add_torus()));
		connect(add_teaPot, SIGNAL(triggered()), this, SLOT(do_add_teaPot()));*/
		//connect(add_sprite, SIGNAL(triggered()), this, SLOT(do_add_sprite()));
		connect(add_button, SIGNAL(triggered()), this, SLOT(do_add_button()));
		connect(add_text, SIGNAL(triggered()), this, SLOT(do_add_text()));
		connect(add_particle, SIGNAL(triggered()), this, SLOT(do_add_particle()));
		connect(add_fog, SIGNAL(triggered()), this, SLOT(do_add_fog()));
		//connect(add_light, SIGNAL(triggered()), this, SLOT(do_add_light()));
		connect(add_skyBox, SIGNAL(triggered()), this, SLOT(do_add_skyBox()));
		connect(add_terrian, SIGNAL(triggered()), this, SLOT(do_add_terrain()));
		connect(add_camera, SIGNAL(triggered()), this, SLOT(do_add_camera()));
		connect(del_action, SIGNAL(triggered()), this, SLOT(do_del_object()));

		mainMenu->move(cursor().pos());
		mainMenu->show();
	}
	
}
//删除对象
void MainWindow::do_del_object() {
	//获取当前游戏对象索引
	int i = listWidget->currentRow();
	QListWidgetItem * item = listWidget->currentItem();
	int xModelid = 0;
	if (item) {
		QString name = item->text();
		proType type = m_vecProWidgets[i]->getType();
		switch (type) {
		case EmptyObject:

			break;
		case My_Camera:
			name = "wCamera";
			worldCamera.erase(name);
			break;
		case My_SkyBox:
			name = "wSkyBox";
			worldSkyBox.erase(name);
			break;
		case My_Terrain:
			name = "wTerrain";
			worldTerrain.erase(name);
			break;
		case My_Light:
			worldLight.erase(name);
			break;
		case My_Particle:
			worldParticle.erase(name);
			break;
		case My_Fog:
			name = "wFog";
			worldFog.erase(name);
			break;
		case My_Sprite:
			worldSprite.erase(name);
			break;
		case My_Button:
			worldButton.erase(name);
			g_Render->DelGUIButton(g_mainGui,(*guiId.find(name)).second);
			guiId.erase(name);
			break;
		case My_Text:
			worldText.erase(name);
			g_Render->DelGUIStaticText(g_mainGui, (*guiId.find(name)).second);
			guiId.erase(name);
			break;
		case My_xModel:		
			xModelid = (*xModelId.find((*worldxModel.find(name)).first)).second;
			g_Render->DelXModel(xModelid);
			worldxModel.erase(name);
			xModelId.erase(name);
			for (auto &id : xModelId) {
				if (id.second > xModelid) {
					id.second -= 1;
				}
			}			
			break;
		case My_Cube:
			worldCube.erase(name);
			break;
		case My_Sphere:
			worldSphere.erase(name);
			break;
		}
		stackedLayout->removeWidget((m_vecProWidgets[i]));
		m_vecProWidgets.erase(m_vecProWidgets.begin() + i);
		listWidget->removeItemWidget(item);
		m_ini_file = new IniFile();
		m_ini_file->del_object_ini(name);
		SAFE_DELETE(item);
	}
}

//添加X模型
void MainWindow::do_add_xModel() {
	listWidget->addItem(u8"模型");
	PropertyWidget *model = new PropertyWidget(this, My_xModel);
	m_vecProWidgets.push_back(model);
	stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(list_change_name(QString, proType)), 
		this, SLOT(do_change_list_name(QString, proType)));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
		ec, SLOT(do_change_obj_pro(QString)));
	listWidget->setCurrentRow(m_vecProWidgets.size() - 1);
}
//添加立方体
void MainWindow::do_add_cube() {
	listWidget->addItem(u8"立方体");
	PropertyWidget *cube = new PropertyWidget(this, My_Cube);
	m_vecProWidgets.push_back(cube);
	stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(list_change_name(QString, proType)),
		this, SLOT(do_change_list_name(QString, proType)));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
		ec, SLOT(do_change_obj_pro(QString)));
	listWidget->setCurrentRow(m_vecProWidgets.size() - 1);
}
//添加球体
void MainWindow::do_add_sphere() {
	listWidget->addItem(u8"球体");
	PropertyWidget *sphere = new PropertyWidget(this, My_Sphere);
	m_vecProWidgets.push_back(sphere);
	stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(list_change_name(QString, proType)), 
		this, SLOT(do_change_list_name(QString, proType)));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
		ec, SLOT(do_change_obj_pro(QString)));
	listWidget->setCurrentRow(m_vecProWidgets.size() - 1);
}
//添加圆柱体
void MainWindow::do_add_cylinder() {
	listWidget->addItem(u8"圆柱体");
	PropertyWidget *sphere = new PropertyWidget(this, My_Sphere);
	m_vecProWidgets.push_back(sphere);
	stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(list_change_name(QString, proType)),
		this, SLOT(do_change_list_name(QString, proType)));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
		ec, SLOT(do_change_obj_pro(QString)));
	listWidget->setCurrentRow(m_vecProWidgets.size() - 1);
}
//添加圆环体
void MainWindow::do_add_torus() {
	listWidget->addItem(u8"圆环体");
	PropertyWidget *sphere = new PropertyWidget(this, My_Sphere);
	m_vecProWidgets.push_back(sphere);
	stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(list_change_name(QString, proType)), 
		this, SLOT(do_change_list_name(QString, proType)));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
		ec, SLOT(do_change_obj_pro(QString)));
	listWidget->setCurrentRow(m_vecProWidgets.size() - 1);
}
//添加茶壶
void MainWindow::do_add_teaPot() {
	listWidget->addItem(u8"茶壶");
	PropertyWidget *sphere = new PropertyWidget(this, My_Sphere);
	m_vecProWidgets.push_back(sphere);
	stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(list_change_name(QString, proType)), 
		this, SLOT(do_change_list_name(QString, proType)));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
		ec, SLOT(do_change_obj_pro(QString)));
	listWidget->setCurrentRow(m_vecProWidgets.size() - 1);
}
//添加UI精灵
void MainWindow::do_add_sprite() {
	listWidget->addItem(u8"UI精灵");
	PropertyWidget *sprite = new PropertyWidget(this, My_Sprite);
	m_vecProWidgets.push_back(sprite);
	stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(list_change_name(QString, proType)), 
		this, SLOT(do_change_list_name(QString, proType)));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
		ec, SLOT(do_change_obj_pro(QString)));
	listWidget->setCurrentRow(m_vecProWidgets.size() - 1);
}
//添加按钮
void MainWindow::do_add_button() {
	listWidget->addItem(u8"按钮");
	PropertyWidget *button = new PropertyWidget(this, My_Button);
	m_vecProWidgets.push_back(button);
	stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(list_change_name(QString, proType)),
		this, SLOT(do_change_list_name(QString, proType)));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
		ec, SLOT(do_change_obj_pro(QString)));
	listWidget->setCurrentRow(m_vecProWidgets.size() - 1);
}
//添加文本
void MainWindow::do_add_text() {
	listWidget->addItem(u8"文本");
	PropertyWidget *text = new PropertyWidget(this, My_Text);
	m_vecProWidgets.push_back(text);
	stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(list_change_name(QString, proType)),
		this, SLOT(do_change_list_name(QString, proType)));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
		ec, SLOT(do_change_obj_pro(QString)));
	listWidget->setCurrentRow(m_vecProWidgets.size() - 1);
}
//添加粒子
void MainWindow::do_add_particle() {
	listWidget->addItem(u8"粒子");
	PropertyWidget *particle = new PropertyWidget(this, My_Particle);
	m_vecProWidgets.push_back(particle);
	stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(list_change_name(QString, proType)), 
		this, SLOT(do_change_list_name(QString, proType)));
	connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
		ec, SLOT(do_change_obj_pro(QString)));
	listWidget->setCurrentRow(m_vecProWidgets.size() - 1);
}
//添加雾效
void MainWindow::do_add_fog() {
	if (worldFog.size() == 0) {
		listWidget->addItem(u8"雾效");
		PropertyWidget *fog = new PropertyWidget(this, My_Fog);
		m_vecProWidgets.push_back(fog);
		stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
		connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(list_change_name(QString, proType)),
			this, SLOT(do_change_list_name(QString, proType)));
		connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
			ec, SLOT(do_change_obj_pro(QString)));
		listWidget->setCurrentRow(m_vecProWidgets.size() - 1);
	}
}
//添加光照 
void MainWindow::do_add_light() {
	if (worldLight.size() == 0) {
		listWidget->addItem(u8"光照");
		PropertyWidget *light = new PropertyWidget(this, My_Light);
		m_vecProWidgets.push_back(light);
		stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
		connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(list_change_name(QString, proType)),
			this, SLOT(do_change_list_name(QString, proType)));
		connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
			ec, SLOT(do_change_obj_pro(QString)));
		listWidget->setCurrentRow(m_vecProWidgets.size() - 1);
	}
}
//添加天空盒
void MainWindow::do_add_skyBox() {
	if (worldSkyBox.size() == 0) {
		listWidget->addItem(u8"天空盒");
		PropertyWidget *skybox = new PropertyWidget(this, My_SkyBox);
		m_vecProWidgets.push_back(skybox);
		stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
		connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(list_change_name(QString, proType)),
			this, SLOT(do_change_list_name(QString, proType)));
		connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
			ec, SLOT(do_change_obj_pro(QString)));
		listWidget->setCurrentRow(m_vecProWidgets.size() - 1);
	}
}
//添加地形
void MainWindow::do_add_terrain() {
	if (worldTerrain.size() == 0) {
		listWidget->addItem(u8"地形");
		PropertyWidget *terrian = new PropertyWidget(this, My_Terrain);
		m_vecProWidgets.push_back(terrian);
		stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
		connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(list_change_name(QString, proType)),
			this, SLOT(do_change_list_name(QString, proType)));
		connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
			ec, SLOT(do_change_obj_pro(QString)));
		listWidget->setCurrentRow(m_vecProWidgets.size() - 1);
	}
}
//添加摄像机
void MainWindow::do_add_camera() {
	if (worldCamera.size() == 0) {
		//添加到对象列表
		listWidget->addItem(u8"摄像机");
		//创建摄像机对象属性面板
		PropertyWidget *pro_cam = new PropertyWidget(this, My_Camera);
		//添加到属性面板列表中
		m_vecProWidgets.push_back(pro_cam);
		stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
		connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(list_change_name(QString, proType)),
			this, SLOT(do_change_list_name(QString, proType)));
		connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
			ec, SLOT(do_change_obj_pro(QString)));
		listWidget->setCurrentRow(m_vecProWidgets.size() - 1);
	}	
}

//读取配置文件，创建游戏对象和游戏对象属性面板
void MainWindow::LoadObject() {
	m_ini_file = new IniFile();
	m_ini_file->process_object_ini();
	if (worldCamera.size() > 0) {
		//添加到对象列表
		listWidget->addItem(u8"摄像机");
		//创建对象属性面板
		PropertyWidget *camera = new PropertyWidget(this, My_Camera);
		camera->setPosX((*worldCamera.begin()).second.posX);
		camera->setPosY((*worldCamera.begin()).second.posY);
		camera->setPosZ((*worldCamera.begin()).second.posZ);
		camera->setCameraType((*worldCamera.begin()).second.type);
		camera->setSpeed((*worldCamera.begin()).second.speed);
		//添加到属性面板列表中
		m_vecProWidgets.push_back(camera);
		stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
		connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
			ec, SLOT(do_change_obj_pro(QString)));
	}
	if (worldSkyBox.size() > 0) {	
		//添加到对象列表
		listWidget->addItem(u8"天空盒");
		//创建对象属性面板
		PropertyWidget *skybox = new PropertyWidget(this, My_SkyBox);
		skybox->setSkyBoxLength((*worldSkyBox.begin()).second.length);
		skybox->setSkyBoxFront((*worldSkyBox.begin()).second.skyFront);
		skybox->setSkyBoxBack((*worldSkyBox.begin()).second.skyBack);
		skybox->setSkyBoxLeft((*worldSkyBox.begin()).second.skyLeft);
		skybox->setSkyBoxRight((*worldSkyBox.begin()).second.skyRight);
		skybox->setSkyBoxTop((*worldSkyBox.begin()).second.skyTop);
		//添加到属性面板列表中
		m_vecProWidgets.push_back(skybox);
		stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
		connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
			ec, SLOT(do_change_obj_pro(QString)));
	}
	if (worldTerrain.size() > 0) {
		//添加到对象列表
		listWidget->addItem(u8"地形");
		//创建对象属性面板
		PropertyWidget *terrain = new PropertyWidget(this, My_Terrain);
		terrain->setRawFileName((*worldTerrain.begin()).second.rawFileName);
		terrain->setFileName((*worldTerrain.begin()).second.fileName);
		terrain->setNumVertsPerRow((*worldTerrain.begin()).second.numVertsPerRow);
		terrain->setNumVertsPerCol((*worldTerrain.begin()).second.numVertsPerCol);
		terrain->setCellSpacing((*worldTerrain.begin()).second.cellSpacing);
		terrain->setHeightScale((*worldTerrain.begin()).second.heightScale);
		//添加到属性面板列表中
		m_vecProWidgets.push_back(terrain);
		stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
		connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
			ec, SLOT(do_change_obj_pro(QString)));
	}
	if (worldLight.size() > 0) {	
		for (auto &wlight : worldLight) {
			//添加到对象列表
			listWidget->addItem(wlight.first);
			//创建对象属性面板
			PropertyWidget *light = new PropertyWidget(this, My_Light);
			light->setName(wlight.first);
			light->setPosX(wlight.second.posX);
			light->setPosY(wlight.second.posY);
			light->setPosZ(wlight.second.posZ);
			light->setRotX(wlight.second.rotX);
			light->setRotX(wlight.second.rotY);
			light->setRotZ(wlight.second.rotZ);
			light->setLightColorR(wlight.second.colorR);
			light->setLightColorG(wlight.second.colorG);
			light->setLightColorB(wlight.second.colorB);
			//添加到属性面板列表中
			m_vecProWidgets.push_back(light);
			stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
			connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
				ec, SLOT(do_change_obj_pro(QString)));
		}
	}
	if (worldParticle.size() > 0) {
		for (auto &wpar : worldParticle) {
			//添加到对象列表
			listWidget->addItem(wpar.first);
			//创建对象属性面板
			PropertyWidget *particle = new PropertyWidget(this, My_Particle);
			particle->setName(wpar.first);
			particle->setFileName(wpar.second.fileName);
			particle->setHeight(wpar.second.height);
			particle->setLength(wpar.second.length);
			particle->setWidth(wpar.second.width);
			particle->setNum(wpar.second.num);
			particle->setParType(wpar.second.type);
			particle->setPosX(wpar.second.postion.x);
			particle->setPosY(wpar.second.postion.y);
			particle->setPosZ(wpar.second.postion.z);
			//添加到属性面板列表中
			m_vecProWidgets.push_back(particle);
			stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
			connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
				ec, SLOT(do_change_obj_pro(QString)));
		}
	}
	if (worldFog.size() > 0) {
		//添加到对象列表
		listWidget->addItem((*worldFog.begin()).first);
		//创建对象属性面板
		PropertyWidget *fog = new PropertyWidget(this, My_Fog);
		fog->setName((*worldFog.begin()).first);
		fog->setFogType((*worldFog.begin()).second.type);
		fog->setFogStart((*worldFog.begin()).second.start);
		fog->setFogEnd((*worldFog.begin()).second.end);
		fog->setFogColorR((*worldFog.begin()).second.color_r);
		fog->setFogColorG((*worldFog.begin()).second.color_g);
		fog->setFogColorB((*worldFog.begin()).second.color_b);
		//添加到属性面板列表中
		m_vecProWidgets.push_back(fog);
		stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
		connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
			ec, SLOT(do_change_obj_pro(QString)));
	}
	if (worldSprite.size() > 0) {
		for (auto &wsprite : worldSprite) {
			//添加到对象列表
			listWidget->addItem(wsprite.first);
			//创建对象属性面板
			PropertyWidget *sprite = new PropertyWidget(this, My_Sprite);
			sprite->setName(wsprite.first);
			sprite->setFileName(wsprite.second.fileName);
			sprite->setPosX(wsprite.second.posX);
			sprite->setPosY(wsprite.second.posY);
			//添加到属性面板列表中
			m_vecProWidgets.push_back(sprite);
			stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
			connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
				ec, SLOT(do_change_obj_pro(QString)));
		}
	}
	if (worldButton.size() > 0) {
		for (auto &wbutton : worldButton) {
			//添加到对象列表
			listWidget->addItem(wbutton.first);
			//创建对象属性面板
			PropertyWidget *button = new PropertyWidget(this, My_Button);
			button->setName(wbutton.first);
			button->set_up_name(wbutton.second.fileNameUp);
			button->set_down_name(wbutton.second.fileNameDown);
			button->set_move_name(wbutton.second.fileNameMove);
			button->setPosX(wbutton.second.posX);
			button->setPosY(wbutton.second.posY);
			//添加到属性面板列表中
			m_vecProWidgets.push_back(button);
			stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
			connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
				ec, SLOT(do_change_obj_pro(QString)));
		}
	}
	if (worldText.size() > 0) {
		for (auto &wtext : worldText) {
			//添加到对象列表
			listWidget->addItem(wtext.first);
			//创建对象属性面板
			PropertyWidget *text = new PropertyWidget(this, My_Text);
			text->setName(wtext.first);
			text->setText(wtext.second.text);
			text->setPosX(wtext.second.posX);
			text->setPosY(wtext.second.posY);
			text->setTextColorR(wtext.second.colorR);
			text->setTextColorG(wtext.second.colorG);
			text->setTextColorB(wtext.second.colorB);
			//添加到属性面板列表中
			m_vecProWidgets.push_back(text);
			stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
			connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
				ec, SLOT(do_change_obj_pro(QString)));
		}
	}
	if (worldxModel.size() > 0) {
		for (auto &wmodel: worldxModel) {
			//添加到对象列表
			listWidget->addItem(wmodel.first);
			//创建对象属性面板
			PropertyWidget *xModel = new PropertyWidget(this, My_xModel);
			xModel->setName(wmodel.first);
			xModel->setFileName(wmodel.second.fileName);
			xModel->setPosX(wmodel.second.posX);
			xModel->setPosY(wmodel.second.posY);
			xModel->setPosZ(wmodel.second.posZ);
			xModel->setRotX(wmodel.second.rotX);
			xModel->setRotY(wmodel.second.rotY);
			xModel->setRotZ(wmodel.second.rotZ);
			xModel->setScaleX(wmodel.second.scaleX);
			xModel->setScaleX(wmodel.second.scaleY);
			xModel->setScaleZ(wmodel.second.scaleZ);
			//添加到属性面板列表中
			m_vecProWidgets.push_back(xModel);
			stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
			connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
				ec, SLOT(do_change_obj_pro(QString)));
		}
	}
	if (worldCube.size() > 0) {
		for (auto &wcube : worldCube) {
			//添加到对象列表
			listWidget->addItem(wcube.first);
			//创建对象属性面板
			PropertyWidget *cube = new PropertyWidget(this, My_Cube);
			cube->setName(wcube.first);
			cube->setPosX(wcube.second.posX);
			cube->setPosY(wcube.second.posY);
			cube->setPosZ(wcube.second.posZ);
			cube->setRotX(wcube.second.rotX);
			cube->setRotX(wcube.second.rotY);
			cube->setRotZ(wcube.second.rotZ);
			cube->setScaleX(wcube.second.scaleX);
			cube->setScaleX(wcube.second.scaleY);
			cube->setScaleZ(wcube.second.scaleZ);
			cube->setColorR(wcube.second.colorR);
			cube->setColorG(wcube.second.colorG);
			cube->setColorB(wcube.second.colorB);
			//添加到属性面板列表中
			m_vecProWidgets.push_back(cube);
			stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
			connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
				ec, SLOT(do_change_obj_pro(QString)));
		}
	}
	if (worldSphere.size() > 0) {
		for (auto &wsphere : worldSphere) {
			//添加到对象列表
			listWidget->addItem(wsphere.first);
			//创建对象属性面板
			PropertyWidget *sphere = new PropertyWidget(this, My_Sphere);
			sphere->setName(wsphere.first);
			sphere->setPosX(wsphere.second.posX);
			sphere->setPosY(wsphere.second.posY);
			sphere->setPosZ(wsphere.second.posZ);
			sphere->setRotX(wsphere.second.rotX);
			sphere->setRotX(wsphere.second.rotY);
			sphere->setRotZ(wsphere.second.rotZ);
			sphere->setScaleX(wsphere.second.scaleX);
			sphere->setScaleX(wsphere.second.scaleY);
			sphere->setScaleZ(wsphere.second.scaleZ);
			sphere->setColorR(wsphere.second.colorR);
			sphere->setColorG(wsphere.second.colorG);
			sphere->setColorB(wsphere.second.colorB);
			//添加到属性面板列表中
			m_vecProWidgets.push_back(sphere);
			stackedLayout->addWidget(m_vecProWidgets.at(m_vecProWidgets.size() - 1));
			connect(m_vecProWidgets.at(m_vecProWidgets.size() - 1), SIGNAL(obj_change_pro(QString)),
				ec, SLOT(do_change_obj_pro(QString)));
		}
	}


	SAFE_DELETE(m_ini_file);
}