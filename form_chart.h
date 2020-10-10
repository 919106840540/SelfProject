#ifndef FORM_CHART_H
#define FORM_CHART_H

#include <QWidget>

namespace Ui {
class Form_chart;
}

class Form_chart : public QWidget
{
    Q_OBJECT

public:
    explicit Form_chart(QWidget *parent = 0);
    ~Form_chart();

private:
    Ui::Form_chart *ui;
};

#endif // FORM_CHART_H
