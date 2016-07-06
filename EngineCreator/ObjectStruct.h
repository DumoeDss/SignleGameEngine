#pragma once
#include "gameEngine.h"
//��Ϸ��������
enum proType {
	EmptyObject = 0,
	My_Camera,
	My_SkyBox,
	My_Terrain,
	My_Light,
	My_Particle,
	My_Fog,
	My_Sprite,
	My_Button,
	My_Text,
	My_xModel,
	My_Cube,
	My_Sphere
};


struct ObjectBase
{
	ObjectBase():posX(0),posY(0),posZ(0),
		rotX(0),rotY(0),rotZ(0){}
	int posX, posY, posZ;
	int rotX, rotY, rotZ;
};

//�����
enum CameraType {	//����
	LANDOBJECT = 0, //½
	AIRCRAFT	//����
};	
struct Pro_Camera {
	Pro_Camera() { 
		posX = posY = posZ = type = 0; 
		speed = 1;
	}
	int posX, posY, posZ;
	int type;
	int speed;
	/*char walk_front;
	char walk_back;
	char walk_left;
	char walk_right;
	char fly_up;
	char fly_down;*/
};

//��պ�
struct Pro_SkyBox {
	Pro_SkyBox() {
		length = 0;
		skyFront = skyBack = skyLeft = skyRight = skyTop = "";
	}
	int length;
	QString skyFront;
	QString skyBack;
	QString skyLeft;
	QString skyRight;
	QString skyTop;
};

//����
struct Pro_Terrain {
	QString rawFileName;
	QString fileName;
	int numVertsPerRow;
	int numVertsPerCol;
	int cellSpacing;
	float heightScale;
};

//��Դ
struct Pro_Light : public ObjectBase {
	Pro_Light() {
		colorR = colorG = colorB = 0;
	}
	//myLight my_light;
	int colorR, colorG, colorB;
	int type;
};

//����
struct Pro_Particle {
	Pro_Particle() {
		postion = MyVector3(0, 0, 0);
		length = 0;
		height = 0;
		width = 0;
		num = 0;
		type = 1;
		fileName = "";
	}
	MyVector3 postion;
	int length;
	int height;
	int width;
	int type;
	QString fileName;
	int num;
};

//��
struct Pro_Fog {
	int start;
	int end;
	int color_r;
	int color_g;
	int color_b;
	int type;
};

//GUI����
struct Pro_Sprite {
	int posX, posY;
	QString fileName;
};

//GUI��ť
struct Pro_Button {
	int posX, posY;
	QString fileNameUp;
	QString fileNameDown;
	QString fileNameMove;
};

//GUI�ı�
struct Pro_Text {
	int posX, posY;
	int colorR, colorG, colorB;
	QString text;
};

//ģ��
struct Pro_xModel : public ObjectBase {
	Pro_xModel() {
		fileName = "";
		scaleX = scaleY = scaleZ = 1.0f;
	}
	QString fileName;
	float scaleX, scaleY, scaleZ;
	int id;
};

//������
struct Pro_Cube : public ObjectBase {
	Pro_Cube() {
		scaleX = scaleY = scaleZ = 1.0f;
		colorR = colorG = colorB = 0;
	}
	float scaleX, scaleY, scaleZ;
	int colorR, colorG, colorB;
};

//����
struct Pro_Sphere : public ObjectBase {
	Pro_Sphere() {
		scaleX = scaleY = scaleZ = 1.0f;
		colorR = colorG = colorB = 0;
	}
	float scaleX, scaleY, scaleZ;
	int colorR, colorG, colorB;
};

////Բ����
//struct Pro_Cylinder : public ObjectBase {
//
//};
//
////Բ����
//struct Pro_Torus : public ObjectBase {
//
//};
//
////���
//struct Pro_Teapot : public ObjectBase {
//
//};

