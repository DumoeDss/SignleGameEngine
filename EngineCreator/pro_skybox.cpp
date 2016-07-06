#include "pro_skybox.h"
#include "defines.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIntValidator>
#include <QFileDialog>
pro_skyBox::pro_skyBox(QWidget * parent) : QWidget(parent) {
	QIntValidator *skyVal = new QIntValidator(0, 100000, this);
	skyBoxGrid = new QGridLayout;
	skyBoxGroupBox = new QGroupBox(u8"天空盒");	

	lb_skyLen = new QLabel(u8"边长");
	le_skyLen = new QLineEdit();
	le_skyLen->setValidator(skyVal);
	btn_Ok = new QPushButton(u8"确定");
	btn_Ok->setFixedSize(50, 22);
	connect(btn_Ok, SIGNAL(clicked()), this, SLOT(do_btn_click()));
	
	lb_skyFront = new QLabel(u8"前");
	le_skyFront = new QLineEdit();
	le_skyFront->setEnabled(false);
	btn_skyFront = new QPushButton(u8"...");
	btn_skyFront->setFixedSize(34, 22);

	lb_skyBack = new QLabel(u8"后");
	le_skyBack = new QLineEdit();
	le_skyBack->setEnabled(false);
	btn_skyBack = new QPushButton(u8"...");
	btn_skyBack->setFixedSize(34, 22);

	lb_skyLeft = new QLabel(u8"左");
	le_skyLeft = new QLineEdit();
	le_skyLeft->setEnabled(false);
	btn_skyLeft = new QPushButton(u8"...");
	btn_skyLeft->setFixedSize(34, 22);

	lb_skyRight = new QLabel(u8"右");
	le_skyRight = new QLineEdit();
	le_skyRight->setEnabled(false);
	btn_skyRight = new QPushButton(u8"...");
	btn_skyRight->setFixedSize(34, 22);

	lb_skyTop = new QLabel(u8"上");
	le_skyTop = new QLineEdit();
	le_skyTop->setEnabled(false);
	btn_skyTop = new QPushButton(u8"...");
	btn_skyTop->setFixedSize(34, 22);

	skyBoxGrid->addWidget(lb_skyLen, 0, 0);
	skyBoxGrid->addWidget(le_skyLen, 0, 1);

	skyBoxGrid->addWidget(lb_skyFront, 1, 0);
	skyBoxGrid->addWidget(le_skyFront, 1, 1);
	skyBoxGrid->addWidget(btn_skyFront, 1, 2);

	skyBoxGrid->addWidget(lb_skyBack, 2, 0);
	skyBoxGrid->addWidget(le_skyBack, 2, 1);
	skyBoxGrid->addWidget(btn_skyBack, 2, 2);

	skyBoxGrid->addWidget(lb_skyLeft, 3, 0);
	skyBoxGrid->addWidget(le_skyLeft, 3, 1);
	skyBoxGrid->addWidget(btn_skyLeft, 3, 2);

	skyBoxGrid->addWidget(lb_skyRight, 4, 0);
	skyBoxGrid->addWidget(le_skyRight, 4, 1);
	skyBoxGrid->addWidget(btn_skyRight, 4, 2);

	skyBoxGrid->addWidget(lb_skyTop, 5, 0);
	skyBoxGrid->addWidget(le_skyTop, 5, 1);
	skyBoxGrid->addWidget(btn_skyTop, 5, 2);

	skyBoxGrid->addWidget(btn_Ok, 6, 3);

	connect(btn_skyFront, SIGNAL(clicked()), this, SLOT(do_btn_front_click()));
	connect(btn_skyBack, SIGNAL(clicked()), this, SLOT(do_btn_back_click()));
	connect(btn_skyLeft, SIGNAL(clicked()), this, SLOT(do_btn_left_click()));
	connect(btn_skyRight, SIGNAL(clicked()), this, SLOT(do_btn_right_click()));
	connect(btn_skyTop, SIGNAL(clicked()), this, SLOT(do_btn_top_click()));

	skyBoxGroupBox->setLayout(skyBoxGrid);
}

pro_skyBox::~pro_skyBox() {
	SAFE_DELETE(le_skyLen);
	SAFE_DELETE(le_skyFront);
	SAFE_DELETE(le_skyBack);
	SAFE_DELETE(le_skyLeft);
	SAFE_DELETE(le_skyRight);
	SAFE_DELETE(lb_skyLen);
	SAFE_DELETE(btn_Ok);
	SAFE_DELETE(lb_skyFront);
	SAFE_DELETE(btn_skyFront);
	SAFE_DELETE(lb_skyBack);
	SAFE_DELETE(btn_skyBack);
	SAFE_DELETE(lb_skyLeft);
	SAFE_DELETE(btn_skyLeft);
	SAFE_DELETE(lb_skyRight);
	SAFE_DELETE(btn_skyRight);
	SAFE_DELETE(lb_skyTop);
	SAFE_DELETE(btn_skyTop);
	SAFE_DELETE(skyBoxGrid);
	SAFE_DELETE(skyBoxGroupBox);
}

QGroupBox* pro_skyBox::getGroupBox() {
	return skyBoxGroupBox;
}

int pro_skyBox::getSkyBoxLength() {
	return le_skyLen->text().toInt();
}

QString pro_skyBox::getSkyBoxFront() {
	return le_skyFront->text();
}

QString pro_skyBox::getSkyBoxBack() {
	return le_skyBack->text();
}

QString pro_skyBox::getSkyBoxLeft() {
	return le_skyLeft->text();
}

QString pro_skyBox::getSkyBoxRight() {
	return le_skyRight->text();
}

QString pro_skyBox::getSkyBoxTop() {
	return le_skyTop->text();
}


void pro_skyBox::setSkyBoxLength(int length) {
	le_skyLen->setText(QString::number(length));
}

void pro_skyBox::setSkyBoxFront(QString front) {
	le_skyFront->setText(front);
}

void pro_skyBox::setSkyBoxBack(QString back) {
	le_skyBack->setText(back);
}

void pro_skyBox::setSkyBoxLeft(QString left) {
	le_skyLeft->setText(left);
}

void pro_skyBox::setSkyBoxRight(QString right) {
	le_skyRight->setText(right);
}

void pro_skyBox::setSkyBoxTop(QString top) {
	le_skyTop->setText(top);
}

void pro_skyBox::do_btn_click() {
	emit(btn_click());
}

void pro_skyBox::do_btn_front_click() {
	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		u8"选择贴图",
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF)")); //选择路径  
	if (filename.isEmpty())
	{
		return;
	}
	else
	{
		setSkyBoxFront(filename);
	}
}

void pro_skyBox::do_btn_back_click() {
	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		u8"选择贴图",
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF)")); //选择路径  
	if (filename.isEmpty())
	{
		return;
	}
	else
	{
		setSkyBoxBack(filename);
	}
}

void pro_skyBox::do_btn_left_click() {
	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		u8"选择贴图",
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF)")); //选择路径  
	if (filename.isEmpty())
	{
		return;
	}
	else
	{
		setSkyBoxLeft(filename);
	}
}

void pro_skyBox::do_btn_right_click() {
	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		u8"选择贴图",
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF)")); //选择路径  
	if (filename.isEmpty())
	{
		return;
	}
	else
	{
		setSkyBoxRight(filename);
	}
}

void pro_skyBox::do_btn_top_click() {
	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		u8"选择贴图",
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF)")); //选择路径  
	if (filename.isEmpty())
	{
		return;
	}
	else
	{
		setSkyBoxTop(filename);
	}
}
