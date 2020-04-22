#ifndef SINGLETEST_H
#define SINGLETEST_H

#include <QWidget>
#include "singleton.h"

class SingleTest : public QWidget,public Singleton<SingleTest>
{
    Q_OBJECT
    friend class Singleton<SingleTest>;
public:

private:
    explicit SingleTest(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // SINGLETEST_H
