#include "pro_xmodel.h"
#include "defines.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QIntValidator>
#include <QDoubleValidator>
pro_xModel::pro_xModel(QWidget * parent) : QWidget(parent) {
	xModelGrid = new QGridLayout;
	xModelGroupBox = new QGroupBox(u8"模型");

	QIntValidator *posVal = new QIntValidator(0, 10000, this);
	QIntValidator *rotVal = new QIntValidator(0, 360, this);
	QDoubleValidator *scalVal = new QDoubleValidator(0.0f, 100.0f, 1);
	lb_name = new QLabel(u8"名字");
	le_name = new QLineEdit();
	le_name->setText(u8"模型");
	
	xModelGrid->addWidget(lb_name, 0, 0);
	xModelGrid->addWidget(le_name, 0, 1);

	//位置
	lb_position = new QLabel(u8"位置");
	le_posX = new QLineEdit();
	le_posX->setValidator(posVal);
	le_posX->setText("0");
	le_posY = new QLineEdit();
	le_posY->setValidator(posVal);
	le_posY->setEnabled(false);
	le_posY->setText("0");
	le_posZ = new QLineEdit();
	le_posZ->setValidator(posVal);
	le_posZ->setText("0");
	lb_posX = new QLabel(tr("X"));
	lb_posY = new QLabel(tr("Y"));
	lb_posZ = new QLabel(tr("Z"));

	xModelGrid->addWidget(lb_position, 1, 0);
	xModelGrid->addWidget(lb_posX, 1, 2);
	xModelGrid->addWidget(le_posX, 1, 3);
	xModelGrid->addWidget(lb_posY, 1, 4);
	xModelGrid->addWidget(le_posY, 1, 5);
	xModelGrid->addWidget(lb_posZ, 1, 6);
	xModelGrid->addWidget(le_posZ, 1, 7);

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

	xModelGrid->addWidget(lb_rotation, 2, 0);
	xModelGrid->addWidget(lb_rotX, 2, 2);
	xModelGrid->addWidget(le_rotX, 2, 3);
	xModelGrid->addWidget(lb_rotY, 2, 4);
	xModelGrid->addWidget(le_rotY, 2, 5);
	xModelGrid->addWidget(lb_rotZ, 2, 6);
	xModelGrid->addWidget(le_rotZ, 2, 7);

	//缩放
	lb_scale = new QLabel(u8"缩放");
	le_scaleX = new QLineEdit();
	le_scaleX->setValidator(scalVal);
	le_scaleX->setText("1");
	le_scaleY = new QLineEdit();
	le_scaleY->setValidator(scalVal);
	le_scaleY->setText("1");
	le_scaleZ = new QLineEdit();
	le_scaleZ->setValidator(scalVal);
	le_scaleZ->setText("1");
	lb_scaleX = new QLabel(tr("X"));
	lb_scaleY = new QLabel(tr("Y"));
	lb_scaleZ = new QLabel(tr("Z"));

	xModelGrid->addWidget(lb_scale, 3, 0);
	xModelGrid->addWidget(lb_scaleX, 3, 2);
	xModelGrid->addWidget(le_scaleX, 3, 3);
	xModelGrid->addWidget(lb_scaleY, 3, 4);
	xModelGrid->addWidget(le_scaleY, 3, 5);
	xModelGrid->addWidget(lb_scaleZ, 3, 6);
	xModelGrid->addWidget(le_scaleZ, 3, 7);

	lb_fileName = new QLabel(u8"文件");
	le_fileName = new QLineEdit();
	le_fileName->setEnabled(false);
	btn_fileName = new QPushButton(u8"...");
	btn_fileName->setFixedSize(34, 22);
	btn_Ok = new QPushButton(u8"确定");
	btn_Ok->setFixedSize(50, 22);
	connect(btn_Ok, SIGNAL(clicked()), this, SLOT(do_btn_click()));
	connect(btn_fileName, SIGNAL(clicked()), this, SLOT(do_btn_fileName_click()));

	xModelGrid->addWidget(lb_fileName, 4, 0);
	xModelGrid->addWidget(le_fileName, 4, 1);
	xModelGrid->addWidget(btn_fileName, 4, 3);

	xModelGrid->addWidget(btn_Ok, 5, 7);

	xModelGroupBox->setLayout(xModelGrid);
}

pro_xModel::~pro_xModel() {
	SAFE_DELETE(lb_fileName);
	SAFE_DELETE(btn_fileName);
	SAFE_DELETE(btn_Ok);
	SAFE_DELETE(le_fileName);
	SAFE_DELETE(xModelGrid);
	SAFE_DELETE(xModelGroupBox);
}

QGroupBox* pro_xModel::getGroupBox() {
	return xModelGroupBox;
}

int pro_xModel::getPosX() {
	return le_posX->text().toInt();
}

int pro_xModel::getPosY() {
	return le_posY->text().toInt();
}

int pro_xModel::getPosZ() {
	return le_posZ->text().toInt();
}

int pro_xModel::getRotX() {
	return le_rotX->text().toInt();
}

int pro_xModel::getRotY() {
	return le_rotY->text().toInt();
}

int pro_xModel::getRotZ() {
	return le_rotZ->text().toInt();
}

void pro_xModel::setPosX(int x) {
	le_posX->setText(QString::number(x));
}

void pro_xModel::setPosY(int y) {
	le_posY->setText(QString::number(y));
}

void pro_xModel::setPosZ(int z) {
	le_posZ->setText(QString::number(z));
}

void pro_xModel::setRotX(int x) {
	le_rotX->setText(QString::number(x));
}

void pro_xModel::setRotY(int y) {
	le_rotY->setText(QString::number(y));
}

void pro_xModel::setRotZ(int z) {
	le_rotZ->setText(QString::number(z));
}

QString pro_xModel::getName() {
	if (le_name)
		return le_name->text();
	else return "";
}

void pro_xModel::setName(QString name) {
	le_name->setText(name);
}

QString pro_xModel::getFileName() {
	if (le_fileName)
		return le_fileName->text();
	else return "";
}

void pro_xModel::setFileName(QString name) {
	le_fileName->setText(name);
}

void pro_xModel::do_btn_click() {
	emit(btn_click());
}

void pro_xModel::do_btn_fileName_click() {
	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		u8"选择模型",
		"",
		tr("xModel (*.x)")); //选择路径  
	if (filename.isEmpty())
	{
		return;
	}
	else
	{
		setFileName(filename);
	}
}

float pro_xModel::getScaleX() {
	return le_scaleX->text().toFloat();
}

float pro_xModel::getScaleY() {
	return le_scaleY->text().toFloat();

}

float pro_xModel::getScaleZ() {
	return le_scaleZ->text().toFloat();

}

void pro_xModel::setScaleX(float x) {
	le_scaleX->setText(QString::number(x));
}

void pro_xModel::setScaleY(float y) {
	le_scaleY->setText(QString::number(y));

}

void pro_xModel::setScaleZ(float z) {
	le_scaleZ->setText(QString::number(z));

}
