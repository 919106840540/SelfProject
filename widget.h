#ifndef WIDGET_H
#define WIDGET_H
#include"pighouse.h"
#include <QWidget>
#include<form_pig.h>

int find_least_hei_num(pigHouse* zhujuan);//找出猪数目最小的黑猪圈编号
int find_least_else_num(pigHouse* zhujuan);//找出猪数目最小的其余猪圈编号
void loadfile();//读取文本文档的信息
void savefile();//存入文本文档
//void find_pig();
//void find_pighouse();
//void find_pighouse(int num);
//void find_pig(int num1, int num2);

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();



private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
