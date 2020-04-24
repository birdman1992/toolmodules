#include "paintlab.h"
#include "ui_paintlab.h"
#include <QDebug>
#include <QFile>

PaintLab::PaintLab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaintLab)
{
    ui->setupUi(this);
    x_min = 0;
    y_min = 0;
    x_max = 0;
    y_max = 0;
    needPaintFx = false;
    ptOrigin = this->geometry().center();
//    doubleVector(fitCoe).swap(fitCoe);
    x_scale = 1;
    y_scale = 1;
}

PaintLab::~PaintLab()
{
    delete ui;
}

void PaintLab::addPoint(point pt)
{
//    if(list_point.isEmpty())
//    {
        db_point.push_back(pt);
        QPoint p((int)pt.x,(int)pt.y);
        x_max = (p.x()>x_max)?p.x():x_max;
        y_max = (p.y()>y_max)?p.y():y_max;
        x_min = (p.x()<x_min)?p.x():x_min;
        y_min = (p.y()<y_min)?p.y():y_min;
        qDebug()<<x_max<<y_max;
        qDebug()<<x_min<<y_min;
//    }
//    else
//    {
//        x_max = abs(p.x());
//        y_max = abs(p.y());
//    }
    list_point<<p;
    autoResize();
    update();
}

void PaintLab::setFitCoe(doubleVector coe)
{
    fitCoe = coe;
}

void PaintLab::savePoint(QString fileName)
{
    QFile f(fileName);
    f.open(QFile::WriteOnly);

    for(vector<point>::iterator it=db_point.begin(); it!=db_point.end(); it++)
    {
        QString strPos = QString("%1 %2\n").arg((*it).x).arg((*it).y);
        f.write(strPos.toLocal8Bit());
    }

    f.close();
}

void PaintLab::readPoint(QString fileName)
{
    QFile f(fileName);
    f.open(QFile::ReadOnly);
    QPoint p;
    QByteArray qba;

    while(!(qba = f.readLine()).isEmpty())
    {
        QString str = QString(qba);
        qDebug()<<"[readPoint]"<<str;
        QStringList l = str.split(" ", QString::SkipEmptyParts);
        if(l.count() != 2)
        {
            qDebug()<<"[readPoint]:File fomat error.";
            return;
        }
        bool ok;
        point p;
        p.x = (l.at(0).toDouble(&ok));
        if(!ok)
        {
            qDebug()<<"[readPoint]:File fomat error.";
            return;
        }
        p.y = (l.at(1).toDouble(&ok));
        if(!ok)
        {
            qDebug()<<"[readPoint]:File fomat error.";
            return;
        }

//        qDebug()<<"addpoint"<<p;
        addPoint(p);
    }
    f.close();
}

void PaintLab::setPaintFx(bool p)
{
    needPaintFx = p;
    this->update();
}

vector<point> PaintLab::getPoints()
{
    return db_point;
}

void PaintLab::paintCoorAxis(QPainter &painter)
{
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

void PaintLab::paintFx(QPainter &painter)
{
    int i=0;
    painter.setPen(QColor(0,0,255));
    for(i=0; i<this->geometry().width(); i++)
    {
        int y = r2sY( value(s2rX(i)));
        qDebug()<<"paintFx"<<i<<y;
        painter.drawPoint(i, y);
    }
}

QPoint PaintLab::realPoint(QPoint p)
{
    QPoint ret = ptOrigin;
    ret.setX((ret.x()+p.x()/x_scale));
    ret.setY((ret.y()-p.y()/y_scale));
//    qDebug()<<ptOrigin;
//    qDebug()<<p<<ret;
    return ret;
}

double PaintLab::s2rX(int x)
{
    return (double)(x-ptOrigin.x())*x_scale;
}

double PaintLab::r2sY(int y)
{
    return ptOrigin.y()-y/y_scale;
}

void PaintLab::autoResize()
{
    int x_range = x_max-x_min;
    int y_range = y_max-y_min;
    x_scale = (float)x_range/this->geometry().width()*2;
    y_scale = (float)y_range/this->geometry().height()*2;
    if(x_scale == 0)
        x_scale = 1;
    if(y_scale == 0)
        y_scale = 1;

    ptOrigin.setX(this->geometry().center().x() - (x_max+x_min)/2/x_scale);
    ptOrigin.setY(this->geometry().center().y() +(y_max+y_min)/2/y_scale);

    qDebug()<<ptOrigin;
    qDebug()<<"scale"<<x_scale<<y_scale;
}

double PaintLab::value(double x)
{
    double ret = 0;
    int i=0;
    for(i=0; i<fitCoe.size(); i++)
    {
        ret += pow(x,i)*fitCoe[i];
    }
    return ret;
}

void PaintLab::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    paintCoorAxis(painter);
    paintPoint(painter);
    if(needPaintFx)
        paintFx(painter);
}

void PaintLab::resizeEvent(QResizeEvent *)
{
    qDebug()<<"resize";
    qDebug()<<ptOrigin;
    ptOrigin = this->geometry().center();
    if(list_point.isEmpty())
    {
        x_max = 0;
        y_max = 0;
    }
    else
    {
        autoResize();
    }
    this->update();
}
