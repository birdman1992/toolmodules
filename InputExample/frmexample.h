#ifndef FRMEXAMPLE_H
#define FRMEXAMPLE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class FrmExample; }
QT_END_NAMESPACE

class FrmExample : public QWidget
{
    Q_OBJECT

public:
    FrmExample(QWidget *parent = nullptr);
    ~FrmExample();

private:
    Ui::FrmExample *ui;
};
#endif // FRMEXAMPLE_H
