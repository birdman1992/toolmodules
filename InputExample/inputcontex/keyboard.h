#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPushButton>
#include <QButtonGroup>
#include <QPainter>
#include <QLineEdit>
#include <QTextEdit>
#include <QFont>
#include <QStyle>
#include <QFile>
#include <QByteArray>

#include <QTimer>
#include "singleton.h"

namespace Ui {
class KeyBoard;
}

enum BtnFunc{
    func_caps_lock,
    func_num,
    func_en_cn,
    func_cn_en,
    func_space,
    func_enter,
    func_hide,
    func_backspace,
    func_more,
    func_back,
    func_and,
};


class KeyBoard : public QWidget, public Singleton<KeyBoard>
{
    Q_OBJECT
    Q_PROPERTY(QString position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QString keyFont READ keyFont WRITE setkeyFont)
    Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize)
    Q_PROPERTY(QString inputMode READ inputMode WRITE setInputMode NOTIFY inputModeChanged)//输入模式, 英文：en|中文：cn

    friend class Singleton<KeyBoard>;
public:
    ~KeyBoard();

    enum IconFunc{
        icon_caps_lock = 0xf062,
        icon_back_space = 0xf177,
    //        enter = ,
    //        space,
        icon_hide = 0xf103,
    };

    QString position() const;
    QString keyFont() const
    {
        return m_keyFont;
    }

    int fontSize() const
    {
        return m_fontSize;
    }

    QString inputMode() const
    {
        return m_inputMode;
    }

public slots:
    void setPosition(QString position);


    void setkeyFont(QString font)
    {
        if (m_keyFont == font)
            return;

        m_keyFont = font;
        QFont _font;
        _font.setFamily(m_keyFont);
        _font.setPixelSize(m_fontSize);
//        qDebug()<<"setfont"<<m_keyFont<<m_fontSize;
        foreach (QPushButton* btn, this->findChildren<QPushButton*>()) {
            btn->setFont(_font);
        }
    }

    void setFontSize(int fontSize)
    {
        m_fontSize = fontSize;
    }

    void setInputMode(QString inputMode)
    {
        if (m_inputMode == inputMode)
            return;

        m_inputMode = inputMode;
        emit inputModeChanged(m_inputMode);
    }

signals:

    void positionChanged(QString position);

    void inputModeChanged(QString inputMode);

private slots:
    void saveFocusWidget(QWidget *, QWidget *newFocus);
    void keyClicked();
    void inputKeyClicked();
    void funcKeyClicked(QString btnText);

private:
    explicit KeyBoard(QWidget *parent = 0);
    QWidget *curFocusedWidget;
    QString curFocusedWidgetType;

    Ui::KeyBoard *ui;
    void paintEvent(QPaintEvent *);
    bool event(QEvent *e);
    bool eventFilter(QObject *watched, QEvent *event);
    void init();
    void initIcons();
    void initMaps();
    void mapReuseBtn(QString btn_text, QString binded_btn_text);
//    void initFuncMap();
    void filterFuncBtns();
    void setBtnIcon(QPushButton* btn, IconFunc func);
    void input();
    void outPut(QString outStr);
    void outPutEn(QString outStr);
    void outPutCN(QString outStr);
    void sendKeyEvent(Qt::Key key);
    void setKeyboardStyle(QString fileStyle);

    //funcs
    void funcCapsLock();
    void funcNum();
    void funcEnCn();
    void funcCnEn();
    void funcSpace();
    void funcEnter();
    void funcHide();
    void funcBackspace();
    void funcMore();
    void funcBack();
    void funcAnd();


    QList<QPushButton*> list_icon_btn;//设置了iconfont的按钮
    QList<QPushButton*> list_input_btn;
    QPushButton* clickedBtn;//被点击的按钮

    QMap<QString, BtnFunc> map_text_func;
    QMap<BtnFunc, QPushButton*> map_func_btn;

    QString m_position;
    QString m_keyFont;
    int m_fontSize;
    QString m_inputMode;
};

#endif // KEYBOARD_H
