#include "iconwidget.h"
#include "ui_iconwidget.h"
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>

IconWidget::IconWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IconWidget)
{
    ui->setupUi(this);
    drawBg();
    on_size_tar_editingFinished();
    updateStyle();
    updateIcon();
}

IconWidget::~IconWidget()
{
    delete ui;
}

void IconWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawTiledPixmap(ui->area_design->rect(), pixBg);
}

void IconWidget::drawBg()
{
    QColor color1 = QColor("#dcdcdc");
    QColor color2 = QColor("#ffffff");
    pixBg = QPixmap(64,64);
    pixBg.fill(color1);
    QPainter painter(&pixBg);
    painter.fillRect(0,0,32,32,color2);
    painter.fillRect(32,32,32,32,color2);
    painter.end();
    update();
}


void IconWidget::on_size_tar_editingFinished()
{
    int sz = ui->size_tar->text().toInt();
    ui->target->resize(sz,sz);
    ui->target2->resize(sz,sz);
}

void IconWidget::on_size_icon_editingFinished()
{
    updateIcon();
}

void IconWidget::on_color_tar_editingFinished()
{
    updateStyle();
}

void IconWidget::on_color_icon_editingFinished()
{
    updateStyle();
}

void IconWidget::on_icon_code_editingFinished()
{
    updateIcon();
}

void IconWidget::updateIcon()
{
    QString code = ui->icon_code->text();
    if(code.size() > 4)
        return;

    bool ok = false;
    ushort iconCode = code.toUShort(&ok, 16);
    if(!ok)
        return;

    int iconSz = ui->size_icon->text().toInt();
    IconHelper::Instance()->SetIcon(ui->target, QChar(iconCode), iconSz);
    int sz = ui->size_tar->text().toInt();
    ui->target2->setIconSize(QSize(sz, sz));
    ui->target2->setIcon(IconHelper::Instance()->GetIcon(sz, QChar(iconCode), iconSz, ui->color_tar->text(), ui->color_icon->text()));
}

void IconWidget::updateStyle()
{
    QString styleStr = QString("QLabel{"
                               "background-color:%1;"
                               "color:%2;"
                               "}").arg(ui->color_tar->text()).arg(ui->color_icon->text());
    ui->target->setStyleSheet(styleStr);
    updateIcon();
}

void IconWidget::on_get_icon_clicked()
{
    int sz = ui->size_tar->text().toInt();
    int iconSz = ui->size_icon->text().toInt();
    QString code = ui->icon_code->text();
    if(code.size() > 4)
        return;

    bool ok = false;
    ushort iconCode = code.toUShort(&ok, 16);
    if(!ok)
        return;

    QIcon icon = IconHelper::Instance()->GetIcon(sz, QChar(iconCode), iconSz, ui->color_tar->text(), ui->color_icon->text());

    QString outputFile = QFileDialog::getSaveFileName(NULL, "导出", "output.png", ".png");
    if(icon.pixmap(QSize(sz,sz)).save(outputFile, "PNG"))
    {
        ui->msg->setText("导出成功");
    }
    else
    {
        ui->msg->setText("导出失败");
    }
    QTimer::singleShot(2000, this, [&](){ui->msg->clear();});
}
