#ifndef UISTACK_H
#define UISTACK_H

#include <QWidget>


extern "C" {
    unsigned char* read_stack(const unsigned int pointer);
}


namespace Ui {
class uistack;
}

class uistack : public QWidget
{
    Q_OBJECT

public:
    explicit uistack(QWidget *parent = nullptr);
    ~uistack();

    void insert();

    void go();


private slots:
    void on_pushButton_released();

private:
    Ui::uistack *ui;
};

#endif // UISTACK_H
