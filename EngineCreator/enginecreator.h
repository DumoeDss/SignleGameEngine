#ifndef ENGINECREATOR_H
#define ENGINECREATOR_H

#include <QtWidgets/QMainWindow>
#include <QWidget>
#include "ui_enginecreator.h"
#include "Inifile.h"
extern HWND g_hwnd;
extern HINSTANCE g_hInstance;

class EngineCreator : public QWidget
{
	Q_OBJECT

public:
	EngineCreator(QWidget *parent = 0, int width = 800, int height = 600);
	~EngineCreator();

	virtual QPaintEngine* paintEngine() const { return NULL; }

protected:
	virtual void resizeEvent(QResizeEvent *e);
	virtual void paintEvent(QPaintEvent *e);

	void d3dRender();
	void renderCamera();
	void renderSkyBox();
	void renderTerrain();
	void renderLight();
	void renderParticle();
	void renderFog();
	void renderSprite();
	void renderButton();
	void renderText();
	void renderxModel();
	void renderCube();
	void renderSphere();

	void processInput();

	void changeWorld();
	void changeWorld(QString name,int objType);
	//void d3dResize();
	bool InitGui();

private slots:
	void timer_done();
	void do_change_obj_pro(QString name);
private:
	IniFile *m_ini_file;
	MyCamera *g_Camera;
	int m_cameraType;
	int m_cameraSpeed;
	myLight *m_light;
	int ligntIndex;
	int m_gui_id;
	Ui::EngineCreatorClass ui;
};
extern bool g_LMBDown;
extern int g_mouseX;
extern int g_mouseY;
extern std::map<QString, int> guiId;
extern std::map<QString, int> xModelId;
void MainMenuCallback(int id, int state);
#endif // ENGINECREATOR_H
