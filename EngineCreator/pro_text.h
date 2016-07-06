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
class pro_text : public QWidget {
	Q_OBJECT

public:
	pro_text(QWidget * parent = Q_NULLPTR);
	~pro_text();
	QGroupBox *getGroupBox();
	

	QString getName();
	void setName(QString name);

	void setPosX(int x);
	void setPosY(int y);
	void setText(QString text);
	void setColorR(int r);
	void setColorG(int g);
	void setColorB(int b);

	int getPosX();
	int getPosY();
	int getColorR();
	int getColorG();
	int getColorB();
	QString getText();
private:
	QGridLayout *textGrid;
	QGroupBox *textGroupBox;

	QLineEdit *le_text;
	QLineEdit *le_colorR;
	QLineEdit *le_colorG;
	QLineEdit *le_colorB;
	QLineEdit *le_posX;
	QLineEdit *le_posY;
	QLabel *lb_text;	
	QLabel *lb_colorR;	
	QLabel *lb_colorG;
	QLabel *lb_colorB;	
	QLabel *lb_posX;
	QLabel *lb_posY;
	QPushButton *btn_Ok;

	QLabel *lb_name;
	QLineEdit *le_name;
private slots:
	void do_btn_click();
signals:
	void btn_click();
};
