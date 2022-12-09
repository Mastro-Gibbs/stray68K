#ifndef UIMEMORY_H
#define UIMEMORY_H

#include <QWidget>
#include <QDebug>


extern "C" {
    unsigned char* read_chunk(const unsigned int pointer, const unsigned int end);
}


namespace Ui {
class uimemory;
}

class uimemory : public QWidget
{
    Q_OBJECT

public:
    explicit uimemory(QWidget *parent = nullptr);
    ~uimemory();

    void insert();

    void go();


private slots:
    void on_pushButton_released();

private:
    Ui::uimemory *ui;
};

#endif // UIMEMORY_H
