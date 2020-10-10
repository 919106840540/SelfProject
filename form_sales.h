#ifndef FORM_SALES_H
#define FORM_SALES_H

#include <QWidget>

namespace Ui {
class Form_sales;
}

class Form_sales : public QWidget
{
    Q_OBJECT

public:
    explicit Form_sales(QWidget *parent = 0);
    void load_sales();
    ~Form_sales();

private:
    Ui::Form_sales *ui;
};

#endif // FORM_SALES_H
