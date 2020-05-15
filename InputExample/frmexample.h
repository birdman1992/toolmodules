#ifndef FRMEXAMPLE_H
#define FRMEXAMPLE_H

#include <QWidget>
class pinyin_im;

QT_BEGIN_NAMESPACE
namespace Ui { class FrmExample; }
QT_END_NAMESPACE

class FrmExample : public QWidget
{
    Q_OBJECT

public:
    FrmExample(QWidget *parent = 0);
    ~FrmExample();

private:
    Ui::FrmExample *ui;
    pinyin_im                *googlePinyin;
    QString                   alreadyInputLetters;     // 用户输入的所有字母
    QStringList               alreadySelectTranslates; // 用户选择的所有中文词组
};
#endif // FRMEXAMPLE_H
