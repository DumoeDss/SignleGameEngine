#pragma once
#include <QWidget>
class QGroupBox;
class QLabel;
class QLineEdit;
class QListWidget;
class QStackedLayout;
class QGridLayout;
class QVBoxLayout;
class QPushButton;
class pro_terrain : public QWidget {
	Q_OBJECT

public:
	pro_terrain(QWidget * parent = Q_NULLPTR);
	~pro_terrain();
	QGroupBox *getGroupBox();

	QString getRawFileName();
	void setRawFileName(QString name);

	QString getFileName();
	void setFileName(QString name);

	void setNumVertsPerRow(int numVertsPerRow);
	int getNumVertsPerRow();
	void setNumVertsPerCol(int numVertsPerCol);
	int getNumVertsPerCol();
	void setCellSpacing(int cellSpacing);
	int getCellSpacing();
	void setHeightScale(float heightScale);
	float getHeightScale();

private:
	QGridLayout *terrainGrid;
	QGroupBox *terrainGroupBox;
	QPushButton *btn_Ok;

	//高度图
	QLabel *lb_rawFileName;
	QPushButton *btn_rawFileName;
	QLineEdit *le_rawFileName;
	//纹理贴图
	QLabel *lb_fileName;
	QPushButton *btn_fileName;
	QLineEdit *le_fileName;
	//每列顶点数
	QLabel *lb_numVertsPerRow;
	QLineEdit *le_numVertsPerRow;
	//每行顶点数
	QLabel *lb_numVertsPerCol;
	QLineEdit *le_numVertsPerCol;
	//顶点间间隔
	QLabel *lb_cellSpacing;
	QLineEdit *le_cellSpacing;
	//高度缩放系数
	QLabel *lb_heightScale;
	QLineEdit *le_heightScale;
private slots:
	void do_btn_click();
	void do_btn_fileName_click();
	void do_btn_rawFileName_click();
signals:
	void btn_click();

};
