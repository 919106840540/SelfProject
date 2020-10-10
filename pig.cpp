#include "pig.h"
#include<QDebug>
pig::pig(double initial_weight, int color, int number, int Pighouse, int raised_time)//读写文件的时候要改，改或者重载
{
    this->weight = initial_weight;
    this->color = color;
    this->num = number;
    this->pighouse = Pighouse;
    this->raised_time = raised_time;
    qDebug() << "添加";
}

pig::pig()
{

}

void pig::weight_growth()
{
    this->weight += ((double)(rand() % 13)) / 10;   //体重增加
    this->raised_time += 1;  //入栏时间增加
}

double pig::getweight()    {return this->weight;}

int pig::getnum()   {return this->num;}

int pig::getpighouse()   {return this->pighouse;}

int pig::getraisedtime()    {return this->raised_time;}

int pig::getcolor()  {return this->color;}
