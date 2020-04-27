#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QPaintEvent>
#include <QPushButton>
#include <QButtonGroup>
#include <QPainter>
#include <QLineEdit>
#include <QTextEdit>
#include <QFont>

#include <QTimer>
#include "singleton.h"

namespace Ui {
class KeyBoard;
}

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
    QLineEdit* curFocusedLineEdit;

    enum IconFunc{
        func_caps_lock = 0xf062,
        func_back_space = 0xf177,
//        enter = ,
//        space,
        func_hide = 0xf103,
    };

    enum BtnFunc{
        btn_caps_lock,
        btn_num,
        btn_en_cn,
        btn_cn_en,
        btn_space,
        btn_enter,
        btn_hide,
        btn_backspace,
        btn_more,
        btn_back,
    };

    Ui::KeyBoard *ui;
    void paintEvent(QPaintEvent *);
    bool event(QEvent *e);
    bool eventFilter(QObject *watched, QEvent *event);
    void init();
    void initIcons();
//    void initFuncMap();
    void filterFuncBtns();
    void setBtnIcon(QPushButton* btn, IconFunc func);
    void outPut(QString outStr);
    void outPutEn(QString outStr);
    void outPutCN(QString outStr);

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


    QList<QPushButton*> list_icon_btn;//设置了iconfont的按钮
    QList<QPushButton*> list_input_btn;
    QPushButton* clickedBtn;//被点击的按钮

    const static QMap<QString, BtnFunc> map_text_func = {
        {"返回", btn_back},
        {QString(QChar(func_caps_lock)), btn_caps_lock},
        {"?123", btn_num},
        {"英/中", btn_en_cn},
        {"中/英", btn_cn_en},
        {"空格", btn_space},
        {"回车", btn_enter},
        {QString(QChar(func_hide)), btn_hide},
        {QString(QChar(func_back_space)), btn_backspace},
        {"更多", btn_more},
    };
    QMap<IconFunc, QPushButton*> map_func_btn;

    QString m_position;
    QString m_keyFont;
    int m_fontSize;
    QString m_inputMode;
};

#endif // KEYBOARD_H
