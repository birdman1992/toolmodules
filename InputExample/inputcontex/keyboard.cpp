#include "keyboard.h"
#include "ui_keyboard.h"
#include <QDebug>

#include "iconfont/iconhelper.h"


////功能->按钮映射
//const static QMap<BtnFunc, QPushButton*> map_func_btn = {
//    {},

//};

KeyBoard::KeyBoard(QWidget *parent) :
    QWidget(parent),curFocusedWidget(0),
    ui(new Ui::KeyBoard)
{
    ui->setupUi(this);
    setInputMode("en");
    setFontSize(20);
    setkeyFont("微软雅黑");
    init();
    qDebug()<<QApplication::applicationDirPath()+ "/style.qss";
    setKeyboardStyle(QApplication::applicationDirPath()+ "/style.qss");
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

    initMaps();
    initIcons();
    map_func_btn.clear();

    foreach (QPushButton* btn, this->findChildren<QPushButton*>())
    {
        connect(btn, SIGNAL(clicked()), this, SLOT(keyClicked()));
        if(map_text_func.contains(btn->text()))
        {
            map_func_btn.insert(map_text_func.value(btn->text()), btn);//初始化文本->按钮映射
            qDebug()<<btn->text()<<btn;
        }
    }
    //初始化复用按钮映射
    mapReuseBtn("中/英", "英/中");

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

        list_icon_btn.clear();
    }
    setBtnIcon(ui->key_37, KeyBoard::icon_caps_lock);

    setBtnIcon(ui->key_43, KeyBoard::icon_back_space);
    setBtnIcon(ui->key_79, KeyBoard::icon_back_space);
    setBtnIcon(ui->key_103, KeyBoard::icon_back_space);

    setBtnIcon(ui->key_49, KeyBoard::icon_hide);
    setBtnIcon(ui->key_87, KeyBoard::icon_hide);
    setBtnIcon(ui->key_84, KeyBoard::icon_hide);

//    list_icon_btn<<

    //    qDebug()<<ui->key_37->text().to.toHex();
}

//文字->功能映射，如果按键上的文字或者iconfont被修改了，需要此处修改映射关系
void KeyBoard::initMaps()
{
    map_text_func.clear();
    map_text_func.insert("返回", func_back);
    map_text_func.insert(QString(QChar(KeyBoard::icon_caps_lock)), func_caps_lock);
    map_text_func.insert("?123", func_num);
    map_text_func.insert("英/中", func_en_cn);
    map_text_func.insert("中/英", func_cn_en);
    map_text_func.insert("空格", func_space);
    map_text_func.insert("回车", func_enter);
    map_text_func.insert(QString(QChar(KeyBoard::icon_hide)), func_hide);
    map_text_func.insert(QString(QChar(KeyBoard::icon_back_space)), func_backspace);
    map_text_func.insert("更多", func_more);
    map_text_func.insert("&&", func_and);
}


/*!
 * \brief KeyBoard::mapReuseBtn
 * \param btn_text 复用的未被绑定按钮文本
 * \param binded_btn_text 被复用的已经绑定的按钮文本
 */
void KeyBoard::mapReuseBtn(QString btn_text, QString binded_btn_text)
{
    BtnFunc func = map_text_func.value(btn_text);
    BtnFunc func_binded = map_text_func.value(binded_btn_text);
    map_func_btn.insert(func, map_func_btn.value(func_binded));
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
        if((btn->text().size()==1) && ((!list_icon_btn.contains(btn)) || btn->text() == "&&")){
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
    }
}

void KeyBoard::outPut(QString outStr)
{
    if(curFocusedWidget->metaObject()->className() == QString("QLineEdit"))
        static_cast<QLineEdit*>(curFocusedWidget)->insert(outStr);
}

void KeyBoard::sendKeyEvent(Qt::Key key)
{
    qDebug()<<"sendevent:"<<key;
    QKeyEvent kEvent = QKeyEvent(QEvent::KeyPress, key, Qt::NoModifier, QString());
    QCoreApplication::sendEvent(curFocusedWidget, &kEvent);
    kEvent = QKeyEvent(QEvent::KeyRelease, key, Qt::NoModifier, QString());
    QCoreApplication::sendEvent(curFocusedWidget, &kEvent);
}

void KeyBoard::setKeyboardStyle(QString fileStyle)
{
    QFile f(fileStyle);
    if(f.open(QFile::ReadWrite))
    {
        if(f.size() == 0)
        {
            f.write(QByteArray("QWidget{\n"
                            "background-color: #233634;\n"
                            "}\n"
                            "QPushButton{\n"
                            "border:1px solid gray;\n"
                            "border-radius:6px;\n"
                            "color:rgb(255, 255, 255);\n"
                            "background-color: #233634;\n"
                            "}\n"
                            "QPushButton:pressed{\n"
                            "color:rgb(255, 255, 255);\n"
                            "background-color: #233634;\n"
                            "margin:3px;\n"
                            "}\n"
                            "QPushButton:checked{\n"
                            "color:#76B5AF;\n"
                            "background-color: #233634;\n"
                            "}"));
            f.flush();
            f.seek(0);
        }
        QString qss = QString::fromLocal8Bit(f.readAll()).remove("\r\n");
//        qDebug()<<"qss"<<qss;
        this->setStyleSheet(qss);
        f.close();
    }
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
        curFocusedWidget = newFocus;
        curFocusedWidgetType = newFocus->metaObject()->className();
//        qDebug()<<"keyboard show"<<QApplication::desktop()->availableGeometry();

        QPoint showPos = curFocusedWidget->mapToGlobal(curFocusedWidget->rect().bottomLeft());
        if(this->geometry().height() + showPos.y() > QApplication::desktop()->availableGeometry().height())
        {
            showPos.setY(showPos.y() - curFocusedWidget->geometry().height() - this->geometry().height());
        }
        this->move(showPos);
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
    case func_caps_lock:
        funcCapsLock();
        break;
    case func_num:
        funcNum();
        break;
    case func_en_cn:
        funcEnCn();
        break;
    case func_cn_en:
        funcCnEn();
        break;
    case func_space:
        funcSpace();
        break;
    case func_enter:
        funcEnter();
        break;
    case func_hide:
        funcHide();
        break;
    case func_backspace:
        funcBackspace();
        break;
    case func_more:
        funcMore();
        break;
    case func_back:
        funcBack();
        break;
    case func_and:
        funcAnd();
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
    ui->stackedWidget->setCurrentWidget(ui->page_num);
}

//切换成中文模式
void KeyBoard::funcEnCn()
{
    map_func_btn[func_en_cn]->setText("中/英");
    setInputMode("cn");
}

//切换成英文模式
void KeyBoard::funcCnEn()
{
    map_func_btn[func_cn_en]->setText("英/中");
    setInputMode("en");
}

void KeyBoard::funcSpace()
{
    outPut(" ");
}

void KeyBoard::funcEnter()
{
    sendKeyEvent(Qt::Key_Enter);
}

void KeyBoard::funcHide()
{
    this->hide();
}

void KeyBoard::funcBackspace()
{
    sendKeyEvent(Qt::Key_Backspace);
}

void KeyBoard::funcMore()
{
    ui->stackedWidget->setCurrentWidget(ui->page_more);
}

void KeyBoard::funcBack()
{
    ui->stackedWidget->setCurrentWidget(ui->page_cn_en);
}

void KeyBoard::funcAnd()
{
    outPut("&");
}

