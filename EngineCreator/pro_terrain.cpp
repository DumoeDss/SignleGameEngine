#include "pro_terrain.h"
#include "defines.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIntValidator>
#include <QFileDialog>
#include <QDoubleValidator>
pro_terrain::pro_terrain(QWidget * parent) : QWidget(parent) {
	terrainGrid = new QGridLayout;
	terrainGroupBox = new QGroupBox(u8"地形");
	QIntValidator *posVal = new QIntValidator(0, 10000, this);
	QDoubleValidator *scalVal = new QDoubleValidator(0.0f, 100.0f, 1);

	lb_numVertsPerRow = new QLabel(u8"每行顶点");
	lb_numVertsPerCol = new QLabel(u8"每列顶点");
	lb_cellSpacing = new QLabel(u8"每格间隔");
	lb_heightScale = new QLabel(u8"高度缩放");
	le_numVertsPerRow = new QLineEdit();
	le_numVertsPerRow->setValidator(posVal);
	le_numVertsPerRow->setText("0");
	le_numVertsPerCol = new QLineEdit();
	le_numVertsPerCol->setValidator(posVal);
	le_numVertsPerCol->setText("0");
	le_cellSpacing = new QLineEdit();
	le_cellSpacing->setValidator(posVal);
	le_cellSpacing->setText("0");
	le_heightScale = new QLineEdit();
	le_heightScale->setValidator(scalVal);
	le_heightScale->setText("0");

	lb_rawFileName = new QLabel(u8"高度图");
	le_rawFileName = new QLineEdit();
	le_rawFileName->setEnabled(false);
	btn_rawFileName = new QPushButton(u8"...");
	btn_rawFileName->setFixedSize(34, 22);

	lb_fileName = new QLabel(u8"贴图");
	le_fileName = new QLineEdit();
	le_fileName->setEnabled(false);
	btn_fileName = new QPushButton(u8"...");
	btn_fileName->setFixedSize(34, 22);

	btn_Ok = new QPushButton(u8"确定");
	btn_Ok->setFixedSize(50, 22);	
	connect(btn_Ok, SIGNAL(clicked()), this, SLOT(do_btn_click()));
	connect(btn_fileName, SIGNAL(clicked()), this, SLOT(do_btn_fileName_click()));
	connect(btn_rawFileName, SIGNAL(clicked()), this, SLOT(do_btn_rawFileName_click()));

	terrainGrid->addWidget(lb_numVertsPerRow, 0, 0);
	terrainGrid->addWidget(le_numVertsPerRow, 0, 1);
	terrainGrid->addWidget(lb_numVertsPerCol, 1, 0);
	terrainGrid->addWidget(le_numVertsPerCol, 1, 1);
	terrainGrid->addWidget(lb_cellSpacing, 2, 0);
	terrainGrid->addWidget(le_cellSpacing, 2, 1);
	terrainGrid->addWidget(lb_heightScale, 3, 0);
	terrainGrid->addWidget(le_heightScale, 3, 1);
	terrainGrid->addWidget(lb_rawFileName, 4, 0);
	terrainGrid->addWidget(le_rawFileName, 4, 1);
	terrainGrid->addWidget(btn_rawFileName, 4, 2);
	terrainGrid->addWidget(lb_fileName, 5, 0);
	terrainGrid->addWidget(le_fileName, 5, 1);
	terrainGrid->addWidget(btn_fileName, 5, 2);
	terrainGrid->addWidget(btn_Ok, 6, 3);
	terrainGroupBox->setLayout(terrainGrid);
}

pro_terrain::~pro_terrain() {
	SAFE_DELETE(lb_rawFileName);
	SAFE_DELETE(btn_rawFileName);
	SAFE_DELETE(le_rawFileName);
	SAFE_DELETE(lb_fileName);
	SAFE_DELETE(btn_fileName);
	SAFE_DELETE(le_fileName);
	SAFE_DELETE(lb_numVertsPerRow);
	SAFE_DELETE(le_numVertsPerRow);
	SAFE_DELETE(lb_numVertsPerCol);
	SAFE_DELETE(le_numVertsPerCol);
	SAFE_DELETE(lb_cellSpacing);
	SAFE_DELETE(le_cellSpacing);
	SAFE_DELETE(lb_heightScale);
	SAFE_DELETE(le_heightScale);
	SAFE_DELETE(btn_Ok);
	SAFE_DELETE(terrainGrid);
	SAFE_DELETE(terrainGroupBox);
}

QGroupBox* pro_terrain::getGroupBox() {
	return terrainGroupBox;
}

void pro_terrain::do_btn_click() {
	emit(btn_click());
}

void pro_terrain::do_btn_rawFileName_click() {
	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		u8"选择高度图",
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF *.raw)")); //选择路径  
	if (filename.isEmpty())
	{
		return;
	}
	else
	{
		setRawFileName(filename);
	}
}

void pro_terrain::do_btn_fileName_click() {
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

QString pro_terrain::getRawFileName() {
	return le_rawFileName->text();
}

void pro_terrain::setRawFileName(QString name) {
	le_rawFileName->setText(name);
}

QString pro_terrain::getFileName() {
	return le_fileName->text();
}

void pro_terrain::setFileName(QString name) {
	le_fileName->setText(name);
}

void pro_terrain::setNumVertsPerRow(int numVertsPerRow) {
	le_numVertsPerRow->setText(QString::number(numVertsPerRow));
}

int pro_terrain::getNumVertsPerRow() {
	return le_numVertsPerRow->text().toInt();
}

void pro_terrain::setNumVertsPerCol(int numVertsPerCol) {
	le_numVertsPerCol->setText(QString::number(numVertsPerCol));
}

int pro_terrain::getNumVertsPerCol() {
	return le_numVertsPerCol->text().toInt();
}

void pro_terrain::setCellSpacing(int cellSpacing) {
	le_cellSpacing->setText(QString::number(cellSpacing));
}

int pro_terrain::getCellSpacing() {
	return le_cellSpacing->text().toInt();
}

void pro_terrain::setHeightScale(float heightScale) {
	le_heightScale->setText(QString::number(heightScale));
}

float pro_terrain::getHeightScale() {
	float a = le_heightScale->text().toFloat();
	return le_heightScale->text().toFloat();
}
