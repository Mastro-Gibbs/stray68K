#include "fileoptions.h"
#include "objects/ui_fileoptions.h"

#include <QDebug>

FileOptions::FileOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileOptions)
{
    ui->setupUi(this);

    ui->titleLabel->setAlignment( Qt::AlignCenter );

    QFont font = ui->titleLabel->font();
    font.setBold( true );
    font.setPointSize( 14 );

    ui->titleLabel->setFont( font );

}

FileOptions::~FileOptions()
{
    delete ui;
}



void FileOptions::deleteMode( QString proPath, QString path, QString fileName )
{
    fileData.pathParam = path;
    fileData.proPath   = proPath;
    fileData.fileName  = fileName;

    ui->titleLabel->setText( "Delete file" );

    ui->fileInfo->setText( path );

    ui->fileInfoLabel->setText( "Deleting this file al location:" );

    permDeletingCheckBox = new QCheckBox( this );

    permDeletingCheckBox->setText( "Delete file permanently" );

    ui->verticalLayout->insertWidget( 5, permDeletingCheckBox );

    opt = Delete;

    show();
}


void FileOptions::renameMode( QString proPath, QString path, QString oldName )
{
    fileData.pathParam = path;
    fileData.proPath   = proPath;
    fileData.fileName  = oldName;

    ui->titleLabel->setText( "Rename file" );

    ui->fileInfo->setText( oldName );

    ui->fileInfoLabel->setText( "Old file name:" );

    QLabel *newFileNameLabel = new QLabel( "New file name:" );

    ui->verticalLayout->insertWidget( 5, newFileNameLabel );

    newFileName = new QLineEdit( this );

    ui->verticalLayout->insertWidget( 6, newFileName );

    opt = Rename;

    show();
}


void FileOptions::accept()
{
    QFile file( fileData.pathParam );

    ProManager *proManager = ProManager::getInstance();
    proManager->setProFile( fileData.proPath );

    if ( opt ) //true = delete
    {
        proManager->removeSourceFile( fileData.fileName );

        if ( permDeletingCheckBox->isChecked() )
            file.remove();

    }
    else       //false = rename
    {
        QString extension ( fileData.pathParam );

        int lio = extension.lastIndexOf( "." ) + 1;
        extension.remove( 0, lio );

        QString newFilePath ( fileData.pathParam );
        lio = newFilePath.lastIndexOf( "/" ) + 1;
        newFilePath.remove( lio, newFilePath.length() );

        QString newFileNameString ( newFileName->text() );
        if ( (lio = newFileNameString.lastIndexOf( "." )) != -1 )
        {
             newFileNameString.remove( lio, newFileNameString.length() );
        }
        newFileNameString.append( "." );
        newFileNameString.append(  extension );
        newFilePath.append( newFileNameString );

        if ( file.rename( newFilePath ) )
        {
            proManager->removeSourceFile( fileData.fileName );
            proManager->addSourceFile( newFileNameString );
            emit newName(fileData.fileName, newFileNameString);
        }
    }
    QDialog::accept();
}
