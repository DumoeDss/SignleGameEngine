#include "pro_light.h"
#include "defines.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIntValidator>
#include <QComboBox>
pro_light::pro_light(QWidget * parent) : QWidget(parent) {
	lightGrid = new QGridLayout;
	lightGroupBox = new QGroupBox(u8"光照");
	QIntValidator *posVal = new QIntValidator(0, 10000, this);
	QIntValidator *rotVal = new QIntValidator(0, 360, this);
	QIntValidator *colorVal = new QIntValidator(0, 255, this);
	lb_name = new QLabel(u8"名字");
	le_name = new QLineEdit();
	le_name->setText(u8"光照");
	lightGrid->addWidget(lb_name, 0, 0);
	lightGrid->addWidget(le_name, 0, 2);
	//类型
	lb_lightType = new QLabel(u8"类型");
	cb_lightType = new QComboBox();
	cb_lightType->addItem(u8"方向光");
	cb_lightType->addItem(u8"点光源");
	cb_lightType->addItem(u8"聚光灯");
	lightGrid->addWidget(lb_lightType, 1, 0);
	lightGrid->addWidget(cb_lightType, 1, 2);
	//位置
	lb_position = new QLabel(u8"位置");
	le_posX = new QLineEdit();
	le_posX->setValidator(posVal);
	le_posX->setText("0");
	le_posY = new QLineEdit();
	le_posY->setValidator(posVal);
	le_posY->setText("0");
	le_posZ = new QLineEdit();
	le_posZ->setValidator(posVal);
	le_posZ->setText("0");
	lb_posX = new QLabel(tr("X"));
	lb_posY = new QLabel(tr("Y"));
	lb_posZ = new QLabel(tr("Z"));

	lightGrid->addWidget(lb_position, 2, 0);
	lightGrid->addWidget(lb_posX, 2, 1);
	lightGrid->addWidget(le_posX, 2, 2);
	lightGrid->addWidget(lb_posY, 2, 3);
	lightGrid->addWidget(le_posY, 2, 4);
	lightGrid->addWidget(lb_posZ, 2, 5);
	lightGrid->addWidget(le_posZ, 2, 6);

	//旋转
	lb_rotation = new QLabel(u8"旋转");
	le_rotX = new QLineEdit();
	le_rotX->setValidator(rotVal);
	le_rotX->setText("0");
	le_rotY = new QLineEdit();
	le_rotY->setValidator(rotVal);
	le_rotY->setText("0");
	le_rotZ = new QLineEdit();
	le_rotZ->setValidator(rotVal);
	le_rotZ->setText("0");
	lb_rotX = new QLabel(tr("X"));
	lb_rotY = new QLabel(tr("Y"));
	lb_rotZ = new QLabel(tr("Z"));

	lightGrid->addWidget(lb_rotation, 3, 0);
	lightGrid->addWidget(lb_rotX, 3, 1);
	lightGrid->addWidget(le_rotX, 3, 2);
	lightGrid->addWidget(lb_rotY, 3, 3);
	lightGrid->addWidget(le_rotY, 3, 4);
	lightGrid->addWidget(lb_rotZ, 3, 5);
	lightGrid->addWidget(le_rotZ, 3, 6);

	//颜色
	lb_color = new QLabel(u8"颜色");
	le_colorR = new QLineEdit();
	le_colorR->setValidator(colorVal);
	le_colorR->setText("0");
	le_colorG = new QLineEdit();
	le_colorG->setValidator(colorVal);
	le_colorG->setText("0");
	le_colorB = new QLineEdit();
	le_colorB->setValidator(colorVal);
	le_colorB->setText("0");
	lb_colorR = new QLabel(tr("R"));
	lb_colorG = new QLabel(tr("G"));
	lb_colorB = new QLabel(tr("B"));

	lightGrid->addWidget(lb_color, 4, 0);
	lightGrid->addWidget(lb_colorR, 4, 1);
	lightGrid->addWidget(le_colorR, 4, 2);
	lightGrid->addWidget(lb_colorG, 4, 3);
	lightGrid->addWidget(le_colorG, 4, 4);
	lightGrid->addWidget(lb_colorB, 4, 5);
	lightGrid->addWidget(le_colorB, 4, 6);

	btn_Ok = new QPushButton(u8"确定");
	btn_Ok->setFixedSize(50, 22);
	lightGrid->addWidget(btn_Ok, 5, 7);
	connect(btn_Ok, SIGNAL(clicked()), this, SLOT(do_btn_click()));
	lightGroupBox->setLayout(lightGrid);
}

pro_light::~pro_light() {
	SAFE_DELETE(lightGrid);
	SAFE_DELETE(lightGroupBox);

}

QGroupBox* pro_light::getGroupBox() {
	return lightGroupBox;
}


int pro_light::getLightType() {
	return cb_lightType->currentIndex();
}

void pro_light::setLightType(int type) {
	cb_lightType->setCurrentIndex(type);
}

int pro_light::getPosX() {
	return le_posX->text().toInt();
}

int pro_light::getPosY() {
	return le_posY->text().toInt();
}

int pro_light::getPosZ() {
	return le_posZ->text().toInt();
}

int pro_light::getRotX() {
	return le_rotX->text().toInt();
}

int pro_light::getRotY() {
	return le_rotY->text().toInt();
}

int pro_light::getRotZ() {
	return le_rotZ->text().toInt();
}

void pro_light::setPosX(int x) {
	le_posX->setText(QString::number(x));
}

void pro_light::setPosY(int y) {
	le_posY->setText(QString::number(y));
}

void pro_light::setPosZ(int z) {
	le_posZ->setText(QString::number(z));
}

void pro_light::setRotX(int x) {
	le_rotX->setText(QString::number(x));
}

void pro_light::setRotY(int y) {
	le_rotY->setText(QString::number(y));
}

void pro_light::setRotZ(int z) {
	le_rotZ->setText(QString::number(z));
}

QString pro_light::getName() {
	if (le_name)
		return le_name->text();
	else return "";
}

void pro_light::setName(QString name) {
	le_name->setText(name);
}

void pro_light::do_btn_click() {
	emit(btn_click());
}

void pro_light::setColorR(int r) {
	le_colorR->setText(QString::number(r));
}

void pro_light::setColorG(int g) {
	le_colorG->setText(QString::number(g));
}

void pro_light::setColorB(int b) {
	le_colorB->setText(QString::number(b));
}

int pro_light::getColorR() {
	return le_colorR->text().toInt();
}

int pro_light::getColorG() {
	return le_colorG->text().toInt();
}

int pro_light::getColorB() {
	return le_colorB->text().toInt();
}