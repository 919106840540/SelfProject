#include "form_pig.h"
#include "ui_form_pig.h"
#include<QDebug>
void Form_pig:: loadpig(){//读数据出现问题
    QFile pig_info("../raisingPigs/info/info_pig.txt");
    pig_info.open(QIODevice::ReadOnly);     //改进，移动光标？不要打开多次
    QString str = pig_info.readAll();
    pig_info.close();

    pig_info.open(QIODevice::ReadOnly);

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "体重" << "花色" << "编号" << "猪圈号" << " 饲养时间");
    QTextStream in(&pig_info);
    if(!str.isEmpty())//检测
    {
        int num_of_pigs = 0;
        in >> num_of_pigs;
        qDebug() << num_of_pigs << "loadpig";
        ui->tableWidget->setRowCount(num_of_pigs);
        for(int k = 0; k < num_of_pigs; k++)
        {
            QString t_weight;
            QString t_color, t_number, t_pighouse, t_raised_time;
            in >> t_weight >> t_color >> t_number >> t_pighouse >> t_raised_time;


            if(t_color == "0")
                ui->tableWidget->setItem(k, 1, new QTableWidgetItem("黑色"));
            if(t_color == "1")
                ui->tableWidget->setItem(k, 1, new QTableWidgetItem("大白花"));
            if(t_color == "2")
                ui->tableWidget->setItem(k, 1, new QTableWidgetItem("小花"));

            ui->tableWidget->setItem(k, 0, new QTableWidgetItem(t_weight));
            ui->tableWidget->setItem(k, 2, new QTableWidgetItem(t_number));
            ui->tableWidget->setItem(k, 3, new QTableWidgetItem(t_pighouse));
            ui->tableWidget->setItem(k, 4, new QTableWidgetItem(t_raised_time));

        }
    }
    pig_info.close();

}

Form_pig::Form_pig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_pig)
{
    ui->setupUi(this);
    this->resize(800, 700);
    this->setWindowTitle("猪的信息");
    loadpig();
    //关闭释放内存
    setAttribute(Qt::WA_DeleteOnClose);


}

Form_pig::~Form_pig()
{
    delete ui;
}
