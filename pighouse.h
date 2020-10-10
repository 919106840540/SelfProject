#ifndef PIGHOUSE_H
#define PIGHOUSE_H
#include<pig.h>
#include <QObject>
#include<QLinkedList>
#include<QList>
class pigHouse : public QObject
{
    Q_OBJECT

    int num;
    int size;
    int hei_num;
    int xiaohua_num;
    int dahua_num;

public:



//    QLinkedList <pig*> pg;
    QList<pig*> pg;

    explicit pigHouse(QObject *parent = nullptr);
    int pig_out();//猪出栏，删除猪的指针
    void pig_in(pig* pg);//猪入栏，添加猪的指针
    int getnum();//获取猪圈编号
    int getsize();//获取猪圈有多少猪
    int gethei_num();//获取黑猪数量
    int getxiaohua_num();//获取小花猪数量
    int getdahua_num();//获取大花猪数量
    int setnum(int x);//设置猪圈编号



signals:

public slots:
};

#endif // PIGHOUSE_H
