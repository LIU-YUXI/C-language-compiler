#include "childwindow.h"
#include "ui_childwindow.h"

ChildWindow::ChildWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChildWindow)
{
    ui->setupUi(this);
    QPixmap *pixmap = new QPixmap("tree.png");
    pixmap->scaled(ui->pic->size(), Qt::KeepAspectRatio);
    ui->pic->setScaledContents(true);
    ui->pic->clear();
    ui->pic->setPixmap(*pixmap);
    ui->pic->show();
}

ChildWindow::~ChildWindow()
{
    delete ui;
}
