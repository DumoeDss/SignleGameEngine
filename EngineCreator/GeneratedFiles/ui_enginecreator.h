/********************************************************************************
** Form generated from reading UI file 'enginecreator.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENGINECREATOR_H
#define UI_ENGINECREATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EngineCreatorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EngineCreatorClass)
    {
        if (EngineCreatorClass->objectName().isEmpty())
            EngineCreatorClass->setObjectName(QStringLiteral("EngineCreatorClass"));
        EngineCreatorClass->resize(600, 400);
        menuBar = new QMenuBar(EngineCreatorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        EngineCreatorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EngineCreatorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        EngineCreatorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(EngineCreatorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        EngineCreatorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(EngineCreatorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EngineCreatorClass->setStatusBar(statusBar);

        retranslateUi(EngineCreatorClass);

        QMetaObject::connectSlotsByName(EngineCreatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *EngineCreatorClass)
    {
        EngineCreatorClass->setWindowTitle(QApplication::translate("EngineCreatorClass", "EngineCreator", 0));
    } // retranslateUi

};

namespace Ui {
    class EngineCreatorClass: public Ui_EngineCreatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENGINECREATOR_H
