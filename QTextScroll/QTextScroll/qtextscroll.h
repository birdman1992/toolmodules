#ifndef QTEXTSCROLL_H
#define QTEXTSCROLL_H

#include <QObject>
#include <QLabel>
#include <QTimer>
#include <QPaintEvent>
#include <QFont>

class QTextScroll : public QLabel
{
    Q_OBJECT
public:
    QTextScroll(QWidget* parent);
    void showScrollText(QString text);
    void setTextColor(QString _color);
    void setBackColor(QString _color);

private:
    int stepWidth;
    int stepTime;
    int curIndex;
    int textHeight;
    QString color_text;
    QString color_bak;
    QFont font;
    QString showText;
    QTimer *scrollTimer;
    QWidget* _parent;

private slots:
    void updateIndex();

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // QTEXTSCROLL_H
