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
class pro_sprite : public QWidget {
	Q_OBJECT

public:
	pro_sprite(QWidget * parent = Q_NULLPTR);
	~pro_sprite();
	QGroupBox *getGroupBox();
	
	QString getName();
	void setName(QString name);

	QString getFileName();
	void setFileName(QString name);

	void setPosX(int x);
	void setPosY(int y);

	int getPosX();
	int getPosY();

private:
	QGridLayout *spriteGrid;
	QGroupBox *spriteGroupBox;
	QLabel *lb_background;
	QPushButton *btn_background;
	QLabel *lb_posX;	
	QLabel *lb_posY;	
	QPushButton *btn_Ok;
	QLineEdit *le_background;
	QLineEdit *le_posX;
	QLineEdit *le_posY;

	QLabel *lb_name;
	QLineEdit *le_name;
private slots:
	void do_btn_click();
	void do_btn_fileName_click();
signals:
	void btn_click();
};
