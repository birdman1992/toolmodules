#ifndef PAINTLAB_H
#define PAINTLAB_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QList>
#include <QPoint>

namespace Ui {
class PaintLab;
}

class PaintLab : public QWidget
{
    Q_OBJECT

public:
    explicit PaintLab(QWidget *parent = 0);
    ~PaintLab();
    void addPoint(QPoint p);
    void savePoint();

private:
    Ui::PaintLab *ui;
    QPoint ptOrigin;//原点
    QList<QPoint> list_point;
    void paintCoorAxis(QPainter& painter);
    void paintPoint(QPainter& painter);
    QPoint realPoint(QPoint p);

protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);
};

#endif // PAINTLAB_H
