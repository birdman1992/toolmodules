#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include "QTextScroll/qtextscroll.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
    void paintEvent(QPaintEvent *);
private slots:
    void on_text_returnPressed();

    void on_foround_returnPressed();

    void on_background_returnPressed();

private:
    Ui::MainWidget *ui;
    QTextScroll* textscrol;
};

#endif // MAINWIDGET_H
