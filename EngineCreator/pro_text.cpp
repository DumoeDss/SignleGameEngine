#include "pro_text.h"
#include "defines.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIntValidator>
pro_text::pro_text(QWidget * parent) : QWidget(parent) {
	textGrid = new QGridLayout;
	textGroupBox = new QGroupBox(u8"UI文本");

	lb_name = new QLabel(u8"名字");
	le_name = new QLineEdit();
	le_name->setText(u8"UI文本");
	
	textGrid->addWidget(lb_name, 0, 0);
	textGrid->addWidget(le_name, 0, 1);

	lb_text = new QLabel(u8"文字");
	le_text = new QLineEdit();
	lb_colorR = new QLabel(u8"R");
	le_colorR = new QLineEdit();
	lb_colorG = new QLabel(u8"G");
	le_colorG = new QLineEdit();
	lb_colorB = new QLabel(u8"B");
	le_colorB = new QLineEdit();
	lb_posX = new QLabel(u8"X");
	le_posX = new QLineEdit();
	lb_posY = new QLabel(u8"Y");
	le_posY = new QLineEdit();

	btn_Ok = new QPushButton(u8"确定");
	btn_Ok->setFixedSize(50, 22);
	connect(btn_Ok, SIGNAL(clicked()), this, SLOT(do_btn_click()));

	textGrid->addWidget(lb_text, 1, 0);
	textGrid->addWidget(le_text, 1, 1);

	textGrid->addWidget(lb_colorR, 2, 0);
	textGrid->addWidget(le_colorR, 2, 1);

	textGrid->addWidget(lb_colorG, 2, 2);
	textGrid->addWidget(le_colorG, 2, 3);

	textGrid->addWidget(lb_colorB, 2, 4);
	textGrid->addWidget(le_colorB, 2, 5);

	textGrid->addWidget(lb_posX, 3, 0);
	textGrid->addWidget(le_posX, 3, 1);

	textGrid->addWidget(lb_posY, 3, 2);
	textGrid->addWidget(le_posY, 3, 3);

	textGrid->addWidget(btn_Ok, 4, 5);

	textGroupBox->setLayout(textGrid);
}

pro_text::~pro_text() {
	SAFE_DELETE(le_text);
	SAFE_DELETE(le_colorR);
	SAFE_DELETE(le_colorG);
	SAFE_DELETE(le_colorB);
	SAFE_DELETE(le_posY);
	SAFE_DELETE(le_posX);
	SAFE_DELETE(lb_text);
	SAFE_DELETE(lb_colorR);
	SAFE_DELETE(lb_colorG);
	SAFE_DELETE(lb_colorB);
	SAFE_DELETE(lb_posX);
	SAFE_DELETE(lb_posY);
	SAFE_DELETE(btn_Ok);
	SAFE_DELETE(textGrid);
	SAFE_DELETE(textGroupBox);
}

QGroupBox* pro_text::getGroupBox() {
	return textGroupBox;
}

QString pro_text::getName() {
	if (le_name)
		return le_name->text();
	else return "";
}

void pro_text::setName(QString name) {
	le_name->setText(name);
}

void pro_text::do_btn_click() {
	emit(btn_click());
}


void pro_text::setPosX(int x) {
	le_posX->setText(QString::number(x));
}

void pro_text::setPosY(int y) {
	le_posY->setText(QString::number(y));

}

int pro_text::getPosX() {
	return le_posX->text().toInt();
}

int pro_text::getPosY() {
	return le_posY->text().toInt();

}

void pro_text::setText(QString text) {
	le_text->setText(text);
}

QString pro_text::getText() {
	return le_text->text();
}

void pro_text::setColorR(int r) {
	le_colorR->setText(QString::number(r));
}

int pro_text::getColorR() {
	return le_colorR->text().toInt();
}

void pro_text::setColorG(int g) {
	le_colorG->setText(QString::number(g));
}

int pro_text::getColorG() {
	return le_colorG->text().toInt();
}

void pro_text::setColorB(int b) {
	le_colorB->setText(QString::number(b));
}

int pro_text::getColorB() {
	return le_colorB->text().toInt();
}