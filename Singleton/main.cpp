#include <QApplication>
#include <QWidget>
#include <singletest.h>
#include "singleton.h"

/********************************************
 注意
 1.必须是Singleton的友元类
 2.构造函数必须是私有的
********************************************/

class DerivedSingle:public Singleton<DerivedSingle>
{
    friend class Singleton<DerivedSingle>;
public:
   DerivedSingle(const DerivedSingle&)=delete;
   DerivedSingle& operator =(const DerivedSingle&)= delete;
private:
   DerivedSingle()=default;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //非界面类示例
    DerivedSingle& singleton1 = DerivedSingle::instance();
    DerivedSingle& singleton2 = DerivedSingle::instance();

    //界面类示例
    SingleTest& t1 = SingleTest::instance();
    SingleTest& t2 = SingleTest::instance();

//    t1.show();
//    t2.show();
    return a.exec();
}


