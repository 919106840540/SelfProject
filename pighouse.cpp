#include "pighouse.h"
#include"widget.h"
#include<QDebug>
#include<QtAlgorithms>

pigHouse::pigHouse(QObject *parent) : QObject(parent)//读取文件要改进
{
    //this->num = num;
    this->size = 0;
    this->hei_num = 0;
    this->xiaohua_num = 0;
    this->dahua_num = 0;
}

void pigHouse::pig_in(pig* pg)  //录入品种，数量，
{
    this->size ++;

    if(pg->color == 0)
        this->hei_num ++;

    if(pg->color == 1)
        this->xiaohua_num ++;

    if(pg->color == 2)
        this->dahua_num ++;
    this->pg.push_back(pg);
}

int pigHouse::pig_out() //每三个月，体重超过150， 饲养超过1年,重新编号！！
{

    //qDebug() << pg.size();
    int sales = 0;
    for(int i = 0; i < this->pg.size(); i ++)
    {
        //黑猪15，小花猪7，大白花猪6


        if(this->pg[i]->weight >= 150 || this->pg[i]->raised_time > 365)
        {
            if(this->pg[i]->color == 0)
            {
                this->hei_num --;
                sales += 15 * this->pg[i]->weight;
            }


            if(this->pg[i]->color == 1)
            {
                this->xiaohua_num --;
                sales += 7 * this->pg[i]->weight;
            }

            if(this->pg[i]->color == 2)
            {
                this->dahua_num --;
                sales += 6 * this->pg[i]->weight;
            }

            this->size --;

            qDebug() << "出栏啦,本次出栏"  ;
            this->pg.removeAt(i);
        }
    }
    //统计售价
    return sales;
}

int pigHouse::getnum(){return this->num;}
int pigHouse::getsize(){return this->size;}
int pigHouse::getdahua_num(){return this->dahua_num;}
int pigHouse::gethei_num(){return this->hei_num;}
int pigHouse::getxiaohua_num(){return this->xiaohua_num;}

int pigHouse::setnum(int x){this->num = x;}



