#include "iconwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IconWidget w;
    w.show();
    return a.exec();
}
