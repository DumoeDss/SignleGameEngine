#include "pro_particle.h"
#include "defines.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIntValidator>
#include <QComboBox>
#include <QFileDialog>
pro_particle::pro_particle(QWidget * parent) : QWidget(parent) {
	particleGrid = new QGridLayout;
	particleGroupBox = new QGroupBox(u8"粒子");
	QIntValidator *posVal = new QIntValidator(0, 10000, this);
	QIntValidator *numVal = new QIntValidator(0, 10000, this);

	lb_name = new QLabel(u8"名字");
	le_name = new QLineEdit();
	le_name->setText(u8"粒子");
	lb_position =  new QLabel(u8"位置");
	lb_posX = new QLabel(tr("X"));
	lb_posY = new QLabel(tr("Y"));
	lb_posZ = new QLabel(tr("Z"));
	le_posX = new QLineEdit();
	le_posX->setValidator(posVal);
	le_posX->setText("0");
	le_posY = new QLineEdit();
	le_posY->setValidator(posVal);
	le_posY->setText("0");
	le_posZ = new QLineEdit();
	le_posZ->setValidator(posVal);
	le_posZ->setText("0");

	lb_length = new QLabel(u8"长度");
	lb_width = new QLabel(u8"宽度");
	lb_height = new QLabel(u8"高度");

	le_length = new QLineEdit();
	le_length->setValidator(posVal);
	le_length->setText("0");
	le_width = new QLineEdit();
	le_width->setValidator(posVal);
	le_width->setText("0");
	le_height = new QLineEdit();
	le_height->setValidator(posVal);
	le_height->setText("0");

	lb_fileName = new QLabel(u8"贴图");
	le_fileName = new QLineEdit();
	le_fileName->setEnabled(false);
	btn_fileName = new QPushButton(u8"...");
	btn_fileName->setFixedSize(34, 22);

	lb_num = new QLabel(u8"数量");
	le_num = new QLineEdit();
	le_num->setValidator(numVal);
	le_num->setText("0");

	lb_particleType = new QLabel(u8"类型");
	cb_particleType = new QComboBox();
	cb_particleType->addItem(u8"雨雪");
	cb_particleType->addItem(u8"爆炸");
	

	btn_Ok = new QPushButton(u8"确定");
	btn_Ok->setFixedSize(50, 22);
	connect(btn_Ok, SIGNAL(clicked()), this, SLOT(do_btn_click()));
	connect(btn_fileName, SIGNAL(clicked()), this, SLOT(do_btn_fileName_click()));
	//名字
	particleGrid->addWidget(lb_name, 0, 0);
	particleGrid->addWidget(le_name, 0, 1);
	//类型
	particleGrid->addWidget(lb_particleType, 1, 0);
	particleGrid->addWidget(cb_particleType, 1, 1);
	//数量
	particleGrid->addWidget(lb_num, 2, 0);
	particleGrid->addWidget(le_num, 2, 1);
	//纹理贴图
	particleGrid->addWidget(lb_fileName, 3, 0);
	particleGrid->addWidget(le_fileName, 3, 1);
	particleGrid->addWidget(btn_fileName, 3, 3);
	//位置
	particleGrid->addWidget(lb_position, 4, 0);
	particleGrid->addWidget(lb_posX, 4, 2);
	particleGrid->addWidget(le_posX, 4, 3);
	particleGrid->addWidget(lb_posY, 4, 4);
	particleGrid->addWidget(le_posY, 4, 5);
	particleGrid->addWidget(lb_posZ, 4, 6);
	particleGrid->addWidget(le_posZ, 4, 7);
	//范围
	particleGrid->addWidget(lb_length, 5, 0);
	particleGrid->addWidget(le_length, 5, 1);
	particleGrid->addWidget(lb_width, 6, 0);
	particleGrid->addWidget(le_width, 6, 1);
	particleGrid->addWidget(lb_height, 7, 0);
	particleGrid->addWidget(le_height, 7, 1);

	particleGrid->addWidget(btn_Ok, 8, 7);
	
	particleGroupBox->setLayout(particleGrid);
}

pro_particle::~pro_particle() {
	SAFE_DELETE(lb_position);
	SAFE_DELETE(lb_posX);
	SAFE_DELETE(lb_posY);
	SAFE_DELETE(lb_posZ);
	SAFE_DELETE(le_posX);
	SAFE_DELETE(le_posY);
	SAFE_DELETE(le_posZ);
	SAFE_DELETE(lb_length);
	SAFE_DELETE(lb_width);
	SAFE_DELETE(lb_height);
	SAFE_DELETE(le_length);
	SAFE_DELETE(le_width);
	SAFE_DELETE(le_height);
	SAFE_DELETE(lb_num);
	SAFE_DELETE(le_num);
	SAFE_DELETE(lb_fileName);
	SAFE_DELETE(btn_fileName);
	SAFE_DELETE(le_fileName);
	SAFE_DELETE(lb_name);
	SAFE_DELETE(le_name);
	SAFE_DELETE(lb_particleType);
	SAFE_DELETE(cb_particleType);
	SAFE_DELETE(btn_Ok);

	SAFE_DELETE(particleGrid);
	SAFE_DELETE(particleGroupBox);
}

QGroupBox* pro_particle::getGroupBox() {
	return particleGroupBox;
}

int pro_particle::getPosX() {
	return le_posX->text().toInt();
}

int pro_particle::getPosY() {
	return le_posY->text().toInt();
}

int pro_particle::getPosZ() {
	return le_posZ->text().toInt();
}

int pro_particle::getLength() {
	return le_length->text().toInt();
}

int pro_particle::getWidth() {
	return le_width->text().toInt();
}

int pro_particle::getHeight() {
	return le_height->text().toInt();
}

void pro_particle::setPosX(int x) {
	le_posX->setText(QString::number(x));
}

void pro_particle::setPosY(int y) {
	le_posY->setText(QString::number(y));
}

void pro_particle::setPosZ(int z) {
	le_posZ->setText(QString::number(z));
}

void pro_particle::setLength(int x) {
	le_length->setText(QString::number(x));
}

void pro_particle::setWidth(int y) {
	le_width->setText(QString::number(y));
}

void pro_particle::setHeight(int z) {
	le_height->setText(QString::number(z));
}

QString pro_particle::getName() {
	if (le_name)
		return le_name->text();
	else return "";
}

void pro_particle::setName(QString name) {
	le_name->setText(name);
}

void pro_particle::do_btn_click() {
	emit(btn_click());
}

void pro_particle::do_btn_fileName_click() {
	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		u8"选择纹理贴图",
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF)")); //选择路径  
	if (filename.isEmpty())
	{
		return;
	}
	else
	{
		setFileName(filename);
	}
}


QString pro_particle::getFileName() {
	return le_fileName->text();
}

void pro_particle::setFileName(QString name) {
	le_fileName->setText(name);
}

int pro_particle::getNum() {
	return le_num->text().toInt();
}

int pro_particle::getType() {
	return cb_particleType->currentIndex();
}

void pro_particle::setNum(int num) {
	le_num->setText(QString::number(num));
}

void pro_particle::setType(int type) {
	cb_particleType->setCurrentIndex(type);
}
