#include "pro_sphere.h"
#include "defines.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIntValidator>
#include <QDoubleValidator>
pro_sphere::pro_sphere(QWidget * parent) : QWidget(parent) {
	sphereGrid = new QGridLayout;
	sphereGroupBox = new QGroupBox(u8"球体");

	QIntValidator *posVal = new QIntValidator(0, 10000, this);
	QIntValidator *rotVal = new QIntValidator(0, 360, this);
	QIntValidator *colorVal = new QIntValidator(0, 255, this);
	QDoubleValidator *scalVal = new QDoubleValidator(0.0f, 100.0f, 1);
	lb_name = new QLabel(u8"名字");
	le_name = new QLineEdit();
	le_name->setText(u8"球体");
	
	sphereGrid->addWidget(lb_name, 0, 0);
	sphereGrid->addWidget(le_name, 0, 2);

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

	sphereGrid->addWidget(lb_position, 1, 0);
	sphereGrid->addWidget(lb_posX, 1, 1);
	sphereGrid->addWidget(le_posX, 1, 2);
	sphereGrid->addWidget(lb_posY, 1, 3);
	sphereGrid->addWidget(le_posY, 1, 4);
	sphereGrid->addWidget(lb_posZ, 1, 5);
	sphereGrid->addWidget(le_posZ, 1, 6);

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

	sphereGrid->addWidget(lb_rotation, 2, 0);
	sphereGrid->addWidget(lb_rotX, 2, 1);
	sphereGrid->addWidget(le_rotX, 2, 2);
	sphereGrid->addWidget(lb_rotY, 2, 3);
	sphereGrid->addWidget(le_rotY, 2, 4);
	sphereGrid->addWidget(lb_rotZ, 2, 5);
	sphereGrid->addWidget(le_rotZ, 2, 6);
	//缩放
	lb_scale = new QLabel(u8"缩放");
	le_scaleX = new QLineEdit();
	le_scaleX->setValidator(scalVal);
	le_scaleX->setText("0");
	le_scaleY = new QLineEdit();
	le_scaleY->setValidator(scalVal);
	le_scaleY->setText("0");
	le_scaleZ = new QLineEdit();
	le_scaleZ->setValidator(scalVal);
	le_scaleZ->setText("0");
	lb_scaleX = new QLabel(tr("X"));
	lb_scaleY = new QLabel(tr("Y"));
	lb_scaleZ = new QLabel(tr("Z"));

	sphereGrid->addWidget(lb_scale, 3, 0);
	sphereGrid->addWidget(lb_scaleX, 3, 1);
	sphereGrid->addWidget(le_scaleX, 3, 2);
	sphereGrid->addWidget(lb_scaleY, 3, 3);
	sphereGrid->addWidget(le_scaleY, 3, 4);
	sphereGrid->addWidget(lb_scaleZ, 3, 5);
	sphereGrid->addWidget(le_scaleZ, 3, 6);

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

	sphereGrid->addWidget(lb_color, 4, 0);
	sphereGrid->addWidget(lb_colorR, 4, 1);
	sphereGrid->addWidget(le_colorR, 4, 2);
	sphereGrid->addWidget(lb_colorG, 4, 3);
	sphereGrid->addWidget(le_colorG, 4, 4);
	sphereGrid->addWidget(lb_colorB, 4, 5);
	sphereGrid->addWidget(le_colorB, 4, 6);

	btn_Ok = new QPushButton(u8"确定");
	btn_Ok->setFixedSize(50, 22);
	sphereGrid->addWidget(btn_Ok, 5, 7);
	connect(btn_Ok, SIGNAL(clicked()), this, SLOT(do_btn_click()));
	sphereGroupBox->setLayout(sphereGrid);
}

pro_sphere::~pro_sphere() {

	SAFE_DELETE(sphereGrid);
	SAFE_DELETE(sphereGroupBox);
}

QGroupBox* pro_sphere::getGroupBox() {
	return sphereGroupBox;
}

int pro_sphere::getPosX() {
	return le_posX->text().toInt();
}

int pro_sphere::getPosY() {
	return le_posY->text().toInt();
}

int pro_sphere::getPosZ() {
	return le_posZ->text().toInt();
}

int pro_sphere::getRotX() {
	return le_rotX->text().toInt();
}

int pro_sphere::getRotY() {
	return le_rotY->text().toInt();
}

int pro_sphere::getRotZ() {
	return le_rotZ->text().toInt();
}

void pro_sphere::setPosX(int x) {
	le_posX->setText(QString::number(x));
}

void pro_sphere::setPosY(int y) {
	le_posY->setText(QString::number(y));
}

void pro_sphere::setPosZ(int z) {
	le_posZ->setText(QString::number(z));
}

void pro_sphere::setRotX(int x) {
	le_rotX->setText(QString::number(x));
}

void pro_sphere::setRotY(int y) {
	le_rotY->setText(QString::number(y));
}

void pro_sphere::setRotZ(int z) {
	le_rotZ->setText(QString::number(z));
}

QString pro_sphere::getName() {
	if (le_name)
		return le_name->text();
	else return "";
}

void pro_sphere::setName(QString name) {
	le_name->setText(name);
}

void pro_sphere::do_btn_click() {
	emit(btn_click());
}


float pro_sphere::getScaleX() {
	return le_scaleX->text().toFloat();
}

float pro_sphere::getScaleY() {
	return le_scaleY->text().toFloat();

}

float pro_sphere::getScaleZ() {
	return le_scaleZ->text().toFloat();

}

void pro_sphere::setScaleX(float x) {
	le_scaleX->setText(QString::number(x));
}

void pro_sphere::setScaleY(float y) {
	le_scaleY->setText(QString::number(y));

}

void pro_sphere::setScaleZ(float z) {
	le_scaleZ->setText(QString::number(z));

}

void pro_sphere::setColorR(int r) {
	le_colorR->setText(QString::number(r));
}

void pro_sphere::setColorG(int g) {
	le_colorG->setText(QString::number(g));
}

void pro_sphere::setColorB(int b) {
	le_colorB->setText(QString::number(b));
}

int pro_sphere::getColorR() {
	return le_colorR->text().toInt();
}

int pro_sphere::getColorG() {
	return le_colorG->text().toInt();
}

int pro_sphere::getColorB() {
	return le_colorB->text().toInt();
}