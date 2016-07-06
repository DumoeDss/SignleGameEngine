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
class pro_button : public QWidget {
	Q_OBJECT

public:
	pro_button(QWidget * parent = Q_NULLPTR);
	~pro_button();
	QGroupBox *getGroupBox();

	QString get_up_name();
	void set_up_name(QString name);
	QString get_down_name();
	void set_down_name(QString name);
	QString get_move_name();
	void set_move_name(QString name);

	QString getName();
	void setName(QString name);

	void setPosX(int x);
	void setPosY(int y);

	int getPosX();
	int getPosY();
private:
	QGridLayout *buttonGrid;
	QGroupBox *buttonGroupBox;

	QLineEdit *le_bgUp;
	QLineEdit *le_bgDown;
	QLineEdit *le_bgMove;
	QLineEdit *le_posX;
	QLineEdit *le_posY;
	QLabel *lb_bgUp;
	QPushButton *btn_bgUp;
	QLabel *lb_bgDown;	
	QPushButton *btn_bgDown;
	QLabel *lb_bgMove;	
	QPushButton *btn_bgMove;
	QLabel *lb_posX;
	QLabel *lb_posY;
	QPushButton *btn_Ok;

	QLabel *lb_name;
	QLineEdit *le_name;

private slots:
	void do_btn_click();
	void do_btn_up_click();
	void do_btn_down_click();
	void do_btn_move_click();
signals:
	void btn_click();
};
