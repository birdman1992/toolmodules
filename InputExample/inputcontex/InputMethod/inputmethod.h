#ifndef INPUTMETHOD_H
#define INPUTMETHOD_H

#include <QObject>
#include <QStringList>

class InputMethod : public QObject
{
    Q_OBJECT
public:
    explicit InputMethod(QObject *parent = nullptr);
    virtual ~InputMethod();
    virtual void loadLexicon(QString path);
    virtual QStringList getPinYinTable(QString input);
    virtual QStringList getWordTable(QString input);

signals:

};

#endif // INPUTMETHOD_H
