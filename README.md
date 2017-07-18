# Birdman的代码模块合集

[TOC]
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
