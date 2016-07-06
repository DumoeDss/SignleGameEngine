#include "pro_camera.h"
#include "defines.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIntValidator>
#include <QComboBox>
pro_camera::pro_camera(QWidget * parent) : QWidget(parent) {
	cameraGrid = new QGridLayout;
	cameraGroupBox = new QGroupBox(u8"摄像机");
	QIntValidator *posVal = new QIntValidator(0, 10000, this);
	QIntValidator *rotVal = new QIntValidator(0, 360, this);
	QIntValidator *speedVal = new QIntValidator(0, 100, this);

	//位置
	lb_position = new QLabel(u8"位置");
	lb_posX = new QLabel(tr("X"));	
	le_posX = new QLineEdit();
	le_posX->setValidator(posVal);
	le_posX->setText("0");
	lb_posY = new QLabel(tr("Y"));
	le_posY = new QLineEdit();
	le_posY->setValidator(posVal);
	le_posY->setText("0");
	lb_posZ = new QLabel(tr("Z"));
	le_posZ = new QLineEdit();
	le_posZ->setValidator(posVal);
	le_posZ->setText("0");
	lb_speed = new QLabel(u8"速度");
	le_speed = new QLineEdit();
	le_speed->setValidator(speedVal);
	le_speed->setText("1");

	cameraGrid->addWidget(lb_position, 0, 0);
	cameraGrid->addWidget(lb_posX, 0, 1);
	cameraGrid->addWidget(le_posX, 0, 2);
	cameraGrid->addWidget(lb_posY, 0, 3);
	cameraGrid->addWidget(le_posY, 0, 4);
	cameraGrid->addWidget(lb_posZ, 0, 5);
	cameraGrid->addWidget(le_posZ, 0, 6);
	cameraGrid->addWidget(lb_speed, 1, 0);
	cameraGrid->addWidget(le_speed, 1, 2);

	lb_cameraType = new QLabel(u8"类型");
	cb_cameraType = new QComboBox();
	cb_cameraType->addItem(u8"普通");
	cb_cameraType->addItem(u8"飞行器");

	btn_Ok = new QPushButton(u8"确定");
	btn_Ok->setFixedSize(50, 22);
	connect(btn_Ok, SIGNAL(clicked()), this, SLOT(do_btn_click()));
	cameraGrid->addWidget(lb_cameraType, 2, 0);
	cameraGrid->addWidget(cb_cameraType, 2, 2);

	cameraGrid->addWidget(btn_Ok, 3, 7);

	cameraGroupBox->setLayout(cameraGrid);
}

pro_camera::~pro_camera() {
	SAFE_DELETE(lb_position);
	SAFE_DELETE(lb_posX);
	SAFE_DELETE(lb_posY);
	SAFE_DELETE(lb_posZ);
	SAFE_DELETE(le_posX);
	SAFE_DELETE(le_posY);
	SAFE_DELETE(le_posZ);
	//SAFE_DELETE(btn_Ok);
	SAFE_DELETE(cb_cameraType);	
	SAFE_DELETE(lb_cameraType);
	SAFE_DELETE(cameraGrid);
	SAFE_DELETE(cameraGroupBox);
}

QGroupBox* pro_camera::getGroupBox() {
	return cameraGroupBox;
}

int pro_camera::getCameraType() {
	return cb_cameraType->currentIndex();
}

void pro_camera::setCameraType(int type) {
	cb_cameraType->setCurrentIndex(type);
}

int pro_camera::getPosX() {
	return le_posX->text().toInt();
}

int pro_camera::getPosY() {
	return le_posY->text().toInt();
}

int pro_camera::getPosZ() {
	return le_posZ->text().toInt();
}

void pro_camera::setPosX(int x) {
	le_posX->setText(QString::number(x));
}

void pro_camera::setPosY(int y) {
	le_posY->setText(QString::number(y));
}

void pro_camera::setPosZ(int z) {
	le_posZ->setText(QString::number(z));
}

int pro_camera::getSpeed() {
	return le_speed->text().toInt();
}

void pro_camera::setSpeed(int speed) {
	le_speed->setText(QString::number(speed));
}

void pro_camera::do_btn_click() {
	emit(btn_click());
}
