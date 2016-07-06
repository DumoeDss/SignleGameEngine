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
class pro_xModel : public QWidget {
	Q_OBJECT

public:
	pro_xModel(QWidget * parent = Q_NULLPTR);
	~pro_xModel();
	QGroupBox *getGroupBox();

	QString getName();
	void setName(QString name);

	QString getFileName();
	void setFileName(QString name);

	int getPosX();
	int getPosY();
	int getPosZ();
	int getRotX();
	int getRotY();
	int getRotZ();
	float getScaleX();
	float getScaleY();
	float getScaleZ();

	void setPosX(int x);
	void setPosY(int y);
	void setPosZ(int z);
	void setRotX(int x);
	void setRotY(int y);
	void setRotZ(int z);
	void setScaleX(float x);
	void setScaleY(float y);
	void setScaleZ(float z);
private:
	QGridLayout *xModelGrid;
	QGroupBox *xModelGroupBox;

	QPushButton *btn_Ok;
	QLabel *lb_fileName;
	QPushButton *btn_fileName;
	QLineEdit *le_fileName;

	QLabel *lb_position;
	QLabel *lb_posX;
	QLabel *lb_posY;
	QLabel *lb_posZ;
	QLabel *lb_rotation;
	QLabel *lb_rotX;
	QLabel *lb_rotY;
	QLabel *lb_rotZ;
	QLabel *lb_scale;
	QLabel *lb_scaleX;
	QLabel *lb_scaleY;
	QLabel *lb_scaleZ;
	QLineEdit *le_posX;
	QLineEdit *le_posY;
	QLineEdit *le_posZ;
	QLineEdit *le_rotX;
	QLineEdit *le_rotY;
	QLineEdit *le_rotZ;
	QLineEdit *le_scaleX;
	QLineEdit *le_scaleY;
	QLineEdit *le_scaleZ;

	QLabel *lb_name;
	QLineEdit *le_name;
private slots:
	void do_btn_click();
	void do_btn_fileName_click();
signals:
	void btn_click();
};
