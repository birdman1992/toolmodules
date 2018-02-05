#include "paintlab.h"
#include "ui_paintlab.h"
#include <QDebug>

PaintLab::PaintLab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaintLab)
{
    ui->setupUi(this);

}

PaintLab::~PaintLab()
{
    delete ui;
}

void PaintLab::addPoint(QPoint p)
{
    list_point<<p;
    update();
}

void PaintLab::paintCoorAxis(QPainter &painter)
{
    ptOrigin = this->geometry().center();
    painter.drawLine(QPoint(0,ptOrigin.y()), QPoint(this->geometry().width()-1, ptOrigin.y()));
    painter.drawLine(QPoint(ptOrigin.x(),0), QPoint(ptOrigin.x(), this->geometry().height()-1));
}

void PaintLab::paintPoint(QPainter &painter)
{
    if(list_point.isEmpty())
        return;

    painter.setBrush(QColor(255, 0, 0));
    QPoint p;
    foreach(p, list_point)
    {
        painter.drawEllipse(realPoint(p), 4, 4);
    }
}

QPoint PaintLab::realPoint(QPoint p)
{
    QPoint ret = ptOrigin;
    ret.setX(ret.x()+p.x());
    ret.setY(ret.y()-p.y());
    return ret;
}

void PaintLab::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    paintCoorAxis(painter);
    paintPoint(painter);
}

void PaintLab::resizeEvent(QResizeEvent *)
{
    this->update();
}
