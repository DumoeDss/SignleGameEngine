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
class pro_particle : public QWidget {
	Q_OBJECT

public:
	pro_particle(QWidget * parent = Q_NULLPTR);
	~pro_particle();
	QGroupBox *getGroupBox();

	QString getName();
	void setName(QString name);

	int getPosX();
	int getPosY();
	int getPosZ();
	int getLength();
	int getWidth();
	int getHeight();
	int getNum();
	int getType(); 
	QString getFileName();
	
	void setPosX(int x);
	void setPosY(int y);
	void setPosZ(int z);
	void setLength(int length);
	void setWidth(int width);
	void setHeight(int height);
	void setNum(int num);
	void setType(int type);	
	void setFileName(QString name);
private:
	QGridLayout *particleGrid;
	QGroupBox *particleGroupBox;
	//位置
	QLabel *lb_position;
	QLabel *lb_posX;
	QLabel *lb_posY;
	QLabel *lb_posZ;
	QLineEdit *le_posX;
	QLineEdit *le_posY;
	QLineEdit *le_posZ;
	//长宽高
	QLabel *lb_length;
	QLabel *lb_width;
	QLabel *lb_height;
	QLineEdit *le_length;
	QLineEdit *le_width;
	QLineEdit *le_height;
	//数量
	QLabel *lb_num;
	QLineEdit *le_num;
	//纹理贴图
	QLabel *lb_fileName;
	QPushButton *btn_fileName;
	QLineEdit *le_fileName;
	//名字
	QLabel *lb_name;
	QLineEdit *le_name;	
	//类型
	QLabel *lb_particleType;
	QComboBox *cb_particleType;

	QPushButton *btn_Ok;
private slots:
	void do_btn_click();
	void do_btn_fileName_click();
signals:
	void btn_click();
};
