#include "imsougou.h"
#include <QFile>
#include <QtDebug>
#include <WinSock2.h>

#define typeof(x) __typeof__(x)
//把数字变量写入缓冲区
#define MEM_ASSIGN(a,b) ({*(typeof(b)*)(a)=(b);(a)+=sizeof(b);})
#define MEM_ASSIGN_ARRAY(a,b) ({memcpy((a), (b).data(), (b).size());(a)+=(b).size();})
//从缓冲区读取数字变量值
#define MEM_FETCH(a,b) ({(a)=*(typeof(a)*)(b);(b)+=sizeof(a);})
//#define MEM_FETCH_ARRAY(a,b) (a=QByteArray())

#define PY_TABLE_OFFSET 0x1540
#define WORD_TABLE_OFFSET 0x2628

ImSougou::ImSougou(QObject *parent) : InputMethod(parent)
{

}

QStringList ImSougou::getPinYinTable(QString input)
{
    QVector<int> v_idx;//符合匹配的拼音下标
    foreach (QString py, pyTable) {
        if(py.indexOf(input) >= 0)

    }
}

QStringList ImSougou::getWordTable(QString input)
{

}

void ImSougou::loadLexicon(QString path)
{
    QFile f(path);
    if(!f.open(QFile::ReadOnly))
        return;

    lexiconCache = f.readAll();
    f.close();

    loadPyTable(PY_TABLE_OFFSET);
    loadWordTable(WORD_TABLE_OFFSET);
    return;
}

void ImSougou::loadPyTable(int offset)
{
    if(lexiconCache.mid(offset, 4).toHex() != "9d010000"){
        qDebug()<<"词库格式错误";
        return;
    }
    offset += 4;

    if(offset>lexiconCache.size())
        return;

    pyTable.clear();
    char* pos = lexiconCache.data()+offset;
    while (pos < lexiconCache.data() + WORD_TABLE_OFFSET) {
        quint16 idx,len;
        MEM_FETCH(idx, pos);
        MEM_FETCH(len, pos);

        QByteArray pinyinByte = QByteArray(lexiconCache.mid(pos-lexiconCache.data(), len));
        pos += len;
        QString pyStr = QString::fromUtf16((ushort*)pinyinByte.data(), pinyinByte.size()/sizeof(ushort));
        pyTable.append(QString(pyStr));
//        qDebug()<<pyTable;
//        qDebug()<<idx<<len<<pyStr<<pinyinByte.toHex()<<sizeof(QChar);
    }
//    qDebug()<<pyTable;
}

void ImSougou::loadWordTable(int offset)
{
    if(offset>lexiconCache.size())
        return;

    char* pos = lexiconCache.data()+offset;
    while (pos < lexiconCache.data() + lexiconCache.size()) {
        quint16 sameCount,pyTbLen,wordTableLen,extLen,ext;
//        qDebug()<<lexiconCache.mid(offset, 50).toHex();
        MEM_FETCH(sameCount, pos);//同音词数量
        MEM_FETCH(pyTbLen, pos);//拼音表长度
        QStringList pyList;
        for(int i=0; i<pyTbLen/sizeof(quint16); i++)
        {
            quint16 pyIndex;
            MEM_FETCH(pyIndex, pos);
//            qDebug()<<pyIndex<<pyTable.at(pyIndex);
            pyList<<pyTable.at(pyIndex);
        }
//        qDebug()<<"same:"<<sameCount;
        qDebug()<<pyList;

        for(int i=0; i<sameCount; i++)
        {
            MEM_FETCH(wordTableLen, pos);//词组长度
            QByteArray wordByte = lexiconCache.mid(pos - lexiconCache.data(), wordTableLen);
            pos += wordTableLen;
            MEM_FETCH(extLen, pos);//扩展信息长度
            MEM_FETCH(ext, pos);
            pos += extLen-2;
            qDebug()<<QString::fromUtf16((ushort*)wordByte.data(), wordByte.size()/sizeof(ushort))<<ext;
        }
    }
}

ImSougou::~ImSougou()
{

}
