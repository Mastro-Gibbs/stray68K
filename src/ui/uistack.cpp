#include "uistack.h"
#include "ui_uistack.h"

uistack::uistack(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uistack)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);
    setWindowTitle("Stack");

    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    ui->tableWidget_2->setEditTriggers(QTableWidget::NoEditTriggers);

    QHeaderView* header = ui->tableWidget_2->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    QRegExp rx("[0-9a-fA-F]{8}");
    ui->lineEdit->setValidator(new QRegExpValidator(rx, this));

    ui->label->setStyleSheet("QLabel { color : rgb(244, 120, 120); }");
    ui->label_2->setStyleSheet("QLabel { color : rgb(255, 255, 142); }");
}

uistack::~uistack()
{
    delete ui;
}

QString fixed4BReg2_1(QString v)
{
    int max = 8;
    int delta = max - v.size();

    for (int i = 0; i < delta; ++i)
        v.prepend('0');

    return v.toUpper();
}

QString fixed2BReg2_1(QString v)
{
    int max = 2;
    int delta = max - v.size();

    for (int i = 0; i < delta; ++i)
        v.prepend('0');

    return v.toUpper();
}

void uistack::insert()
{
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->verticalHeader()->hide();

    ui->lineEdit->setText("00FFFFFC");

    for (int i = 9, j = 0; i >= 0 ; j++, i--)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        QFont font = QFont();
        font.setFamily("Noto Sans Mono");
        font.setPointSize(11);
        item->setFont(font);
        item->setForeground(QBrush(QColor(255, 255, 142), Qt::SolidPattern));
        item->setText(fixed4BReg2_1(QString::number((16777212-(j*0x4)), 16)));
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        ui->tableWidget->setItem(i, 0, item);
    }

    ui->tableWidget_2->setRowCount(10);
    ui->tableWidget_2->verticalHeader()->hide();

    for (int i = 9; i >= 0 ; i--)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        QFont font = QFont();
        font.setFamily("Noto Sans Mono");
        font.setPointSize(11);
        item->setFont(font);
        item->setText("00 00 00 00");
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        ui->tableWidget_2->setItem(i, 0, item);
    }


}


void uistack::go()
{
    on_pushButton_released();
}


void uistack::on_pushButton_released()
{
    ui->label->setText("");

    QString svalue = ui->lineEdit->text();
    unsigned int value = svalue.toInt(nullptr, 16);

    if (value > 0xFFFFFC)
    {
        ui->label->setText("Invalid address\ntoo large address");
        return;
    }

    if ((value % 4) == 0)
    {
        for (int i = 9, j = 0; i >= 0 ; j++, i--)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            QFont font = QFont();
            font.setFamily("Noto Sans Mono");
            font.setPointSize(11);
            item->setFont(font);
            item->setForeground(QBrush(QColor(255, 255, 142), Qt::SolidPattern));
            item->setText(fixed4BReg2_1(QString::number((value-(j*0x4)), 16)));
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
            ui->tableWidget->setItem(i, 0, item);
        }

        ui->lineEdit->setText(fixed4BReg2_1(svalue));

        unsigned char* raw_ram = read_stack(value);

        for (unsigned long j = 0, z = 0; j < 10; j++, z+=4)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            QFont font = item->font();
            font.setPointSize(13);
            item->setFont(font);
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);

            for (int i = 0; i < 4; i++)
            {
                QString byte = QString::number(raw_ram[z+i], 16);
                byte = fixed2BReg2_1(byte);
                item->setText(item->text() + byte + " ");

            }
            ui->tableWidget_2->setItem(j, 0, item);
        }

        free(raw_ram);
    }
    else
        ui->label->setText("Invalid address\npass a multiple of 0x04");

}

