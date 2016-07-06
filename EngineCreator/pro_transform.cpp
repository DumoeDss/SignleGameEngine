#include "pro_transform.h"
#include "defines.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIntValidator>

pro_transform::pro_transform(QWidget * parent) : QWidget(parent) {

	QIntValidator *posVal = new QIntValidator(0, 10000, this);
	QIntValidator *rotVal = new QIntValidator(0, 360, this);

	transGrid = new QGridLayout;
	transGroupBox = new QGroupBox(u8"变换");
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

	transGrid->addWidget(lb_position, 0, 0);
	transGrid->addWidget(lb_posX, 0, 1);
	transGrid->addWidget(le_posX, 0, 2);
	transGrid->addWidget(lb_posY, 0, 3);
	transGrid->addWidget(le_posY, 0, 4);
	transGrid->addWidget(lb_posZ, 0, 5);
	transGrid->addWidget(le_posZ, 0, 6);

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

	transGrid->addWidget(lb_rotation, 1, 0);
	transGrid->addWidget(lb_rotX, 1, 1);
	transGrid->addWidget(le_rotX, 1, 2);
	transGrid->addWidget(lb_rotY, 1, 3);
	transGrid->addWidget(le_rotY, 1, 4);
	transGrid->addWidget(lb_rotZ, 1, 5);
	transGrid->addWidget(le_rotZ, 1, 6);

	btn_Ok = new QPushButton(u8"确定");
	btn_Ok->setEnabled(false);
	btn_Ok->setFixedSize(50, 22);
	transGrid->addWidget(btn_Ok, 2, 7);

	//缩放
	//QLabel *lb_scale = new QLabel(tr("Scale"));
	/*QLineEdit *le_scaX = new QLineEdit();
	QLineEdit *le_scaY = new QLineEdit();
	QLineEdit *le_scaZ = new QLineEdit();
	QLabel *lb_scaX = new QLabel(tr("X"));
	QLabel *lb_scaY = new QLabel(tr("Y"));
	QLabel *lb_scaZ = new QLabel(tr("Z"));*/
	/*transGrid->addWidget(lb_scale, 2, 0);
	transGrid->addWidget(lb_scaX, 2, 1);
	transGrid->addWidget(le_scaX, 2, 2);
	transGrid->addWidget(lb_scaY, 2, 3);
	transGrid->addWidget(le_scaY, 2, 4);
	transGrid->addWidget(lb_scaZ, 2, 5);
	transGrid->addWidget(le_scaZ, 2, 6);*/
	transGroupBox->setLayout(transGrid);

	connect(le_posX, SIGNAL(textChanged(const QString &)), this, SLOT(changeBtnState()));
	connect(le_posY, SIGNAL(textChanged(const QString &)), this, SLOT(changeBtnState()));
	connect(le_posZ, SIGNAL(textChanged(const QString &)), this, SLOT(changeBtnState()));
	connect(le_rotX, SIGNAL(textChanged(const QString &)), this, SLOT(changeBtnState()));
	connect(le_rotY, SIGNAL(textChanged(const QString &)), this, SLOT(changeBtnState()));
	connect(le_rotZ, SIGNAL(textChanged(const QString &)), this, SLOT(changeBtnState()));
	connect(btn_Ok, SIGNAL(clicked()), this, SLOT(btnClicked()));
}

pro_transform::~pro_transform() {
	SAFE_DELETE(btn_Ok);
	SAFE_DELETE(le_posX);
	SAFE_DELETE(le_posY);
	SAFE_DELETE(le_posZ);
	SAFE_DELETE(le_rotX);
	SAFE_DELETE(le_rotY);
	SAFE_DELETE(le_rotZ);
	SAFE_DELETE(transGrid);
	SAFE_DELETE(transGroupBox);	
}

QGroupBox *pro_transform::getGroupBox() {
	return transGroupBox;
}

void pro_transform::changeBtnState() {
	if(!btn_Ok->isEnabled())
		btn_Ok->setEnabled(true);
}

void pro_transform::btnClicked() {
	btn_Ok->setEnabled(false);
}

int pro_transform::getPosX() {
	return le_posX->text().toInt();
}

int pro_transform::getPosY() {
	return le_posY->text().toInt();
}

int pro_transform::getPosZ() {
	return le_posZ->text().toInt();
}

int pro_transform::getRotX() {
	return le_rotX->text().toInt();
}

int pro_transform::getRotY() {
	return le_rotY->text().toInt();
}

int pro_transform::getRotZ() {
	return le_rotZ->text().toInt();
}

void pro_transform::setPosX(int x) {
	le_posX->setText(QString::number(x));
}

void pro_transform::setPosY(int y) {
	le_posY->setText(QString::number(y));
}

void pro_transform::setPosZ(int z) {
	le_posZ->setText(QString::number(z));
}

void pro_transform::setRotX(int x) {
	le_rotX->setText(QString::number(x));
}

void pro_transform::setRotY(int y) {
	le_rotY->setText(QString::number(y));
}

void pro_transform::setRotZ(int z) {
	le_rotZ->setText(QString::number(z));
}

