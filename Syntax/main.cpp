#include "syntax.h"

#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Syntax w;
    w.show();
    return a.exec();
}
