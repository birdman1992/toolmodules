#include "frmexample.h"
#include "ui_frmexample.h"

FrmExample::FrmExample(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrmExample)
{
    ui->setupUi(this);
}

FrmExample::~FrmExample()
{
    delete ui;
}

