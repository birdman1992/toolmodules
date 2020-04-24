#include "qtextscroll.h"
#include <QPainter>
#include <QDebug>
#include <QFontMetrics>
#include <QString>
//#define Y_COR 0
#define W_COR 8    //字体宽度修正量

QTextScroll::QTextScroll(QWidget *parent):
    QLabel(parent)
{
    stepTime = 20;
    stepWidth = 1;
    curIndex = 0;
    _parent = parent;
    color_text = "ffffff";
    color_bak = "ffffff";

    font.setFamily("微软雅黑");
    font.setPixelSize(20);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 2);
//    font.setWordSpacing(30);
    this->setFont(font);

    this->setGeometry(0, 0, parent->geometry().width(),parent->geometry().height());

    scrollTimer = new QTimer();
    connect(scrollTimer, SIGNAL(timeout()), this, SLOT(updateIndex()));
}

void QTextScroll::showScrollText(QString text)//public接口，设置要滚动的文字，并开始滚动
{
    if(scrollTimer->isActive())
        scrollTimer->stop();

    QFontMetrics metrics(font);

    int resizeWidth = metrics.width(text)+text.length()*W_COR;
    int resizeHeight = metrics.height();
    textHeight = metrics.height();
//    qDebug()<<"[this wid]"<<resizeWidth<<_parent->geometry().width();

    resizeWidth = (resizeWidth>_parent->geometry().width())?resizeWidth:_parent->geometry().width();
    resizeHeight = (resizeHeight>_parent->geometry().height())?resizeHeight:_parent->geometry().height();

    resize(resizeWidth,resizeHeight);
//    qDebug()<<"[resize wid]"<<resizeWidth<<resizeHeight;
//    qDebug()<<this->geometry().width();

    showText = text;
    scrollTimer->start(stepTime);
}

void QTextScroll::setTextColor(QString _color)
{
    color_text = _color;
    QString qssStr = QString("color:#%1;background-color:#%2").arg(color_text).arg(color_bak);
    qDebug()<<_color;
    qDebug()<<"[setstylesheet]"<<qssStr;
    this->setStyleSheet(qssStr);
}

void QTextScroll::setBackColor(QString _color)
{
    color_bak = _color;
    QString qssStr = QString("color:#%1;background-color:#%2").arg(color_text).arg(color_bak);
    qDebug()<<_color;
    qDebug()<<"[setstylesheet]"<<qssStr;
    this->setStyleSheet(qssStr);
}

void QTextScroll::updateIndex()//刷新滚动参数curIndex
{
    update();
    curIndex++;
    if (curIndex*stepWidth > width())
        curIndex = 0;
}

void QTextScroll::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawText(0-stepWidth*curIndex, (this->geometry().height()+textHeight)/2, showText);//画左半部分的文字
    painter.drawText(width() - stepWidth*curIndex, (this->geometry().height()+textHeight)/2, showText.left(curIndex));//画右半部分的文字
}

