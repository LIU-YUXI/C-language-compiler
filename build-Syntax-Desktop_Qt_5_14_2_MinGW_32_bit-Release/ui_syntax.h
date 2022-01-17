/********************************************************************************
** Form generated from reading UI file 'syntax.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNTAX_H
#define UI_SYNTAX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Syntax
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QTextBrowser *outputBox1;
    QTextBrowser *outputBox3;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *startBtn;
    QTextEdit *fileBox1;
    QTextEdit *fileBox2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QTextBrowser *outputBox2;
    QLabel *label_7;
    QTextBrowser *outputBox4;
    QLabel *label_8;
    QPushButton *rstBtn;
    QPushButton *picBtn;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QTableView *table;
    QTextBrowser *outputBox5;
    QTableView *table2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Syntax)
    {
        if (Syntax->objectName().isEmpty())
            Syntax->setObjectName(QString::fromUtf8("Syntax"));
        Syntax->resize(1621, 870);
        centralwidget = new QWidget(Syntax);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(630, 20, 231, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(14);
        label->setFont(font);
        outputBox1 = new QTextBrowser(centralwidget);
        outputBox1->setObjectName(QString::fromUtf8("outputBox1"));
        outputBox1->setGeometry(QRect(30, 120, 361, 321));
        outputBox3 = new QTextBrowser(centralwidget);
        outputBox3->setObjectName(QString::fromUtf8("outputBox3"));
        outputBox3->setGeometry(QRect(410, 470, 371, 341));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(410, 450, 68, 20));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 450, 91, 16));
        startBtn = new QPushButton(centralwidget);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));
        startBtn->setGeometry(QRect(580, 50, 93, 28));
        fileBox1 = new QTextEdit(centralwidget);
        fileBox1->setObjectName(QString::fromUtf8("fileBox1"));
        fileBox1->setGeometry(QRect(110, 50, 191, 31));
        fileBox2 = new QTextEdit(centralwidget);
        fileBox2->setObjectName(QString::fromUtf8("fileBox2"));
        fileBox2->setGeometry(QRect(370, 50, 201, 31));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 60, 72, 15));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(320, 60, 72, 15));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(950, 50, 141, 16));
        outputBox2 = new QTextBrowser(centralwidget);
        outputBox2->setObjectName(QString::fromUtf8("outputBox2"));
        outputBox2->setGeometry(QRect(30, 470, 361, 341));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 100, 72, 15));
        outputBox4 = new QTextBrowser(centralwidget);
        outputBox4->setObjectName(QString::fromUtf8("outputBox4"));
        outputBox4->setGeometry(QRect(410, 120, 371, 321));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(410, 100, 72, 15));
        rstBtn = new QPushButton(centralwidget);
        rstBtn->setObjectName(QString::fromUtf8("rstBtn"));
        rstBtn->setGeometry(QRect(690, 50, 93, 28));
        picBtn = new QPushButton(centralwidget);
        picBtn->setObjectName(QString::fromUtf8("picBtn"));
        picBtn->setGeometry(QRect(800, 50, 93, 28));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(800, 450, 72, 15));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(800, 100, 72, 15));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(1200, 30, 151, 20));
        table = new QTableView(centralwidget);
        table->setObjectName(QString::fromUtf8("table"));
        table->setGeometry(QRect(800, 470, 801, 341));
        outputBox5 = new QTextBrowser(centralwidget);
        outputBox5->setObjectName(QString::fromUtf8("outputBox5"));
        outputBox5->setGeometry(QRect(1200, 50, 401, 391));
        table2 = new QTableView(centralwidget);
        table2->setObjectName(QString::fromUtf8("table2"));
        table2->setGeometry(QRect(800, 120, 381, 321));
        Syntax->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Syntax);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1621, 26));
        Syntax->setMenuBar(menubar);
        statusbar = new QStatusBar(Syntax);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Syntax->setStatusBar(statusbar);

        retranslateUi(Syntax);

        QMetaObject::connectSlotsByName(Syntax);
    } // setupUi

    void retranslateUi(QMainWindow *Syntax)
    {
        Syntax->setWindowTitle(QCoreApplication::translate("Syntax", "Syntax", nullptr));
        label->setText(QCoreApplication::translate("Syntax", "LR(1)\350\257\255\346\263\225\350\257\255\344\271\211\345\210\206\346\236\220\345\231\250", nullptr));
        label_2->setText(QCoreApplication::translate("Syntax", "\350\257\255\346\263\225\345\210\206\346\236\220", nullptr));
        label_3->setText(QCoreApplication::translate("Syntax", "\350\257\255\346\263\225\344\272\247\347\224\237\345\274\217", nullptr));
        startBtn->setText(QCoreApplication::translate("Syntax", "\345\274\200\345\247\213\345\210\206\346\236\220", nullptr));
        label_4->setText(QCoreApplication::translate("Syntax", "\350\257\255\346\263\225\346\226\207\344\273\266", nullptr));
        label_5->setText(QCoreApplication::translate("Syntax", "\346\272\220\344\273\243\347\240\201", nullptr));
        label_6->setText(QCoreApplication::translate("Syntax", "\345\221\250\345\251\211\350\216\271&\345\210\230\347\276\275\350\214\234", nullptr));
        label_7->setText(QCoreApplication::translate("Syntax", "\346\272\220\347\240\201", nullptr));
        label_8->setText(QCoreApplication::translate("Syntax", "\350\257\215\346\263\225\345\210\206\346\236\220", nullptr));
        rstBtn->setText(QCoreApplication::translate("Syntax", "\351\207\215\347\275\256", nullptr));
        picBtn->setText(QCoreApplication::translate("Syntax", "\346\237\245\347\234\213\350\257\255\346\263\225\346\240\221", nullptr));
        label_9->setText(QCoreApplication::translate("Syntax", "\347\254\246\345\217\267\350\241\250", nullptr));
        label_10->setText(QCoreApplication::translate("Syntax", "\350\277\220\350\241\214\346\240\210", nullptr));
        label_11->setText(QCoreApplication::translate("Syntax", "\350\257\255\344\271\211\345\210\206\346\236\220\347\273\223\346\236\234-\345\233\233\345\205\203\345\274\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Syntax: public Ui_Syntax {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNTAX_H
