#include "form_chart.h"
#include "ui_form_chart.h"
#include<QtCharts>
#include"pig.h"
#include"pighouse.h"
#include<QFile>
using namespace QtCharts;

Form_chart::Form_chart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_chart)
{
    ui->setupUi(this);
    this->setWindowTitle("分布图");
    pigHouse* zhujuan= new pigHouse[100];
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




    QChart *m_chart = new QChart();
    //创建3个条线数据
    QBarSet *set0 = new QBarSet("数量");
    QBarSet *set1 = new QBarSet("重量");
    QBarSet *set2 = new QBarSet("饲养总时间");

    //三个花色的数据

    int n_bai = 0, n_hua = 0, n_hei = 0;
    double w_bai = 0, w_hua = 0, w_hei = 0;
    int r_bai = 0, r_hua = 0, r_hei = 0;

    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < zhujuan[i].pg.size(); j++)
        {
            if(zhujuan[i].pg[j]->getcolor() == 0)
            {
                n_hei ++;
                w_hei += zhujuan[i].pg[j]->getweight();
                r_hei += zhujuan[i].pg[j]->getraisedtime();
            }

            if(zhujuan[i].pg[j]->getcolor() == 1)
            {
                n_hua ++;
                w_hua += zhujuan[i].pg[j]->getweight();
                r_hua += zhujuan[i].pg[j]->getraisedtime();
            }

            if(zhujuan[i].pg[j]->getcolor() == 2)
            {
                n_bai ++;
                w_bai += zhujuan[i].pg[j]->getweight();
                r_bai += zhujuan[i].pg[j]->getraisedtime();
            }
        }
    }

    *set0 << n_bai << n_hua << n_hei;
    *set1 << w_bai << w_hua << w_hei;
    *set2 << r_bai << r_hua << r_hei;

    set0->setLabelColor(QColor(0,0,255));
    set1->setLabelColor(QColor(0,0,255));
    set2->setLabelColor(QColor(0,0,255));

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->setVisible(true);
    series->setLabelsVisible(true);

    m_chart->setTheme(QChart::ChartThemeLight);//设置白色主题
    m_chart->setDropShadowEnabled(true);//背景阴影
    m_chart->addSeries(series);//添加系列到QChart上

    m_chart->setTitleBrush(QBrush(QColor(0,0,255)));//设置标题Brush
    m_chart->setTitleFont(QFont("微软雅黑"));//设置标题字体
    m_chart->setTitle("不同品种猪的数量和体重、饲养时间分布图");

    //创建X轴和Y轴
    QBarCategoryAxis *axisX = new QBarCategoryAxis;
    axisX->append("黑猪");
    axisX->append("小白花猪");
    axisX->append("大白花猪");

    axisX->setLabelsColor(QColor(7,28,96));

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0,1000);   //改为setRange(0,1);则表示坐标为动态计算大小的
    //axisY->setTitleText("价格");
    //axisY->setLabelFormat("%d$");

    m_chart->setAxisX(axisX,series);
    m_chart->setAxisY(axisY,series);

    //修改说明样式
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
    m_chart->legend()->setBackgroundVisible(true);//设置背景是否可视
    m_chart->legend()->setAutoFillBackground(true);//设置背景自动填充
    m_chart->legend()->setColor(QColor(222,233,251));//设置颜色
    m_chart->legend()->setLabelColor(QColor(0,100,255));//设置标签颜色
    m_chart->legend()->setMaximumHeight(50);

    QChartView *chartView = new QChartView(m_chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *pVLayout = new QVBoxLayout(this);
    pVLayout->addWidget(chartView);
    resize(960, 720);
}

Form_chart::~Form_chart()
{
    delete ui;
}
