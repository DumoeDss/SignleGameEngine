/********************************************************************************
** Form generated from reading UI file 'propertywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYWIDGET_H
#define UI_PROPERTYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PropertyWidget
{
public:

    void setupUi(QWidget *PropertyWidget)
    {
        if (PropertyWidget->objectName().isEmpty())
            PropertyWidget->setObjectName(QStringLiteral("PropertyWidget"));
        PropertyWidget->resize(400, 300);

        retranslateUi(PropertyWidget);

        QMetaObject::connectSlotsByName(PropertyWidget);
    } // setupUi

    void retranslateUi(QWidget *PropertyWidget)
    {
        PropertyWidget->setWindowTitle(QApplication::translate("PropertyWidget", "PropertyWidget", 0));
    } // retranslateUi

};

namespace Ui {
    class PropertyWidget: public Ui_PropertyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYWIDGET_H
