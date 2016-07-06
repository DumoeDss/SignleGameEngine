#include "pro_sprite.h"
#include "defines.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIntValidator>
#include <QFileDialog>
pro_sprite::pro_sprite(QWidget * parent) : QWidget(parent) {
	spriteGrid = new QGridLayout;
	spriteGroupBox = new QGroupBox(u8"UI精灵");

	lb_name = new QLabel(u8"名字");
	le_name = new QLineEdit();
	le_name->setText(u8"精灵");
	
	spriteGrid->addWidget(lb_name, 0, 0);
	spriteGrid->addWidget(le_name, 0, 1);

	lb_background = new QLabel(u8"背景");
	le_background = new QLineEdit();
	lb_posX = new QLabel(u8"X");
	le_posX = new QLineEdit();
	lb_posY = new QLabel(u8"Y");
	le_posY = new QLineEdit();
	le_background->setEnabled(false);
	btn_background = new QPushButton(u8"...");
	btn_background->setFixedSize(34, 22);
	btn_Ok = new QPushButton(u8"确定");
	btn_Ok->setFixedSize(50, 22);
	connect(btn_Ok, SIGNAL(clicked()), this, SLOT(do_btn_click()));
	connect(btn_background, SIGNAL(clicked()), this, SLOT(do_btn_fileName_click()));

	spriteGrid->addWidget(lb_background, 1, 0);
	spriteGrid->addWidget(le_background, 1, 1);
	spriteGrid->addWidget(btn_background, 1, 2);

	spriteGrid->addWidget(lb_posX, 2, 0);
	spriteGrid->addWidget(le_posX, 2, 1);

	spriteGrid->addWidget(lb_posY, 3, 0);
	spriteGrid->addWidget(le_posY, 3, 1);

	spriteGrid->addWidget(btn_Ok, 4, 3);

	spriteGroupBox->setLayout(spriteGrid);
}

pro_sprite::~pro_sprite() {
	SAFE_DELETE(le_background);
	SAFE_DELETE(le_posX);
	SAFE_DELETE(le_posY);	
	SAFE_DELETE(lb_background);
	SAFE_DELETE(btn_background);
	SAFE_DELETE(lb_posX);
	SAFE_DELETE(lb_posY);
	SAFE_DELETE(btn_Ok);
	SAFE_DELETE(spriteGrid);
	SAFE_DELETE(spriteGroupBox);
}

QGroupBox* pro_sprite::getGroupBox() {
	return spriteGroupBox;
}

QString pro_sprite::getName() {
	if (le_name)
		return le_name->text();
	else return "";
}

void pro_sprite::setName(QString name) {
	le_name->setText(name);
}

void pro_sprite::do_btn_click() {
	emit(btn_click());
}

void pro_sprite::do_btn_fileName_click() {
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
		setFileName(filename);
	}
}


QString pro_sprite::getFileName() {
	return le_background->text();
}

void pro_sprite::setFileName(QString name) {
	le_background->setText(name);
}

void pro_sprite::setPosX(int x) {
	le_posX->setText(QString::number(x));
}

void pro_sprite::setPosY(int y) {
	le_posY->setText(QString::number(y));

}

int pro_sprite::getPosX() {
	return le_posX->text().toInt();
}

int pro_sprite::getPosY() {
	return le_posY->text().toInt();

}
