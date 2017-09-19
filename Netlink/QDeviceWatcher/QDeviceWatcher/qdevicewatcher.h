#ifndef QDEVICEWATCHER_H
#define QDEVICEWATCHER_H

#include <QObject>

class QDeviceWatcher : public QObject
{
    Q_OBJECT
public:
    explicit QDeviceWatcher(QObject *parent = 0);

signals:

public slots:
};

#endif // QDEVICEWATCHER_H