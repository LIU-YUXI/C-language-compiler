#ifndef SYNTAX_H
#define SYNTAX_H

#include <QMainWindow>
#include <childwindow.h>
#include <QStandardItemModel>
QT_BEGIN_NAMESPACE
namespace Ui { class Syntax; }
QT_END_NAMESPACE

class Syntax : public QMainWindow
{
    Q_OBJECT

public:
    Syntax(QWidget *parent = nullptr);
    ~Syntax();
public slots:
    void start();
    void reset();
    void showpic();
private:
    Ui::Syntax *ui;
    ChildWindow *cw;
    QStandardItemModel* t1;
    QStandardItemModel* t2;
};
#endif // SYNTAX_H
