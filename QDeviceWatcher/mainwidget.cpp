#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    devWatcher = new QDeviceWatcher(this);
    devWatcher->addDevice("hidraw0");
    connect(devWatcher, SIGNAL(deviceAdded(QString)), this, SLOT(devAdd(QString)));
    connect(devWatcher, SIGNAL(deviceRemoved(QString)), this, SLOT(devRemove(QString)));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::devAdd(QString devName)
{
    qDebug()<<devName<<"is added";
}

void MainWidget::devRemove(QString devName)
{
    qDebug()<<devName<<"is removed";
}
