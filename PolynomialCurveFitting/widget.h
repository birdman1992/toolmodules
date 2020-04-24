#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "paintlab.h"
#include "polcurvefit.h"

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
    void on_export_2_clicked();
    void on_import_2_clicked();
    void on_start_clicked(bool checked);

private:
    Ui::Widget *ui;
    PaintLab* paintLab;
    PolCurveFit fit;
};

#endif // WIDGET_H
