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
class pro_cube : public QWidget {
	Q_OBJECT

public:
	pro_cube(QWidget * parent = Q_NULLPTR);
	~pro_cube();
	QGroupBox *getGroupBox();

	QString getName();
	void setName(QString name);

	int getPosX();
	int getPosY();
	int getPosZ();
	int getRotX();
	int getRotY();
	int getRotZ();
	float getScaleX();
	float getScaleY();
	float getScaleZ();
	int getColorR();
	int getColorG();
	int getColorB();

	void setPosX(int x);
	void setPosY(int y);
	void setPosZ(int z);
	void setRotX(int x);
	void setRotY(int y);
	void setRotZ(int z);
	void setScaleX(float x);
	void setScaleY(float y);
	void setScaleZ(float z);
	void setColorR(int r);
	void setColorG(int g);
	void setColorB(int b);
private:
	QGridLayout *cubeGrid;
	QGroupBox *cubeGroupBox;

	QLabel *lb_position;
	QLabel *lb_posX;
	QLabel *lb_posY;
	QLabel *lb_posZ;
	QLabel *lb_rotation;
	QLabel *lb_rotX;
	QLabel *lb_rotY;
	QLabel *lb_rotZ;
	QLabel *lb_color;
	QLabel *lb_colorR;
	QLabel *lb_colorG;
	QLabel *lb_colorB;
	QLineEdit *le_posX;
	QLineEdit *le_posY;
	QLineEdit *le_posZ;
	QLineEdit *le_rotX;
	QLineEdit *le_rotY;
	QLineEdit *le_rotZ;
	QLabel *lb_scale;
	QLabel *lb_scaleX;
	QLabel *lb_scaleY;
	QLabel *lb_scaleZ;
	QLineEdit *le_scaleX;
	QLineEdit *le_scaleY;
	QLineEdit *le_scaleZ;
	QLineEdit *le_colorR;
	QLineEdit *le_colorG;
	QLineEdit *le_colorB;

	QLabel *lb_name;
	QLineEdit *le_name;
	QPushButton *btn_Ok;
private slots:
	void do_btn_click();
signals:
	void btn_click();
};
