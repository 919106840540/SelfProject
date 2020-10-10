#ifndef FORM_PIG_H
#define FORM_PIG_H
#include<QFile>
#include<QTextStream>
#include <QWidget>
#include<QString>

namespace Ui {
class Form_pig;
}

class Form_pig : public QWidget
{
    Q_OBJECT

public:
    explicit Form_pig(QWidget *parent = 0);
    ~Form_pig();
    void loadpig();
private:
    Ui::Form_pig *ui;
};

#endif // FORM_PIG_H
