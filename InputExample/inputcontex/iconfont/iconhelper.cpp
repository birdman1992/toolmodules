#include "iconhelper.h"
#include <QDebug>

IconHelper* IconHelper::_instance = 0;
IconHelper::IconHelper(QObject *) :
    QObject(qApp)
{
    int fontId = QFontDatabase::addApplicationFont(":/fonts/fontawesome-webfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    iconFont = QFont(fontName);
}

QFont IconHelper::loadFont(QString fontSrc)
{
    int fontId = QFontDatabase::addApplicationFont(":/fonts/fontawesome-webfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    return QFont(fontName);
}

void IconHelper::initFonts()
{
    lstFont<<loadFont(":/fonts/fontawesome-webfont.ttf");
}

void IconHelper::SetIcon(QLabel *lab, QChar c, int size, QString color, QString backGroundColor)
{
    QString styleStr = QString("QLabel{"
                               "background-color:%1;"
                               "color:%2;"
                               "}").arg(backGroundColor).arg(color);
    iconFont.setPixelSize(size);
    lab->setFont(iconFont);
    lab->setStyleSheet(styleStr);
    lab->setText(c);
}

void IconHelper::SetIcon(QPushButton *btn, QChar c, int size, QString color, QString backGroundColor)
{
    QString styleStr = QString("QLabel{"
                               "background-color:%1;"
                               "color:%2;"
                               "}").arg(backGroundColor).arg(color);
    iconFont.setPixelSize(size);
    btn->setFont(iconFont);
    btn->setStyleSheet(styleStr);
    btn->setFont(iconFont);
    btn->setText(c);
}

QIcon IconHelper::GetIcon(int backGroundSize, QChar c, int fontSize, QString color, QString backGroundColor)
{
    QWidget* backBoard = new QWidget;
    QLabel* lab = new QLabel(c, backBoard);
    QString styleStr = QString("QLabel{"
                               "background-color:%1;"
                               "color:%2;"
                               "}").arg(backGroundColor).arg(color);
    lab->setStyleSheet(styleStr);
    lab->setAlignment(Qt::AlignCenter);
    lab->resize(backGroundSize, backGroundSize);
    SetIcon(lab, c, fontSize);
    QIcon ret = QIcon(QPixmap::grabWidget(lab, lab->rect()));
    backBoard->deleteLater();
    return ret;
}
