#include "keyboard.h"
#include "ui_keyboard.h"
#include <QDebug>

#include "iconfont/iconhelper.h"

KeyBoard::KeyBoard(QWidget *parent) :
    QWidget(parent),curFocusedWidget(0),
    ui(new Ui::KeyBoard)
{
    ui->setupUi(this);
    setFontSize(20);
    setkeyFont("微软雅黑");
    init();
}

KeyBoard::~KeyBoard()
{
    delete ui;
}

QString KeyBoard::position() const
{
    return m_position;
}

void KeyBoard::setPosition(QString position)
{
    if (m_position == position)
        return;

    m_position = position;
    emit positionChanged(m_position);
}

bool KeyBoard::event(QEvent *e)
{
    switch (e->type()) {
//! [1]
    case QEvent::WindowActivate:
        if (curFocusedWidget)
            curFocusedWidget->activateWindow();
        break;
//! [1]
    default:
        break;
    }

    return QWidget::event(e);
}

bool KeyBoard::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this) {
        //处理自身拖动
        static QPoint mousePoint;
        static bool mousePressed = false;
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

        //按下的时候记住坐标,移动到鼠标松开的位置
        if (event->type() == QEvent::MouseButtonPress) {
            if (mouseEvent->button() == Qt::LeftButton) {
                mousePressed = true;
                mousePoint = mouseEvent->globalPos() - this->pos();
                return true;
            }
        } else if (event->type() == QEvent::MouseButtonRelease) {
            mousePressed = false;
            return true;
        } else if (event->type() == QEvent::MouseMove) {
            if (mousePressed && (mouseEvent->buttons() && Qt::LeftButton && position() != "bottom")) {
                this->move(mouseEvent->globalPos() - mousePoint);
                this->update();
                return true;
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void KeyBoard::init()
{
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
    setWindowFlags(Qt::Tool | Qt::WindowDoesNotAcceptFocus | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
#else
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
#endif

    initIcons();
    foreach (QPushButton* btn, this->findChildren<QPushButton*>())
    {
        connect(btn, SIGNAL(clicked()), this, SLOT(keyClicked()));
    }

    filterFuncBtns();

    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)),
            this, SLOT(saveFocusWidget(QWidget*,QWidget*)));
    this->installEventFilter(this);
    //    qApp->installEventFilter(this);
}

void KeyBoard::initIcons()
{
    if(!list_icon_btn.isEmpty())
    {
//        qDeleteAll(list_icon_btn);
        map_func_btn.clear();
        list_icon_btn.clear();
    }
    setBtnIcon(ui->key_37, KeyBoard::func_caps_lock);

    setBtnIcon(ui->key_43, KeyBoard::func_back_space);
    setBtnIcon(ui->key_79, KeyBoard::func_back_space);
    setBtnIcon(ui->key_103, KeyBoard::func_back_space);

    setBtnIcon(ui->key_49, KeyBoard::func_hide);
    setBtnIcon(ui->key_87, KeyBoard::func_hide);
    setBtnIcon(ui->key_84, KeyBoard::func_hide);

//    list_icon_btn<<

    //    qDebug()<<ui->key_37->text().to.toHex();
}

//初始化功能映射，如果按键上的文字或者iconfont被修改了，需要此处修改映射关系
//void KeyBoard::initFuncMap()
//{
//    if(!map_text_func.isEmpty())
//        map_text_func.clear();

//    map_text_func.insert("返回", btn_back);
//    map_text_func.insert(QString(QChar(func_caps_lock)), btn_caps_lock);
//    map_text_func.insert("?123", btn_num);
//    map_text_func.insert("英/中", btn_en_cn);
//    map_text_func.insert("中/英", btn_cn_en);
//    map_text_func.insert("空格", btn_space);
//    map_text_func.insert("回车", btn_enter);
//    map_text_func.insert(QString(QChar(func_hide)), btn_hide);
//    map_text_func.insert(QString(QChar(func_back_space)), btn_backspace);
//    map_text_func.insert("更多", btn_more);
//}

void KeyBoard::filterFuncBtns()
{
    if(!list_input_btn.isEmpty())
    {
//        qDeleteAll(list_input_btn);
        list_input_btn.clear();
    }

    foreach (QPushButton* btn, this->findChildren<QPushButton*>()){
        if((btn->text().size()==1) && (!list_icon_btn.contains(btn)) || btn->text() == "&&"){
//            btn->setStyleSheet("QPushButton{"
//                               "border:0px silid gray;"
//                               "color:rgb(255, 255, 255);"
//                               "background-color: rgb(36, 0, 149);"
//                               "}");
            list_input_btn<<btn;
        }
    }

}

void KeyBoard::setBtnIcon(QPushButton *btn, IconFunc func)
{
    IconHelper::Instance()->SetIcon(btn, QChar(func), m_fontSize);
    if(!list_icon_btn.contains(btn))
    {
        list_icon_btn<<btn;
        map_func_btn.insert(func, btn);
    }
}

void KeyBoard::outPut(QString outStr)
{
    curFocusedLineEdit->insert(outStr);
}

void KeyBoard::paintEvent(QPaintEvent*)
{
//    QStyleOption opt;
//    opt.init(this);
//    QPainter p(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void KeyBoard::saveFocusWidget(QWidget * /*oldFocus*/, QWidget *newFocus)
{
    if (newFocus != 0 && !this->isAncestorOf(newFocus) && newFocus != curFocusedWidget) {
        qDebug()<<newFocus->metaObject()->className();
//        switch (newFocus->metaObject()->className()) {
//        case "QLineEdit":

//            break;
//        default:
//            break;
//        }
        curFocusedWidget = newFocus;
        qDebug()<<"keyboard show";
        this->show();
    }


}

void KeyBoard::keyClicked()
{
    clickedBtn = static_cast<QPushButton*>(QObject::sender());
    qDebug()<<clickedBtn->text();
    if(list_input_btn.contains(clickedBtn))//输入按键
    {
        outPut(clickedBtn->text());
    }
    else//功能按键
    {
        funcKeyClicked(clickedBtn->text());
    }
}

void KeyBoard::inputKeyClicked()
{

}

void KeyBoard::funcKeyClicked(QString btnText)
{
    switch (map_text_func[btnText]) {
    case btn_caps_lock:
        funcCapsLock();
        break;
    case btn_num:
        funcNum();
        break;
    case btn_en_cn:
        funcEnCn();
        break;
    case btn_cn_en:
        funcCnEn();
        break;
    case btn_space:
        funcSpace();
        break;
    case btn_enter:
        funcEnter();
        break;
    case btn_hide:
        funcHide();
        break;
    case btn_backspace:
        funcBackspace();
        break;
    case btn_more:
        funcMore();
        break;
    case btn_back:
        funcBack();
        break;
    default:
        break;
    }
}


void KeyBoard::funcCapsLock()
{
    foreach (QPushButton* btn, list_input_btn) {
        if(map_func_btn[func_caps_lock]->isChecked())
            btn->setText(btn->text().toUpper());
        else
            btn->setText(btn->text().toLower());
    }
}

void KeyBoard::funcNum()
{

}

//切换成中文模式
void KeyBoard::funcEnCn()
{
    map_func_btn
}

//切换成英文模式
void KeyBoard::funcCnEn()
{

}

void KeyBoard::funcSpace()
{

}

void KeyBoard::funcEnter()
{

}

void KeyBoard::funcHide()
{

}

void KeyBoard::funcBackspace()
{

}

void KeyBoard::funcMore()
{

}

void KeyBoard::funcBack()
{

}

