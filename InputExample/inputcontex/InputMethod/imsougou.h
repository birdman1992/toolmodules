#ifndef IMSOUGOU_H
#define IMSOUGOU_H

#include "inputmethod.h"
#include <QObject>
#include <QByteArray>
#include <QVector>

class WordInfo
{
public:
    WordInfo(const QString& wd, quint16 info) :word(wd){
//        word = wd;
        exInfo = info;
    }
    QString word;//����
    quint16 exInfo;//��չ��Ϣ
};

class ImSougou : public InputMethod
{
    Q_OBJECT

    ~ImSougou();
public:
    explicit ImSougou(QObject *parent = nullptr);

    // InputMethod interface
public:
    QStringList getPinYinTable(QString input) override;
    QStringList getWordTable(QString input) override;
    void loadLexicon(QString path) override;

    void loadPyTable(int offset);
    void loadWordTable(int offset);

private:
    QByteArray lexiconCache;
    QVector<QString> pyTable;
    QVector<int> index_py;//��ǰ���������ƴ���±껺��
};

#endif // IMSOUGOU_H
