#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "paintlab.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_addPoint_clicked();

private:
    Ui::Widget *ui;
    PaintLab* paintLab;
};

#endif // WIDGET_H
