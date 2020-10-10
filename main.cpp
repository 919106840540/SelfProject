#include "widget.h"
#include <QApplication>
#include<pig.h>
#include<pighouse.h>
#include"form_sales.h"
#include<widget.h>
Form_pig *f_pig;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    f_pig = new Form_pig();
    f_pig->show();


    return a.exec();
}
