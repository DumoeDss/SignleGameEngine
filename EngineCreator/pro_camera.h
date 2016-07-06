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
class QComboBox;
class pro_camera : public QWidget {
	Q_OBJECT

public:
	pro_camera(QWidget * parent = Q_NULLPTR);
	~pro_camera();
	QGroupBox *getGroupBox();

	int getCameraType();
	void setCameraType(int type);

	int getPosX();
	int getPosY();
	int getPosZ();
	int getSpeed();

	void setPosX(int x);
	void setPosY(int y);
	void setPosZ(int z);
	void setSpeed(int speed);

	QPushButton *btn_Ok;
private:
	QGridLayout *cameraGrid;
	QGroupBox *cameraGroupBox;
	QLabel *lb_cameraType;
	QComboBox *cb_cameraType;	

	QLabel *lb_position;
	QLabel *lb_posX;
	QLabel *lb_posY;
	QLabel *lb_posZ;
	QLineEdit *le_posX;
	QLineEdit *le_posY;
	QLineEdit *le_posZ;
	QLabel *lb_speed;
	QLineEdit *le_speed;

private slots:
	void do_btn_click();
signals:
	void btn_click();
};
