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
//坐标变换属性
class pro_transform : public QWidget {
	Q_OBJECT

public:
	pro_transform(QWidget * parent = Q_NULLPTR);
	~pro_transform();
	QGroupBox *getGroupBox();

	int getPosX();
	int getPosY();
	int getPosZ();
	int getRotX();
	int getRotY();
	int getRotZ();

	void setPosX(int x);
	void setPosY(int y);
	void setPosZ(int z);
	void setRotX(int x);
	void setRotY(int y);
	void setRotZ(int z);

	QPushButton *btn_Ok;
private:
	QGridLayout *transGrid;	//变换布局
	QGroupBox *transGroupBox;	//变换组	

	QLabel *lb_position;
	QLabel *lb_posX;
	QLabel *lb_posY;
	QLabel *lb_posZ;
	QLabel *lb_rotation;
	QLabel *lb_rotX;
	QLabel *lb_rotY;
	QLabel *lb_rotZ;
	QLineEdit *le_posX;
	QLineEdit *le_posY;
	QLineEdit *le_posZ;
	QLineEdit *le_rotX;
	QLineEdit *le_rotY;
	QLineEdit *le_rotZ;
private slots:
	void changeBtnState();
	void btnClicked();
};
