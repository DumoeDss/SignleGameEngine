#include "pro_name.h"
#include "defines.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
pro_name::pro_name(QWidget * parent, QString name) : QWidget(parent) {
	nameGrid = new QGridLayout;
	nameGroupBox = new QGroupBox(u8"属性");

	lb_name = new QLabel(u8"名字");
	le_name = new QLineEdit();
	le_name->setText(name);
	btn_Ok = new QPushButton(u8"确定");
	btn_Ok->setFixedSize(50, 22);
	connect(btn_Ok, SIGNAL(clicked()), this, SLOT(do_btn_click()));
	nameGrid->addWidget(lb_name, 0, 0);
	nameGrid->addWidget(le_name, 0, 1);
	nameGrid->addWidget(btn_Ok, 1, 2);

	nameGroupBox->setLayout(nameGrid);
}

pro_name::~pro_name() {
	SAFE_DELETE(le_name);
	SAFE_DELETE(lb_name);
	SAFE_DELETE(btn_Ok);
	SAFE_DELETE(nameGrid);
	SAFE_DELETE(nameGroupBox);	
}


QGroupBox* pro_name::getGroupBox() {
	return nameGroupBox;
}

void pro_name::do_btn_click() {
	emit(btn_click());
}

QString pro_name::getName() {
	if(le_name)
		return le_name->text();
	else return "";
}

void pro_name::setName(QString name) {
	le_name->setText(name);
}