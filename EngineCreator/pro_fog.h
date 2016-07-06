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
class pro_fog : public QWidget {
	Q_OBJECT

public:
	pro_fog(QWidget * parent = Q_NULLPTR);
	~pro_fog();
	QGroupBox *getGroupBox();

	int getFogType();
	int getFogStart();
	int getFogEnd();
	int getFogColorR();
	int getFogColorG();
	int getFogColorB();

	void setFogType(int type);
	void setFogStart(int start);
	void setFogEnd(int end);
	void setFogColorR(int r);
	void setFogColorG(int g);
	void setFogColorB(int b);

private:
	QGridLayout *fogGrid;	//雾效布局
	QGroupBox *fogGroupBox;	//雾效组

	QLineEdit *le_fogStart;
	QLineEdit *le_fogEnd;
	QLineEdit *le_fogColorR;
	QLineEdit *le_fogColorG;
	QLineEdit *le_fogColorB;
	QComboBox *cb_fogType;
	//开始
	QLabel *lb_fogStart;	
	//结束
	QLabel *lb_fogEnd;
	//颜色
	QLabel *lb_fogColor;
	QLabel *lb_fogColorR;
	QLabel *lb_fogColorG;	
	QLabel *lb_fogColorB;	
	//类型
	QLabel *lb_fogType;	
	//确定
	QPushButton *btn_Ok;
private slots:
	void do_btn_click();
signals:
	void btn_click();
};
