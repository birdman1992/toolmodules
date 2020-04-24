#include "frmexample.h"
#include "ui_frmexample.h"
#include <QMessageBox>
#include <QDebug>

// google拼音接口
#include "xygooglepinyin.h"


FrmExample::FrmExample(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrmExample)
{
    ui->setupUi(this);

    googlePinyin = new pinyin_im;
    bool ret = googlePinyin->init(qApp->applicationDirPath() + "/dict");
    if (!ret)
    {
        ret = googlePinyin->init(qApp->applicationDirPath()
                                 +  "/../../InputExample/libgooglepinyin/dict");
    }
    if (!ret) {
        QMessageBox::warning(NULL, "warning", "Load lexicon failed!", QMessageBox::Ok);
    }
    alreadyInputLetters = "xg";

    if (alreadyInputLetters.size() > 26) // 如果查询内容太长google库崩溃
    {
//        return true;
    }
    unsigned cand_num = googlePinyin->search(alreadyInputLetters.toLower());

    QString str_data;
    for (unsigned i = 0; i < cand_num; i++)
    {
        QString str = googlePinyin->get_candidate(i);
        str_data = str_data + " " + str;
    }

    ui->textEdit->append("xg: " + str_data);

}

FrmExample::~FrmExample()
{
    delete ui;
}

