/********************************************************************************
** Form generated from reading UI file 'testapp.ui'
**
** Created by: Qt User Interface Compiler version 5.15.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTAPP_H
#define UI_TESTAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestApp
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TestApp)
    {
        if (TestApp->objectName().isEmpty())
            TestApp->setObjectName(QString::fromUtf8("TestApp"));
        TestApp->resize(400, 300);
        centralWidget = new QWidget(TestApp);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        TestApp->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TestApp);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        TestApp->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TestApp);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TestApp->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TestApp);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TestApp->setStatusBar(statusBar);

        retranslateUi(TestApp);

        QMetaObject::connectSlotsByName(TestApp);
    } // setupUi

    void retranslateUi(QMainWindow *TestApp)
    {
        TestApp->setWindowTitle(QCoreApplication::translate("TestApp", "TestApp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestApp: public Ui_TestApp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTAPP_H
