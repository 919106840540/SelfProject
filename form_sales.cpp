#include "form_sales.h"
#include "ui_form_sales.h"
#include<QTextStream>
#include<QFile>
void Form_sales::load_sales()
{
    QFile out_info("../raisingPigs/info/out_info.txt");
    out_info.open(QIODevice::ReadOnly);     //改进，移动光标？不要打开多次
    QString str = out_info.readAll();
    out_info.close();

    out_info.open(QIODevice::ReadOnly);
    QTextStream in(&out_info);
    int lines = 0;
    while(!out_info.atEnd())
    {
        out_info.readLine();
        lines++;
    }
    out_info.close();
    out_info.open(QIODevice::ReadOnly);

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "出栏时间" << "售价");

    if(! str.isEmpty())//检测
    {
        ui->tableWidget->setRowCount(lines);
        for(int k = 0; k < lines; k++)
        {
            QString time, sales;
            in >> time >> sales;
            ui->tableWidget->setItem(k, 0, new QTableWidgetItem(time));
            ui->tableWidget->setItem(k, 1, new QTableWidgetItem(sales));
        }
    }
    out_info.close();
}
Form_sales::Form_sales(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_sales)
{
    ui->setupUi(this);
    load_sales();
    this->setWindowTitle("售出信息");
}

Form_sales::~Form_sales()
{
    delete ui;
}
