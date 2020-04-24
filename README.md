# Birdman's tool modules
- [Birdman的代码模块合集](#birdmans-tool-modules)
    - [汉字转拼音](#chineseletterhelper)
    - [监视设备热插拔](#qdevicewatcher)
    - [Qt滚动文本](#qtextscroll)
    - [多项式曲线拟合](#polcurvefit)

## ChineseLetterHelper
* 功能：获取汉字的拼音，或者拼音首字母
* 接口：
```cpp
static QString GetFirstLetter(const QString &src);//获取第一个汉字的首字母
static QString GetFirstLetters(const QString &src);//获取所有汉字的首字母
static QString GetFirstLettersAll(const QString &src);//获取所有汉字的首字母，加强版，二级汉字也能获取
static QString GetPinyin(int code);// 获取一个汉字编码的汉语拼音
static QString GetPinyins(const QString& text);// 获取所有汉字的汉语拼音
```
* 示例：
```cpp
QString str("Birdman的代码模块合集");
qDebug()<<"src:"<<str;
qDebug()<<"First letter:"<<ChineseLetterHelper::GetFirstLetter(str);
qDebug()<<"First letters:"<<ChineseLetterHelper::GetFirstLetters(str);
qDebug()<<"First letters all:"<<ChineseLetterHelper::GetFirstLettersAll(str);
qDebug()<<"Pinyin letters:"<<ChineseLetterHelper::GetPinyins(str);
```

## QDeviceWatcher
* 功能：实时监视设备的热插拔
* 接口：
```cpp
    int addDevice(QString deviceName);//添加设备到监控列表
    int removeDevice(QString deviceName);//从监控列表移除设备
    QStringList getDevices();//获取设备列表
```
* 示例：见mainwidget.cpp
```cpp
    QDeviceWatcher devWatcher = new QDeviceWatcher(this);//创建对象
    devWatcher->addDevice("hidraw0");//添加监控设备
    connect(devWatcher, SIGNAL(deviceAdded(QString)), this, SLOT(devAdd(QString)));//接收设备添加的信号
    connect(devWatcher, SIGNAL(deviceRemoved(QString)), this, SLOT(devRemove(QString)));//接收设备移除的信号
```

## QTextScroll
* 功能：继承自QLabel，实现文本的滚动
* 接口：
```cpp
    void showScrollText(QString text);//设置滚动文本
    void setTextColor(QString _color);//设置文本颜色
    void setBackColor(QString _color);//设置背景色
```

## PolCurveFit
* 功能：实现输入多点坐标拟合出曲线方程
* 接口：
```cpp
    doubleVector fitStart(vector<point> sample);//输入坐标数组，输出系数数组
```
