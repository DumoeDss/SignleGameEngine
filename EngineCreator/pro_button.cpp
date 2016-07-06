#include "pro_button.h"
#include "defines.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIntValidator>
#include <QFileDialog>
pro_button::pro_button(QWidget * parent) : QWidget(parent) {
	buttonGrid = new QGridLayout;
	buttonGroupBox = new QGroupBox(u8"按钮");

	lb_name = new QLabel(u8"名字");
	le_name = new QLineEdit();
	le_name->setText(u8"按钮");
	
	buttonGrid->addWidget(lb_name, 0, 0);
	buttonGrid->addWidget(le_name, 0, 1);

	lb_bgUp = new QLabel(u8"Up");
	le_bgUp = new QLineEdit();
	le_bgUp->setEnabled(false);
	btn_bgUp = new QPushButton(u8"...");
	btn_bgUp->setFixedSize(34, 22);

	lb_bgDown = new QLabel(u8"Down");
	le_bgDown = new QLineEdit();
	le_bgDown->setEnabled(false);
	btn_bgDown = new QPushButton(u8"...");
	btn_bgDown->setFixedSize(34, 22);

	lb_bgMove = new QLabel(u8"Move");
	le_bgMove = new QLineEdit();
	le_bgMove->setEnabled(false);
	btn_bgMove = new QPushButton(u8"...");
	btn_bgMove->setFixedSize(34, 22);

	lb_posX = new QLabel(u8"X");
	le_posX = new QLineEdit();
	lb_posY = new QLabel(u8"Y");
	le_posY = new QLineEdit();
	
	btn_Ok = new QPushButton(u8"确定");
	btn_Ok->setFixedSize(50, 22);
	connect(btn_Ok, SIGNAL(clicked()), this, SLOT(do_btn_click()));
	connect(btn_bgUp, SIGNAL(clicked()), this, SLOT(do_btn_up_click()));
	connect(btn_bgDown, SIGNAL(clicked()), this, SLOT(do_btn_down_click()));
	connect(btn_bgMove, SIGNAL(clicked()), this, SLOT(do_btn_move_click()));

	buttonGrid->addWidget(lb_bgUp, 1, 0);
	buttonGrid->addWidget(le_bgUp, 1, 1);
	buttonGrid->addWidget(btn_bgUp, 1, 2);

	buttonGrid->addWidget(lb_bgDown, 2, 0);
	buttonGrid->addWidget(le_bgDown, 2, 1);
	buttonGrid->addWidget(btn_bgDown, 2, 2);

	buttonGrid->addWidget(lb_bgMove, 3, 0);
	buttonGrid->addWidget(le_bgMove, 3, 1);
	buttonGrid->addWidget(btn_bgMove, 3, 2);

	buttonGrid->addWidget(lb_posX, 4, 0);
	buttonGrid->addWidget(le_posX, 4, 1);

	buttonGrid->addWidget(lb_posY, 5, 0);
	buttonGrid->addWidget(le_posY, 5, 1);

	buttonGrid->addWidget(btn_Ok, 6, 3);

	buttonGroupBox->setLayout(buttonGrid);
}

pro_button::~pro_button() {
	SAFE_DELETE(le_bgUp);
	SAFE_DELETE(le_bgDown);
	SAFE_DELETE(le_bgMove);
	SAFE_DELETE(le_posX);
	SAFE_DELETE(le_posY);
	SAFE_DELETE(lb_bgUp);
	SAFE_DELETE(btn_bgUp);
	SAFE_DELETE(lb_bgDown);
	SAFE_DELETE(btn_bgDown);
	SAFE_DELETE(lb_bgMove);
	SAFE_DELETE(btn_bgMove);
	SAFE_DELETE(lb_posX);
	SAFE_DELETE(lb_posY);
	SAFE_DELETE(btn_Ok);
	SAFE_DELETE(buttonGrid);
	SAFE_DELETE(buttonGroupBox);
}

QGroupBox* pro_button::getGroupBox() {
	return buttonGroupBox;
}

QString pro_button::getName() {
	if (le_name)
		return le_name->text();
	else return "";
}

void pro_button::setName(QString name) {
	le_name->setText(name);
}

void pro_button::do_btn_click() {
	emit(btn_click());
}

void pro_button::do_btn_up_click() {
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
		set_up_name(filename);
	}
}

void pro_button::do_btn_down_click() {
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
		set_down_name(filename);
	}
}

void pro_button::do_btn_move_click() {
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
		set_move_name(filename);
	}
}

QString pro_button::get_up_name() {
	return le_bgUp->text();
}

void pro_button::set_up_name(QString name) {
	le_bgUp->setText(name);
}

QString pro_button::get_down_name() {
	return le_bgDown->text();
}

void pro_button::set_down_name(QString name) {
	le_bgDown->setText(name);
}

QString pro_button::get_move_name() {
	return le_bgMove->text();
}

void pro_button::set_move_name(QString name) {
	le_bgMove->setText(name);
}

void pro_button::setPosX(int x) {
	le_posX->setText(QString::number(x));
}

void pro_button::setPosY(int y) {
	le_posY->setText(QString::number(y));

}

int pro_button::getPosX() {
	return le_posX->text().toInt();
}

int pro_button::getPosY() {
	return le_posY->text().toInt();

}
