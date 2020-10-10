#include "widget.h"
#include "ui_widget.h"
#include"pig.h"
#include"pighouse.h"
#include<QDebug>
#include<QTimer>
#include<QPushButton>
#include<QString>
#include<QFile>
#include"form_sales.h"
#include"form_chart.h"
#include<QtCharts>
using namespace QtCharts;

int global_time = 0;
bool timer_status;
pigHouse* zhujuan= new pigHouse[100];

int find_least_hei_num(pigHouse* zhujuan)
{
    int min = 11;
    int res = -1;

    for(int i = 0; i < 100; i ++)
    {
        if(zhujuan[i].getdahua_num() == 0 &&
                zhujuan[i].getxiaohua_num() == 0 &&
                zhujuan[i].getsize() < min)
        {
            min = zhujuan[i].getsize();
            res = i;
        }
    }
    return res;
}

int find_least_else_num(pigHouse* zhujuan)
{
    int min = 11;
    int res = -1;

    for(int i = 0; i < 100; i ++)
    {
        if(zhujuan[i].gethei_num() == 0 && zhujuan[i].getsize() < min)
        {
            min = zhujuan[i].getsize();
            res = i;
        }
    }
    return res;
}

void loadfile(){//读数据出现问题
    QFile pig_info("../raisingPigs/info/info_pig.txt");
    pig_info.open(QIODevice::ReadOnly);     //改进，移动光标？不要打开多次
    QString str = pig_info.readAll();
    pig_info.close();

    pig_info.open(QIODevice::ReadOnly);
    QTextStream in(&pig_info);

    //f_pig.resize(100, 100);



    if(! str.isEmpty())//检测
    {
        int num_of_pigs = 0;
        in >> num_of_pigs;
        qDebug() << num_of_pigs;

        for(int k = 0; k < num_of_pigs; k++)
        {
            double t_weight;
            int t_color, t_number, t_pighouse, t_raised_time;
            in >> t_weight >> t_color >> t_number >> t_pighouse >> t_raised_time;

            pig *newpig = new pig(t_weight, t_color, t_number, t_pighouse, t_raised_time);
            zhujuan[t_pighouse].pig_in(newpig);
        }
    }
    pig_info.close();
}

void savefile()
{
    QFile pig_info("../raisingPigs/info/info_pig.txt");
    pig_info.open(QFile::WriteOnly | QFile::Truncate);
    QTextStream out(&pig_info);
    int save_size = 0;

    for(int i = 0; i < 99 ; i++)
    {
        save_size += zhujuan[i].pg.size();
    }
    out << save_size << "\n";

    for(int i = 0; i < 99; i++)
    {
        for(int j = 0; j < zhujuan[i].pg.size(); j++)
        {
            out << zhujuan[i].pg[j]->getweight() <<" "
                << zhujuan[i].pg[j]->getcolor() <<" "
                << zhujuan[i].pg[j]->getnum() <<" "
                << zhujuan[i].pg[j]->getpighouse() <<" "
                << zhujuan[i].pg[j]->getraisedtime() << "\n";
        }
    }
    pig_info.close();
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //加载数据，以后写在函数里
    loadfile();
    //标好序号
    ui->setupUi(this);
    this->resize(1400, 1000);
    this->setWindowTitle("养猪模拟");


    for(int i = 0; i < 100 ; i ++)
        zhujuan[i].setnum(i);

    //时间对应猪长肉

    timer_status = true;

    QTimer* timer = new QTimer(this);

    connect(timer, &QTimer::timeout, [=](){
        global_time ++; //时间增加
        qDebug() << global_time;
        //出栏
        if(global_time > 0 && global_time % 90 == 0)
        {
            QFile out_info("../raisingPigs/info/out_info.txt");
            out_info.open(QIODevice::ReadOnly);     //改进，移动光标？不要打开多次
            QString str = out_info.readAll();
            out_info.close();

            QFile out_info1("../raisingPigs/info/out_info.txt");
            out_info1.open(QFile::WriteOnly | QFile::Append);
            QTextStream out(&out_info1);
            if(! str.isEmpty())
                out << "\n";

            //out << 1 <<" "; //1为出栏
            out << global_time <<" ";
            double sales = 0;
            for(int i = 0; i < 99; i++)
            {
                sales += zhujuan[i].pig_out();
            }
            out << sales;
            out_info1.close();

        }

        //猪长肉,饲养时间增加
        for(int i = 0; i < 99; i++)
            for(int j = 0; j < zhujuan[i].pg.size(); j++)
                zhujuan[i].pg[j]->weight_growth();
    });

    connect(ui->timer_button, &QPushButton::clicked,[=](){
        if(timer_status == true)
        {
            timer->start(100);
            timer_status = false;
            ui->timer_button->setText("停止计时");
        }
        else
        {
            timer->stop();
            timer_status = true;
            ui->timer_button->setText("开始计时");
        }
        //qDebug() << global_time;
    });

    //添加猪

    connect(ui->pushButton_1, &QPushButton::clicked,[=](){  //引用传参解决问题
        int add_num = ui->spinBox_1->value();

        QFile in_info("../raisingPigs/info/in_info.txt");
        in_info.open(QIODevice::ReadOnly);     //改进，移动光标？不要打开多次
        QString str = in_info.readAll();
        in_info.close();

        QFile in_info1("../raisingPigs/info/in_info.txt");
        in_info1.open(QFile::WriteOnly | QFile::Append);
        QTextStream out(&in_info1);

        if(! str.isEmpty())
            out << "\n";

        for(int i = 0; i < add_num; i++)
        {
            double t_weight = 20 + rand() % 31;
            int t_color = rand() % 3;
            int * t_house = new int;
            //黑猪入栏
            if(t_color == 0)
                *t_house = find_least_hei_num(zhujuan);
            if(t_color != 0)
                *t_house = find_least_else_num(zhujuan);

            int t_num = zhujuan[*t_house].pg.size();
            pig *t_pig = new pig(t_weight, t_color, t_num, *t_house);

            qDebug() << "体重" << t_weight << "花色" << t_color << "猪编号" << t_num << "猪圈号" << *t_house;
            zhujuan[*t_house].pig_in(t_pig);

            out << 0 <<" "; //0为进入；
            out << t_pig->getweight() << " " <<
                   t_pig->getcolor() << " " <<
                   t_pig->getnum()<<" " <<
                   t_pig->getpighouse()<<" " <<
                   t_pig->getraisedtime()<<"\n";
        }
        in_info.close();

    });

    //查询猪圈
    connect(ui->pushButton_2, &QPushButton::clicked,[=](){
        int num = ui->spinBox_2->value();//万一是错误的值,在ui设置了最大值
        qDebug() << "查询的是" << num;

        qDebug() << zhujuan[num].pg.size() << zhujuan[num].gethei_num() << zhujuan[num].getxiaohua_num() << zhujuan[num].getdahua_num();
        ui->lineEdit_2_1->setText(QString::number(zhujuan[num].gethei_num()));
        ui->lineEdit_2_2->setText(QString::number(zhujuan[num].getxiaohua_num()));
        ui->lineEdit_2_3->setText(QString::number(zhujuan[num].getdahua_num()));

    });

    //查询具体的猪
    connect(ui->pushButton_3, &QPushButton::clicked, [=](){
        int num1 = ui->spinBox_3_1->value();    //猪圈号
        int num2 = ui->spinBox_3_2->value();    //猪编号
        qDebug() << zhujuan[num1].pg.size();

        //考虑到超过size的情况
        if(num2 < zhujuan[num1].pg.size())
        {
            int t_color = zhujuan[num1].pg[num2]->getcolor();
            int t_weight = zhujuan[num1].pg[num2]->getweight();
            int t_raised_time = zhujuan[num1].pg[num2]->getraisedtime();
            if(t_color == 0)
                ui->lineEdit_3_1->setText("黑色");
            if(t_color == 1)
                ui->lineEdit_3_1->setText("小花猪");
            if(t_color == 2)
                ui->lineEdit_3_1->setText("大白花猪");

            ui->lineEdit_3_2->setText(QString::number(t_weight));
            ui->lineEdit_3_3->setText(QString::number(t_raised_time));
        }
        else
        {
            ui->lineEdit_3_1->setText("查无此猪");
            ui->lineEdit_3_2->setText("");
            ui->lineEdit_3_3->setText("");
        }

    });

    //记录猪圈信息
    connect(ui->save_button, &QPushButton::clicked, [=](){savefile();});


    //查询售卖历史
    connect(ui->sale_button, &QPushButton::clicked, [=](){
        Form_sales *f_sales = new Form_sales;
        f_sales->show();
    });

    //显示花色表格

    connect(ui->chart_button, &QPushButton::clicked, [=](){
        savefile();
        Form_chart *f_chart = new Form_chart;
        f_chart->show();

    });

    //显示猪的情况


    connect(ui->pig_button, &QPushButton::clicked, [=](){
        qDebug() << "著信息";
        Form_pig *f_pig = new Form_pig();
        f_pig->show();

    });

}

Widget::~Widget()
{
    delete ui;
}
