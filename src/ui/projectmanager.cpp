#include "projectmanager.h"

#include <iostream>

ProjectManager::ProjectManager()
{}

ProjectManager::~ProjectManager(){}


ProjectManager *ProjectManager::getInstance()
{
    static ProjectManager instance;
    return &instance;
}


void ProjectManager::generateSkASMTree
                     ( QTreeWidget *parent, QString s68kPath )
{
    parent->clear();

    parent->setIconSize( QSize( 20, 20 ) );
    parent->setFont( QFont( "Ubuntu Mono" ) );

    QPixmap project  ( ":/icons/img/open.png" );
    QPixmap fileicon( ":/icons/img/file.png" );
    QPixmap s68kicon( ":/icons/img/s68k.png" );
    QPixmap binicon( ":/icons/img/B68.png" );

    ProManager *proManager = ProManager::getInstance();
    proManager->setProFile( s68kPath );

    QString sourcePath = elaboratePath( s68kPath );

    QString projectName  = proManager->proData( ProManager::Name );
    QString mainFileName = proManager->proData( ProManager::Main );
    QVector<QString> sources  = proManager->sourcesToQStringVector();
    QVector<QString> binary  = proManager->binaryToQStringVector();

    QString mainSourcePath( sourcePath);
    mainSourcePath.append ( mainFileName );

    QTreeWidgetItem *projectFolder = new QTreeWidgetItem;
    QTreeWidgetItem *s68kFile     = new QTreeWidgetItem;
    QTreeWidgetItem *sourcesFolder = new QTreeWidgetItem;
    QTreeWidgetItem *binaryFolder = new QTreeWidgetItem;
    QTreeWidgetItem *mainFile      = new QTreeWidgetItem;

    ProjectTreeItem *s68k    = new ProjectTreeItem( nullptr, s68kPath );
    ProjectTreeItem *mainItem = new ProjectTreeItem( nullptr, mainSourcePath );
    ProjectTreeItem *srcItem  = new ProjectTreeItem( nullptr, QString() );
    ProjectTreeItem *binItem  = new ProjectTreeItem( nullptr, QString() );

    mainItem->setText     ( mainFileName );
    s68k->setText        ( projectName + ".s68k" );
    srcItem->setText      ( "Sources");
    binItem->setText      ( "Binary");
    projectFolder->setText( 0, projectName );

    projectFolder->setIcon( 0, project );
    sourcesFolder->setIcon( 0, project );
    binaryFolder->setIcon( 0, project );
    mainFile->setIcon     ( 0, fileicon );
    s68kFile->setIcon    ( 0, s68kicon );

    projectFolder->addChild( s68kFile );
    projectFolder->addChild( sourcesFolder );
    projectFolder->addChild( binaryFolder );
    sourcesFolder->addChild( mainFile );

    QFont font = projectFolder->font( 0 );
    font.setBold( true );
    font.setPointSize( 12 );
    projectFolder->setFont( 0, font );
    font.setPointSize( 11 );
    srcItem->setFont( font );
    binItem->setFont( font );

    parent->addTopLevelItem( projectFolder );
    parent->expandItem     ( projectFolder );
    parent->setItemWidget  ( s68kFile,     0, s68k );
    parent->setItemWidget  ( mainFile,      0, mainItem );
    parent->setItemWidget  ( sourcesFolder, 0, srcItem );
    parent->setItemWidget  ( binaryFolder, 0, binItem );

    mainPath = mainItem->getPath();

    foreach ( QString sourceFileString, sources )
    {
        QString localSourcePath( sourcePath );
        localSourcePath.append ( sourceFileString );

        QTreeWidgetItem *sourceFile = new QTreeWidgetItem;
        ProjectTreeItem *sourceItem = new ProjectTreeItem( nullptr, localSourcePath );
        sourceItem->setText    ( sourceFileString );
        sourceFile->setIcon    ( 0, fileicon );
        sourceItem->setIconSize( QSize( 20, 20 ) );
        sourcesFolder->addChild( sourceFile );
        parent->setItemWidget  ( sourceFile, 0, sourceItem );

        connect( sourceItem, &ProjectTreeItem::leftClicked,   this, [=](){ ProjectManager::open( sourceItem->getPath() ); });
        connect( sourceItem, &ProjectTreeItem::rightClicked,  this, [=](){ ProjectManager::generatePopupMenu( sourceItem, sourceItem->getPath(), Source ); });
    }

    foreach ( QString binaryFileString, binary )
    {
        QString localSourcePath( sourcePath );
        localSourcePath.append ( binaryFileString );

        QTreeWidgetItem *sourceFile = new QTreeWidgetItem;
        ProjectTreeItem *sourceItem = new ProjectTreeItem( nullptr, localSourcePath );
        sourceItem->setText    ( binaryFileString );
        sourceFile->setIcon    ( 0, binicon );
        sourceItem->setIconSize( QSize( 20, 20 ) );
        binaryFolder->addChild( sourceFile );
        parent->setItemWidget  ( sourceFile, 0, sourceItem );

        connect( sourceItem, &ProjectTreeItem::rightClicked,  this, [=](){ ProjectManager::generatePopupMenu( sourceItem, sourceItem->getPath(), Binary ); });
    }

    connect( s68k,    &ProjectTreeItem::leftClicked,  this, [=](){ ProjectManager::open( s68k->getPath() ); });
    connect( mainItem, &ProjectTreeItem::leftClicked,  this, [=](){ ProjectManager::open( mainItem->getPath() ); });

    connect( mainItem, &ProjectTreeItem::rightClicked,  this, [=](){ ProjectManager::generatePopupMenu( mainItem, mainItem->getPath(), Source ); });
    connect( srcItem,  &ProjectTreeItem::rightClicked,  this, [=](){ ProjectManager::generatePopupMenu( srcItem, srcItem->getPath(), Folder ); });

    sourcesFolder->setExpanded( true );
    binaryFolder->setExpanded( true );

    emit generatingFinished();
}

QString ProjectManager::elaboratePath( QString s68kPath )
{
    int lio = s68kPath.lastIndexOf('/') + 1;
    s68kPath.remove( lio, s68kPath.length() );
    return s68kPath;
}


void ProjectManager::addSrc( QTreeWidget *parent, QString proPath )
{
    int lio = proPath.lastIndexOf("/") + 1;
    QString projectPath( proPath );
    projectPath.remove(lio, proPath.length());

    if ( adder != nullptr )
    {
        adder->deleteLater();
        adder = nullptr;
    }

    adder = new SourceAdder;
    adder->setProjectPath( projectPath );
    adder->setProPath( proPath );

    connect( adder, &SourceAdder::accepted, this, [=]{ generateSkASMTree(parent, proPath); } );
   // connect( this, &ProjectManager::generatingFinished, [=] { ProjectManager::deleteObj(adder); } );
}


void ProjectManager::deleteSrc( QTreeWidget *parent, QVector<QString> params )
{
    QString proPath  = params[0];
    QString filePath = params[1];
    QString fileName = params[2];

    if ( fileOptions != nullptr )   // forced to kill obj here :
    {                               // if remove it and kill obj with commented connection below
        fileOptions->deleteLater(); // app will crash, maybe bcs deley from calling slot-signal it's too
        fileOptions = nullptr;      // slow compared to this connecton
    }

    fileOptions = new FileOptions;
    fileOptions->deleteMode( proPath, filePath, fileName );

    connect( fileOptions, &QDialog::accepted, this, [=]{ generateSkASMTree(parent, proPath); } );

    //connect( this, &ProjectManager::generatingFinished, [=] { ProjectManager::deleteObj(fileOptions); } );

}


void ProjectManager::renameSrc( QTreeWidget *parent, QVector<QString> params )
{
    QString proPath  = params[0];
    QString filePath = params[1];
    QString fileName = params[2];

    if ( fileOptions != nullptr )   // forced to kill obj here :
    {                               // if remove it and kill obj with commented connection below
        fileOptions->deleteLater(); // app will crash, maybe bcs deley from calling slot-signal it's too
        fileOptions = nullptr;      // slow compared to this connecton
    }

    fileOptions = new FileOptions;
    fileOptions->renameMode( proPath, filePath, fileName );

    connect( fileOptions, &QDialog::accepted, this, [=]{ generateSkASMTree(parent, proPath); } );
    connect( fileOptions, SIGNAL(newName(QString,QString)), this, SLOT(renamed(QString,QString)) );

    //connect( this, &ProjectManager::generatingFinished, [=] { ProjectManager::deleteObj(fileOptions); } );

}

