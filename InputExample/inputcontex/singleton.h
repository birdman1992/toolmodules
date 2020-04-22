#ifndef SINGLETON_H
#define SINGLETON_H

#include <QDebug>
#include <QMutex>
#include <QMutexLocker>

template<typename T>
class Singleton{
public:
    static T& instance(){
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        qDebug()<<"lock over";
        static T _instance;
        return _instance;
    }
    virtual ~Singleton(){
        qDebug()<<"singelton delete.";
    }
    Singleton(const Singleton&)=delete;
    Singleton& operator =(const Singleton&)=delete;
protected:
    Singleton(){
        qDebug()<<"singelton create.";
    }
};

#endif // SINGLETON_H
