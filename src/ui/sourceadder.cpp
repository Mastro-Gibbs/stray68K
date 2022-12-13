#include "sourceadder.h"
#include "objects/ui_sourceadder.h"
 #include <iostream>

SourceAdder::SourceAdder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SourceAdder)
{
    ui->setupUi(this);

    setWindowTitle("Source adder");

    show();
}

SourceAdder::~SourceAdder()
{
    delete ui;
}


void SourceAdder::accept()
{
    QString newSource;

    newSource = ui->sourceName->text().split('.').at(0);
    newSource.append(".X68");

    projectPath.append(newSource);

    QFile file(projectPath);
    file.open( QIODevice::WriteOnly );
    file.close();


    ProManager *proManager = ProManager::getInstance();
    proManager->setProFile( proPath );
    proManager->addSourceFile( newSource );

    QDialog::accept();

}
