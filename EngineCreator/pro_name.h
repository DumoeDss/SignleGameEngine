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
class pro_name : public QWidget {
	Q_OBJECT

public:
	pro_name(QWidget * parent = Q_NULLPTR,QString name = "");
	~pro_name();
	QGroupBox *getGroupBox();
	
	QString getName();
	void setName(QString name);
private:
	QGridLayout *nameGrid;
	QGroupBox *nameGroupBox;
	QLabel *lb_name;	
	QPushButton *btn_Ok;
	QLineEdit *le_name;
private slots:
	void do_btn_click();
signals:
	void btn_click();

};
