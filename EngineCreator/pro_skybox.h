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
//天空盒属性
class pro_skyBox : public QWidget {
	Q_OBJECT

public:
	pro_skyBox(QWidget * parent = Q_NULLPTR);
	~pro_skyBox();

	int getSkyBoxLength();
	QString getSkyBoxFront();
	QString getSkyBoxBack();
	QString getSkyBoxLeft();
	QString getSkyBoxRight();
	QString getSkyBoxTop();

	void setSkyBoxLength(int length);
	void setSkyBoxFront(QString front);
	void setSkyBoxBack(QString back);
	void setSkyBoxLeft(QString left);
	void setSkyBoxRight(QString right);
	void setSkyBoxTop(QString top);

	QGroupBox *getGroupBox();
	
private:
	QGridLayout *skyBoxGrid;	//天空盒布局
	QGroupBox *skyBoxGroupBox;	//天空盒组

	QLineEdit *le_skyLen;
	QLineEdit *le_skyFront;
	QLineEdit *le_skyBack;
	QLineEdit *le_skyLeft;
	QLineEdit *le_skyRight;
	QLineEdit *le_skyTop;

	QLabel *lb_skyLen;	
	QPushButton *btn_Ok;

	QLabel *lb_skyFront;
	QPushButton *btn_skyFront;

	QLabel *lb_skyBack;
	QPushButton *btn_skyBack;

	QLabel *lb_skyLeft;
	QPushButton *btn_skyLeft;

	QLabel *lb_skyRight;	
	QPushButton *btn_skyRight;

	QLabel *lb_skyTop;	
	QPushButton *btn_skyTop;
private slots:
	void do_btn_click();
	void do_btn_front_click();
	void do_btn_back_click();
	void do_btn_left_click();
	void do_btn_right_click();
	void do_btn_top_click();
signals:
	void btn_click();

};
