#include "pro_fog.h"
#include "defines.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIntValidator>
#include <QComboBox>
pro_fog::pro_fog(QWidget * parent) : QWidget(parent) {
	QIntValidator *fogVal = new QIntValidator(0, 1000, this);
	QIntValidator *colorVal = new QIntValidator(0, 255, this);
	fogGrid = new QGridLayout;
	fogGroupBox = new QGroupBox(u8"雾效");

	lb_fogStart = new QLabel(u8"开始");
	le_fogStart = new QLineEdit();
	le_fogStart->setValidator(fogVal);
	
	lb_fogEnd = new QLabel(u8"结束");
	le_fogEnd = new QLineEdit();
	le_fogEnd->setValidator(fogVal);

	lb_fogColor = new QLabel(u8"颜色");

	lb_fogColorR = new QLabel(u8"R");
	le_fogColorR = new QLineEdit();
	le_fogColorR->setValidator(colorVal);
	le_fogColorR->setFixedSize(50, 22);

	lb_fogColorG = new QLabel(u8"G");
	le_fogColorG = new QLineEdit();
	le_fogColorG->setValidator(colorVal);
	le_fogColorG->setFixedSize(50, 22);

	lb_fogColorB = new QLabel(u8"B");
	le_fogColorB = new QLineEdit();
	le_fogColorB->setValidator(colorVal);
	le_fogColorB->setFixedSize(50, 22);

	lb_fogType = new QLabel(u8"类型");
	cb_fogType = new QComboBox();
	cb_fogType->addItem(u8"顶点雾");
	cb_fogType->addItem(u8"像素雾");

	btn_Ok = new QPushButton(u8"确定");
	btn_Ok->setFixedSize(50, 22);
	connect(btn_Ok, SIGNAL(clicked()), this, SLOT(do_btn_click()));

	fogGrid->addWidget(lb_fogType, 0, 0);
	fogGrid->addWidget(cb_fogType, 0, 1);

	fogGrid->addWidget(lb_fogStart, 1, 0);
	fogGrid->addWidget(le_fogStart, 1, 1);

	fogGrid->addWidget(lb_fogEnd, 1, 2);
	fogGrid->addWidget(le_fogEnd, 1, 3);

	fogGrid->addWidget(lb_fogColor, 2, 0);

	fogGrid->addWidget(lb_fogColorR, 3, 0);
	fogGrid->addWidget(le_fogColorR, 3, 1);
	fogGrid->addWidget(lb_fogColorG, 3, 2);
	fogGrid->addWidget(le_fogColorG, 3, 3);
	fogGrid->addWidget(lb_fogColorB, 3, 4);
	fogGrid->addWidget(le_fogColorB, 3, 5);

	fogGrid->addWidget(btn_Ok, 4, 5);

	fogGroupBox->setLayout(fogGrid);
}

pro_fog::~pro_fog() {
	SAFE_DELETE(le_fogStart);
	SAFE_DELETE(le_fogEnd);
	SAFE_DELETE(le_fogColorR);
	SAFE_DELETE(le_fogColorG);
	SAFE_DELETE(le_fogColorB);
	SAFE_DELETE(cb_fogType);	
	SAFE_DELETE(lb_fogStart);
	SAFE_DELETE(lb_fogEnd);
	SAFE_DELETE(lb_fogColor);
	SAFE_DELETE(lb_fogColorR);
	SAFE_DELETE(lb_fogColorG);
	SAFE_DELETE(lb_fogColorB);
	SAFE_DELETE(lb_fogType);
	SAFE_DELETE(btn_Ok);
	SAFE_DELETE(fogGrid);
	SAFE_DELETE(fogGroupBox);
}

QGroupBox* pro_fog::getGroupBox() {
	return fogGroupBox;
}

void pro_fog::do_btn_click() {
	emit(btn_click());
}

int pro_fog::getFogType() {
	return cb_fogType->currentIndex();
}

int pro_fog::getFogStart() {
	return le_fogStart->text().toInt();
}

int pro_fog::getFogEnd() {
	return le_fogEnd->text().toInt();
}

int pro_fog::getFogColorR() {
	return le_fogColorR->text().toInt();
}

int pro_fog::getFogColorG() {
	return le_fogColorG->text().toInt();
}

int pro_fog::getFogColorB() {
	return le_fogColorB->text().toInt();
}


void pro_fog::setFogType(int type) {
	cb_fogType->setCurrentIndex(type);
}

void pro_fog::setFogStart(int start) {
	le_fogStart->setText(QString::number(start));
}

void pro_fog::setFogEnd(int end) {
	le_fogEnd->setText(QString::number(end));
}

void pro_fog::setFogColorR(int r) {
	le_fogColorR->setText(QString::number(r));
}

void pro_fog::setFogColorG(int g) {
	le_fogColorG->setText(QString::number(g));
}

void pro_fog::setFogColorB(int b) {
	le_fogColorB->setText(QString::number(b));
}
