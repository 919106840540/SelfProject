#ifndef PIG_H
#define PIG_H

#include <QObject>

class pig : public QObject
{
    Q_OBJECT

    friend class pigHouse;

    double weight;

    int num;    //编号

    int color;  //0为黑猪，1为小花猪， 2为大白花猪

    int pighouse;

    int raised_time;


public:


    pig(double initial_weight, int color, int number, int Pighouse, int raised_time = 0);

    pig();

    double getweight();//获取当前体重

    int getnum();//获取猪圈编号

    int getcolor();//获取颜色

    int getpighouse();//获取猪圈号

    int getraisedtime();//获取饲养时间

    void weight_growth();//增加体重和饲养时间

signals:

public slots:
};

#endif // PIG_H
