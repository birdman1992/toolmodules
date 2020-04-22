#ifndef SINGLETON_H
#define SINGLETON_H

#include <QDebug>
#include <QMutex>
template<typename T>
class Singleton{
public:
    static T& instance(){
        static QMutex mutex;
        static QMutexLocker locker(&mutex);
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
