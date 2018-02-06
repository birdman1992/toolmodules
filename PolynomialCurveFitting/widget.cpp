#include "widget.h"
#include "ui_widget.h"
#include <QPoint>
#include <QDebug>
#include <qstringlist.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    paintLab = new PaintLab();
    ui->paintFrame->layout()->addWidget(paintLab);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_addPoint_clicked()
{
    QString str = ui->input->text();
    QStringList l = str.split(" ", QString::SkipEmptyParts);
    if(l.count() != 2)
        return;
    bool ok;
    point p;
    p.x = (l.at(0).toDouble(&ok));
    if(!ok)
        return;
    p.y = (l.at(1).toDouble(&ok));
    if(!ok)
        return;

    qDebug()<<"addpoint"<<p.x<<p.y;
    paintLab->addPoint(p);
}

void Widget::on_export_2_clicked()
{
    paintLab->savePoint("ptList");
}

void Widget::on_import_2_clicked()
{
    paintLab->readPoint("ptList");
}

void Widget::on_start_clicked(bool checked)
{
    doubleVector v = fit.fitStart(paintLab->getPoints());
    QString str("f(x)=");

    for(unsigned int i=0; i<v.size(); i++)
    {
        str.append(QString("%1x^%2+").arg(v[i]).arg(i));
    }
    str.chop(1);
    ui->label->setText(str);
    paintLab->setFitCoe(v);
    paintLab->setPaintFx(checked);
}
