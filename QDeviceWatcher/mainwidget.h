#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "QDeviceWatcher/qdevicewatcher.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    QDeviceWatcher* devWatcher;

private slots:
    void devAdd(QString devName);
    void devRemove(QString devName);
};

#endif // MAINWIDGET_H
