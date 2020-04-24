#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QTimer>
#include <qpainter.h>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    textscrol = new QTextScroll(ui->frame);//实现代码请参考QTextScroll类
//    textscrol->resize(726,181);
//    textscrol->move(0,0);
    textscrol->showScrollText("qt实现无缝滚动字幕，刷新间隔任意调节");
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::paintEvent(QPaintEvent*)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    p.fillRect(this->rect(), QColor(100, 100, 100, 100));
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MainWidget::on_text_returnPressed()
{
    textscrol->showScrollText(ui->text->text());
}

void MainWidget::on_foround_returnPressed()
{
    textscrol->setTextColor(ui->foround->text());
}

void MainWidget::on_background_returnPressed()
{
    textscrol->setBackColor(ui->background->text());
}
