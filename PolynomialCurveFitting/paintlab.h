#ifndef PAINTLAB_H
#define PAINTLAB_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QList>
#include <QPoint>
#include "polcurvefit.h"

namespace Ui {
class PaintLab;
}

class PaintLab : public QWidget
{
    Q_OBJECT

public:
    explicit PaintLab(QWidget *parent = 0);
    ~PaintLab();
    void addPoint(point pt);
    void setFitCoe(doubleVector coe);
    void savePoint(QString fileName);
    void readPoint(QString fileName);
    void setPaintFx(bool p);
    vector<point> getPoints();

private:
    Ui::PaintLab *ui;
    QPoint ptOrigin;//原点
    QList<QPoint> list_point;
    vector<point> db_point;
    doubleVector fitCoe;//拟合系数
    bool needPaintFx;
    int x_max;
    int x_min;
    int y_max;
    int y_min;
    float x_scale;
    float y_scale;
    void paintCoorAxis(QPainter& painter);
    void paintPoint(QPainter& painter);
    void paintFx(QPainter& painter);
    QPoint realPoint(QPoint p);//真实坐标转屏幕坐标
    double s2rX(int x);
    double r2sY(int y);
    void autoResize();
    double value(double x);

protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);
};

#endif // PAINTLAB_H
