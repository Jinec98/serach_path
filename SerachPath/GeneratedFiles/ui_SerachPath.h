/********************************************************************************
** Form generated from reading UI file 'SerachPath.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERACHPATH_H
#define UI_SERACHPATH_H

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

class Ui_SerachPathClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SerachPathClass)
    {
        if (SerachPathClass->objectName().isEmpty())
            SerachPathClass->setObjectName(QStringLiteral("SerachPathClass"));
        SerachPathClass->resize(600, 400);
        menuBar = new QMenuBar(SerachPathClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        SerachPathClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SerachPathClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SerachPathClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SerachPathClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SerachPathClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SerachPathClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SerachPathClass->setStatusBar(statusBar);

        retranslateUi(SerachPathClass);

        QMetaObject::connectSlotsByName(SerachPathClass);
    } // setupUi

    void retranslateUi(QMainWindow *SerachPathClass)
    {
        SerachPathClass->setWindowTitle(QApplication::translate("SerachPathClass", "SerachPath", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SerachPathClass: public Ui_SerachPathClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERACHPATH_H
