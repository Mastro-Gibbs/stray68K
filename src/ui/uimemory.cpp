#include "uimemory.h"
#include "ui_uimemory.h"



uimemory::uimemory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uimemory)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);
    setWindowTitle("Memory");

    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    ui->tableWidget_2->setEditTriggers(QTableWidget::NoEditTriggers);

    QHeaderView* header = ui->tableWidget_2->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    QRegExp rx("[0-9a-fA-F]{8}");
    ui->lineEdit->setValidator(new QRegExpValidator(rx, this));

    ui->label->setStyleSheet("QLabel { color : rgb(244, 120, 120); }");
    ui->label_2->setStyleSheet("QLabel { color : rgb(255, 255, 142); }");
}

uimemory::~uimemory()
{
    delete ui;
}

QString fixed4BReg2(QString v)
{
    int max = 8;
    int delta = max - v.size();

    for (int i = 0; i < delta; ++i)
        v.prepend('0');

    return v.toUpper();
}

QString fixed2BReg2(QString v)
{
    int max = 2;
    int delta = max - v.size();

    for (int i = 0; i < delta; ++i)
        v.prepend('0');

    return v.toUpper();
}

void uimemory::insert()
{
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->verticalHeader()->hide();

    ui->lineEdit->setText("00001000");

    for (int i = 0; i < 10; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        QFont font = QFont();
        font.setFamily("Noto Sans Mono");
        font.setPointSize(11);
        item->setFont(font);
        item->setForeground(QBrush(QColor(255, 255, 142), Qt::SolidPattern));
        item->setText(fixed4BReg2(QString::number((4096+(i*0x10)), 16)));
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        ui->tableWidget->setItem(i, 0, item);
    }

    ui->tableWidget_2->setRowCount(10);
    ui->tableWidget_2->verticalHeader()->hide();

    for (int i = 0; i < 10; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        QFont font = QFont();
        font.setFamily("Noto Sans Mono");
        font.setPointSize(11);
        item->setFont(font);
        item->setText("00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00");
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        ui->tableWidget_2->setItem(i, 0, item);
    }


}


void uimemory::disable_go_btn()
{
    ui->pushButton->setDisabled(true);
}

void uimemory::enable_go_btn()
{
    ui->pushButton->setDisabled(false);
}


void uimemory::go()
{
    on_pushButton_released();
}


void uimemory::on_pushButton_released()
{
    ui->label->setText("");

    QString svalue = ui->lineEdit->text();
    int value = svalue.toInt(nullptr, 16);

    if ((value + 0x100) > 0x1000000)
    {
        ui->label->setText("Invalid address: too large address");
        return;
    }

    if ((value - 0x100) < 0)
    {
        ui->label->setText("Invalid address: too small address");
        return;
    }

    if ((value % 16) == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            QFont font = QFont();
            font.setFamily("Noto Sans Mono");
            font.setPointSize(11);
            item->setFont(font);
            item->setForeground(QBrush(QColor(255, 255, 142), Qt::SolidPattern));
            item->setText(fixed4BReg2(QString::number((value+(i*0x10)), 16)));
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
            ui->tableWidget->setItem(i, 0, item);
        }

        ui->lineEdit->setText(fixed4BReg2(svalue));

        unsigned char* raw_ram = read_chunk(value, 0x100);

        for (unsigned long j = 0, z = 0; j < 10; j++, z+=16)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            QFont font = item->font();
            font.setPointSize(13);
            item->setFont(font);
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);

            for (int i = 0; i < 16; i++)
            {
                QString byte = QString::number(raw_ram[z+i], 16);
                byte = fixed2BReg2(byte);
                item->setText(item->text() + byte + " ");

            }
            ui->tableWidget_2->setItem(j, 0, item);
        }

        free(raw_ram);
    }
    else
        ui->label->setText("Invalid address: pass a multiple of 0x10");

}


void uimemory::on_nextbtn_released()
{
    ui->label->setText("");

    QString svalue = ui->lineEdit->text();
    int value = svalue.toInt(nullptr, 16);

    if ((value + 0x100) > 0x1000000)
    {
        ui->label->setText("Invalid address: too large address");
        return;
    }

    value += 0x100;

    if ((value % 16) == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            QFont font = QFont();
            font.setFamily("Noto Sans Mono");
            font.setPointSize(11);
            item->setFont(font);
            item->setForeground(QBrush(QColor(255, 255, 142), Qt::SolidPattern));
            item->setText(fixed4BReg2(QString::number((value+(i*0x10)), 16)));
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
            ui->tableWidget->setItem(i, 0, item);
        }

        ui->lineEdit->setText(fixed4BReg2(QString::number(value, 16)));

        unsigned char* raw_ram = read_chunk(value, 0x100);

        for (unsigned long j = 0, z = 0; j < 10; j++, z+=16)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            QFont font = item->font();
            font.setPointSize(13);
            item->setFont(font);
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);

            for (int i = 0; i < 16; i++)
            {
                QString byte = QString::number(raw_ram[z+i], 16);
                byte = fixed2BReg2(byte);
                item->setText(item->text() + byte + " ");

            }
            ui->tableWidget_2->setItem(j, 0, item);
        }

        free(raw_ram);
    }
    else
        ui->label->setText("Invalid address: pass a multiple of 0x10");
}


void uimemory::on_prevbtn_released()
{
    ui->label->setText("");

    QString svalue = ui->lineEdit->text();
    int value = svalue.toInt(nullptr, 16);

    if ((value - 0x100) < 0)
    {
        ui->label->setText("Invalid address: too small address");
        return;
    }

    value -= 0x100;

    if ((value % 16) == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            QFont font = QFont();
            font.setFamily("Noto Sans Mono");
            font.setPointSize(11);
            item->setFont(font);
            item->setForeground(QBrush(QColor(255, 255, 142), Qt::SolidPattern));
            item->setText(fixed4BReg2(QString::number((value+(i*0x10)), 16)));
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
            ui->tableWidget->setItem(i, 0, item);
        }

        ui->lineEdit->setText(fixed4BReg2(QString::number(value, 16)));

        unsigned char* raw_ram = read_chunk(value, 0x100);

        for (unsigned long j = 0, z = 0; j < 10; j++, z+=16)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            QFont font = item->font();
            font.setPointSize(13);
            item->setFont(font);
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);

            for (int i = 0; i < 16; i++)
            {
                QString byte = QString::number(raw_ram[z+i], 16);
                byte = fixed2BReg2(byte);
                item->setText(item->text() + byte + " ");

            }
            ui->tableWidget_2->setItem(j, 0, item);
        }

        free(raw_ram);
    }
    else
        ui->label->setText("Invalid address: pass a multiple of 0x10");
}

