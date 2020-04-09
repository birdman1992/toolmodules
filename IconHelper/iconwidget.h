#ifndef ICONWIDGET_H
#define ICONWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>
#include "iconfont/iconhelper.h"

QT_BEGIN_NAMESPACE
namespace Ui { class IconWidget; }
QT_END_NAMESPACE

class IconWidget : public QWidget
{
    Q_OBJECT

public:
    IconWidget(QWidget *parent = nullptr);
    ~IconWidget();

protected:
    void paintEvent(QPaintEvent* event);
    void drawBg();

private slots:
    void on_size_tar_editingFinished();

    void on_size_icon_editingFinished();

    void on_color_tar_editingFinished();

    void on_color_icon_editingFinished();

    void on_icon_code_editingFinished();

    void on_get_icon_clicked();

private:
    Ui::IconWidget *ui;
    QPixmap pixBg;
    void updateIcon();
    void updateStyle();
};
#endif // ICONWIDGET_H
