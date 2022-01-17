/********************************************************************************
** Form generated from reading UI file 'childwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHILDWINDOW_H
#define UI_CHILDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChildWindow
{
public:
    QWidget *centralwidget;
    QLabel *pic;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ChildWindow)
    {
        if (ChildWindow->objectName().isEmpty())
            ChildWindow->setObjectName(QString::fromUtf8("ChildWindow"));
        ChildWindow->resize(1216, 830);
        centralwidget = new QWidget(ChildWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pic = new QLabel(centralwidget);
        pic->setObjectName(QString::fromUtf8("pic"));
        pic->setGeometry(QRect(10, 0, 1191, 781));
        ChildWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ChildWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1216, 26));
        ChildWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ChildWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ChildWindow->setStatusBar(statusbar);

        retranslateUi(ChildWindow);

        QMetaObject::connectSlotsByName(ChildWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ChildWindow)
    {
        ChildWindow->setWindowTitle(QCoreApplication::translate("ChildWindow", "MainWindow", nullptr));
        pic->setText(QCoreApplication::translate("ChildWindow", "\350\257\255\346\263\225\345\210\206\346\236\220\346\240\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChildWindow: public Ui_ChildWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHILDWINDOW_H
