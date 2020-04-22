#include "frmexample.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FrmExample w;
    w.show();
    return a.exec();
}
