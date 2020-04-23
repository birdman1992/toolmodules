#include "frmexample.h"

#include <QApplication>
#include "inputcontex/keyboard.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FrmExample w;
    w.show();
    KeyBoard::instance().hide();
    return a.exec();
}
