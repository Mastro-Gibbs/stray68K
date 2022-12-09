#include "axolotlApp.h"
#include "ui_axolotlApp.h"

#include <iostream>

int block_num;
int pc;

AxolotlApp::AxolotlApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AxolotlApp)
{
    ui->setupUi(this);
}


AxolotlApp::~AxolotlApp()
{
    delete ui;
}




//#################################### START PUBLIC METHODS ##################################


void AxolotlApp::dynamicBinding()
{

    connect(ui->hideBtn, &QPushButton::clicked, this, &AxolotlApp::on_actionProgram_output_frame_triggered);

    connect( this, &AxolotlApp::projectOpened, [=] { AxolotlApp::disableRunProject(false); } );
    connect( this, &AxolotlApp::projectClosed, [=] { AxolotlApp::disableRunProject(true); }  );

    connect( ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(disableEditorActions(int)) );

    connect( ui->output, &QPlainTextEdit::textChanged, this, &AxolotlApp::to_bottom);

}


void AxolotlApp::init()
{
    run_mode = false;

    ui->tabWidget->setTabsClosable( true );
    ui->tabWidget->setMovable( true );

    ui->actionRun_project->setDisabled( true );
    ui->actionRun->setDisabled( true );

    ui->actionSave->setDisabled          ( true );
    ui->actionSave_as->setDisabled       ( true );
    ui->actionClose_all_tabs->setDisabled( true );
    ui->actionCurrent_editor_zoom_in->setDisabled ( true );
    ui->actionCurrent_editor_zoom_out->setDisabled( true );

    ui->actionMemory->setDisabled( true );

    ui->sbs->hide();

    ConfigManager *conf = ConfigManager::getInstance();

    QJsonObject obj = conf->consoleAspect();
    if (obj.value("status").toInt() == 1)
    {
        ui->outputFrame->show();
        ui->outputFrame->setMinimumHeight(1);
        QJsonArray data = obj.value("ratio").toArray();
        ui->splitter_3->setStretchFactor(0, 5);
        ui->actionProgram_output_frame->setText("Hide program output frame");
    }
    else
    {
        ui->outputFrame->hide();
        ui->outputFrame->setMinimumHeight(0);
        ui->actionProgram_output_frame->setText("Show program output frame");
    }

    obj = conf->projectAspect();
    if (obj.value("status").toInt() == 1)
    {
        ui->treeWidget->show();
        ui->treeWidget->setMinimumHeight(1);

        QJsonArray data = obj.value("ratio").toArray();
        ui->splitter->setStretchFactor( data[0].toInt(), data[1].toInt() );
    }
    else
    {
        ui->treeWidget->hide();
        ui->treeWidget->setMinimumHeight(0);
    }


    ui->pushButton_4->setDisabled(true);
    ui->pushButton->setDisabled(true);

    //Init struct who contain project infos
    projectData.projectOpened = false;
    projectData.s68kPath      = QString();
    projectData.mainPath      = QString();
    projectData.projectPath   = QString();


    //Set highlighter and font for pseudo-console, connect his hideBtn
    syntaxHighlighter = new OutputHighlighter;
    syntaxHighlighter->setHiglightFormat();
    syntaxHighlighter->setDocument( ui->output->document() );

    ConfigManager *configManager = ConfigManager::getInstance();
    QFont outputFont ( configManager->consoleFont() );
    outputFont.setPointSize( configManager->consoleFontSize() );
    ui->output->setFont( outputFont );

    findInexistentRecentPath( RECENT_FILES_PATH );
    findInexistentRecentPath( RECENT_PROJECTS_PATH );
    recent( RECENT_FILES_PATH );
    recent( RECENT_PROJECTS_PATH );

}//end init method


void AxolotlApp::setIcons()
{    
    QPixmap folder(":/icons/img/folder.png");
    QPixmap close(":/icons/img/close.png");
    QPixmap newfile(":/icons/img/newfile.png");
    QPixmap fileicon(":/icons/img/fileicon.png");
    QPixmap run(":/icons/img/run.png");
    QPixmap save(":/icons/img/save.png");
    QPixmap zoomin (":/icons/img/zoomin.png");
    QPixmap zoomout(":/icons/img/zoomout.png");
    QPixmap force(":/icons/img/red_x.png");
    QPixmap project(":/icons/img/project.png");
    QPixmap newproj(":/icons/img/newproj.png");
    QPixmap settings(":/icons/img/settings.png");

    ui->menuFileMode->setIcon(fileicon);
    ui->actionNewFile->setIcon(newfile);
    ui->actionOpenFile->setIcon(folder);
    ui->menuProjectMode->setIcon(project);
    ui->actionSave->setIcon(save);
    ui->actionSave_as->setIcon(save);
    ui->actionClose_all_tabs->setIcon(close);
    ui->actionForce_quit->setIcon(force);
    ui->actionCurrent_editor_zoom_in->setIcon(zoomin);
    ui->actionCurrent_editor_zoom_out->setIcon(zoomout);
    ui->actionRun->setIcon(run);
    ui->actionRun_project->setIcon(run);
    ui->actionCloseProject->setIcon(close);
    ui->actionOpenProject->setIcon(folder);
    ui->actionNewProject->setIcon(newproj);
    ui->actionSettings->setIcon(settings);
}


void AxolotlApp::setTheme()
{
    ThemeSetter *themeSetter = ThemeSetter::getInstance();
    themeSetter->setConfig();
    themeSetter->setStyle();

    this->setStyleSheet          ( themeSetter->getMainbg() );
    ui->treeWidget->setStyleSheet( themeSetter->getTreeWidget() );
    ui->tabWidget->setStyleSheet ( themeSetter->getEditor() );

    themeSetter->setOutputFrameStyle();

    QVector<QJsonValue> outputStyle = themeSetter->getOutputFrame();

    ui->hideBtn->setStyleSheet ( outputStyle[0].toString() );
    ui->cleanBtn->setStyleSheet( outputStyle[0].toString() );
    ui->stopBtn->setStyleSheet ( outputStyle[0].toString() );
    ui->output->setStyleSheet  ( outputStyle[1].toString() );
}//end setTheme method



//#################################### END PUBLIC METHODS ##################################















//#################################### START PRIVATE METHODS ################################




void AxolotlApp::findInexistentRecentPath( const QString &path_to_file )
{
    QVector<QString> filespath;

    QFile file( path_to_file );
    if ( file.open( QIODevice::ReadOnly ) )
    {
       QTextStream in( &file );
       int i = 0;
       while ( !in.atEnd() && i < 7 )
       {
           filespath << in.readLine();
           i++;
       }
       file.close();
    }

    foreach ( QString filePath, filespath )
    {
        QFile localFile(filePath);
        if ( !localFile.exists() )
        {
            filespath.removeOne(filePath);
        }
    }

    if ( file.open(QIODevice::WriteOnly) )
    {
        while( filespath.length() != 0 )
        {
            file.write( filespath.front().toUtf8() );
            file.write( "\n" );
            filespath.removeFirst();
        }
        file.close();
    }
}



/**
 * Get recent (max 7)
 */
void AxolotlApp::recent( const QString &path_to_file )
{
    if ( path_to_file == RECENT_FILES_PATH )
        ui->menuRecent_files->clear();
    else
        ui->menuRecent_projects->clear();

    QFile inputFile( path_to_file );
    int i = 0;

    if ( inputFile.open( QIODevice::ReadOnly ) )
    {
        QTextStream in( &inputFile );

        while ( !in.atEnd() && i < 7 )
        {
            QString line = in.readLine();
            i++;
            QAction *recent = new QAction( QString::number( i ) + " | " + line );

            if ( path_to_file == RECENT_FILES_PATH )
            {
                ui->menuRecent_files->addAction   ( recent );
                connect( recent, &QAction::triggered, this, [=]{ AxolotlApp::openFile( line ); } );
            }
            else
            {
                ui->menuRecent_projects->addAction( recent );
                connect( recent, &QAction::triggered, this, [=]{ AxolotlApp::openProject( line ); } );
            }
        }
        inputFile.close();
    }

    if ( i )
    {
        QAction *clearRecent = new QAction( "Clear" );
        connect( clearRecent, &QAction::triggered, this, [=]{ AxolotlApp::clearRecent( path_to_file ); } );

        if ( path_to_file == RECENT_FILES_PATH )
        {
            ui->menuRecent_files->addAction( clearRecent );
            ui->menuRecent_files->addSeparator();
        }
        else
        {
            ui->menuRecent_projects->addAction( clearRecent );
            ui->menuRecent_projects->addSeparator();
        }
    }
    else
    {
        if ( path_to_file == RECENT_FILES_PATH )
            ui->menuRecent_files->addAction( new QAction( "No recents.." ) );
        else
            ui->menuRecent_projects->addAction( new QAction( "No recents.." ) );
    }

}


/**
 * Write recent (max 7 item)
 */
void AxolotlApp::setRecent( const QString &path_to_file, QString filepath )
{
    QStringList filespath;
    QFile file( path_to_file );

    if ( file.open( QIODevice::ReadOnly ) )
    {
       QTextStream in( &file );
       int i = 0;
       while ( !in.atEnd() && i < 7 )
       {
           filespath << in.readLine();
           i++;
       }
       file.close();
    }

    if ( !filespath.contains( filepath ) )
        filespath.insert(0, filepath);
    else
        return;

    if ( filespath.size() > 7 ) filespath.removeLast();

    clearRecent( path_to_file );

    if ( file.open(QIODevice::WriteOnly) )
    {
        while( filespath.length() != 0 )
        {
            file.write( filespath.front().toUtf8() );
            file.write( "\n" );
            filespath.removeFirst();
        }
        file.close();
    }
    recent( path_to_file );
}


/**
 * Clean recent data
 */
void AxolotlApp::clearRecent( const QString &path_to_file )
{
    QFile file( path_to_file );

    if ( file.open( QIODevice::WriteOnly ) )
    {
        file.write( "" );
        file.close();
        recent( path_to_file );
    }
}



//#################################### END PRIVATE METHODS ################################














//#################################### START PROGRAMMER DEFINED SLOTS ################################


void AxolotlApp::initTheme()
{
    setTheme();
}

void AxolotlApp::openFile( QString path )
{
    QString fname( path );

    if ( path.compare( "" ) != 0 )
    { 
        int lio = path.lastIndexOf( "/" ) + 1;
        fname.remove( 0, lio );

        if ( !openedFileMap.contains( fname ) )
        {
            QFile *f = new QFile( path );
            f->open(QIODevice::ReadOnly);
            QByteArray data = f->readAll();

            Editor *editor = new Editor ( ui->tabWidget );
            ConfigManager *manager = ConfigManager::getInstance();
            QFont font ( manager->editorFont() );
            font.setPointSize( manager->editorFontSize() );

            editor->setFont( font );

            int index = ui->tabWidget->addTab( editor, fname );

            //after genereting this newTab can give to completer his father! //do not change it
            editor->initializeCompleter( projectData.projectPath );

            QPixmap fileicon(":/icons/img/file.png");
            ui->tabWidget->setTabIcon(index, fileicon);

            connect( ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeEditorTab(int)) );

            editor->insertPlainText(data);

            this->openedFileMap.insert( fname, path );

            connect( editor, &Editor::textChanged, this, &AxolotlApp::fileModified );

            setRecent( RECENT_FILES_PATH, path );
        }
        else
            ui->statusbar->showMessage( "File already opened", 5000 );
    }
}


void AxolotlApp::openProject( QString s68kPath )
{
    if ( s68kPath.compare( "" ) != 0 && !projectData.projectOpened )
    {
        int lio = s68kPath.lastIndexOf( "/" ) + 1;
        QString projectPath( s68kPath );
        projectPath.remove( lio, s68kPath.length() );

        projectManager = ProjectManager::getInstance();
        projectManager->generateSkASMTree( ui->treeWidget, s68kPath );

        projectData.projectOpened = true;
        projectData.s68kPath      = s68kPath;
        projectData.mainPath      = projectManager->getMainPath();
        projectData.projectPath   = projectPath;

        connect( projectManager, SIGNAL(openRequest(QString)), this, SLOT(openFile(QString)));

        connect( projectManager,
                SIGNAL(popupMenuRequest(ProjectTreeItem*,QString,ProjectManager::ProjectItemType)),
                this,
                SLOT(generatePopupMenu(ProjectTreeItem*,QString,ProjectManager::ProjectItemType))
        );

        ui->treeWidget->show();

        emit projectOpened();

        setRecent( RECENT_PROJECTS_PATH, projectData.s68kPath );
    }
    else
        ui->statusbar->showMessage( "Unable to open project", 8000 );
}


/**
 * Append '*' if file will update/modified
 */
void AxolotlApp::fileModified()
{
    int currindex = ui->tabWidget->currentIndex();
    QString currText( ui->tabWidget->tabText( currindex ) );

    Editor *curr = ( Editor* ) ui->tabWidget->widget( currindex );
    curr->setModified( true );

    if ( currText.at( currText.length() - 1 ) != "*" )
    {
        ui->tabWidget->setTabText( currindex, currText + "*" );
    }
}


/**
 * Delete current widget and relative widegt's tab.
 */
void AxolotlApp::closeEditorTab(int index)
{
    int currindex = ui->tabWidget->currentIndex();
    QString currText(ui->tabWidget->tabText(currindex));

    if (currText.at(currText.length() - 1) == "*")
    {
        currText.remove(currText.length() - 1, currText.length() - 1);
        this->openedFileMap.remove(currText);
    }
    else
    {
        this->openedFileMap.remove(currText);
    }

    //disconnect previous connection ==> after delete curr widget in selected tab, we must connect again every tab
    disconnect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeEditorTab(int)));

    //deleting curr widget will delete itself and tab who contain it
    ui->tabWidget->widget(index)->deleteLater();

    //reconnect all tabs with signal, tabBar's ids after delete, is changed
    connect(ui->tabWidget,    SIGNAL(tabCloseRequested(int)), this, SLOT(closeEditorTab(int)));
}


/**
 * Genarate popup menu on rightclick event over treewidget ( project tree ) items
 * this menu depend on the type of the item ( folder or file )
 *
 *
 * NOTE: must be complited!
 *
 */

void AxolotlApp::generatePopupMenu
                  ( ProjectTreeItem *parent, QString filePath, ProjectManager::ProjectItemType type )
{
    QPixmap folder(":/icons/img/folder.png");
    QPixmap close(":/icons/img/close.png");
    QPixmap newfile(":/icons/img/file.png");

    QPoint pos = parent->mapToGlobal( QPoint( 0, 0 ) );
    pos.setX( pos.x() + 50 );

    QMenu popupMenu( this );

    QAction actionDelete;
    actionDelete.setText( "Delete" );
    actionDelete.setParent( this );
    actionDelete.setIcon( close );

    QAction actionAddSrc;
    actionAddSrc.setText( "Add Source File" );
    actionAddSrc.setParent( this );
    actionAddSrc.setIcon( newfile );

    if (type == ProjectManager::ProjectItemType::Source)
    {
        QAction actionRename;
        actionRename.setText( "Rename" );
        actionRename.setParent( this );

        QAction actionOpen;
        actionOpen.setText( "Open" );
        actionOpen.setParent( this );
        actionOpen.setIcon( folder );

        popupMenu.addAction( &actionOpen );
        popupMenu.addSeparator();
        popupMenu.addAction( &actionRename );

        popupMenu.addAction( &actionDelete );


        connect( &actionDelete, &QAction::triggered,
                 projectManager, [=]{ projectManager->deleteSrc( ui->treeWidget, QVector<QString>() << projectData.s68kPath
                                                                                                    << filePath
                                                                                                    << parent->text() ); } );
        connect( projectManager, SIGNAL(fileNameChanged(QString,QString)), this, SLOT(updateDataAfterRenaming(QString,QString)) );


        connect( &actionOpen,   &QAction::triggered,
                 this, [=]{ AxolotlApp::openFile( filePath ); } );

        connect( &actionRename, &QAction::triggered,
                 projectManager, [=]{ projectManager->renameSrc( ui->treeWidget, QVector<QString>() << projectData.s68kPath
                                                                                                    << filePath
                                                                                                    << parent->text() ); } );
    }
    else if (type == ProjectManager::ProjectItemType::Folder)
    {
        popupMenu.addAction( &actionAddSrc );
        connect( &actionAddSrc, &QAction::triggered,
                 projectManager, [=]{ projectManager->addSrc(ui->treeWidget, projectData.s68kPath); } );
    }
    else
    {

        popupMenu.addAction( &actionDelete );


        connect( &actionDelete, &QAction::triggered,
                 projectManager, [=]{ projectManager->deleteSrc( ui->treeWidget, QVector<QString>() << projectData.s68kPath
                                                                                                    << filePath
                                                                                                    << parent->text() ); } );
    }



    popupMenu.exec(pos);
}


/**
 * Exec main file of current project or current opened ( selected from tabWidget ) file
 */
int AxolotlApp::build(QString path)
{
    QByteArray source = QByteArray(path.toUtf8());
    QString msg = "[BUILD] " + source + "\n";
    ui->output->insertPlainText(msg);

    QByteArray filename = QByteArray(path.toUtf8());
    filename.remove(path.indexOf('.'), path.size());
    filename.append(".B68");

    msg = "stray68k -a -c -i " + source + " -o " + filename + "\n";
    ui->output->insertPlainText(msg);

    char mo[] = "-o";
    char mi[] = "-i";
    char mc[] = "-c";

    int argc = 7;
    char *argv[argc];
    argv[2] = mc;
    argv[3] = mi;
    argv[4] = source.data();
    argv[5] = mo;
    argv[6] = filename.data();

    if (assemble(argc, argv))
    {
        ui->output->insertPlainText("[BUILD] Success\n");
        if (projectData.projectOpened)
        {
            ProManager *m = ProManager::getInstance();
            filename.remove(0, filename.lastIndexOf('/') + 1);
            m->addBinFile(filename);
        }


        return 1;
    }
    else
    {
        ui->output->insertPlainText("[BUILD] Fail\n");
        return 0;
    }
}


QString fixed4BReg(QString v)
{
    int max = 8;
    int delta = max - v.size();

    for (int i = 0; i < delta; ++i)
        v.prepend('0');

    return v;
}

QString fixedBinaryNum(QString v)
{
    QString s = QString::number(v.toUInt(nullptr, 16), 2);

    int max = 16;
    int delta = max - s.size();

    for (int i = 0; i < delta; ++i)
        s.prepend('0');

    return s;
}


void AxolotlApp::updateMachine()
{
    QString json = QString(machine_status());

    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());

    QJsonObject jsonObject = doc.object();

    QJsonObject CPU = jsonObject.value(QString("CPU")).toObject();
    ui->a0le->setText(fixed4BReg(CPU["A0"].toString()));
    ui->a1le->setText(fixed4BReg(CPU["A1"].toString()));
    ui->a2le->setText(fixed4BReg(CPU["A2"].toString()));
    ui->a3le->setText(fixed4BReg(CPU["A3"].toString()));
    ui->a4le->setText(fixed4BReg(CPU["A4"].toString()));
    ui->a5le->setText(fixed4BReg(CPU["A5"].toString()));
    ui->a6le->setText(fixed4BReg(CPU["A6"].toString()));
    ui->a7le->setText(fixed4BReg(CPU["A7"].toString()));

    ui->d0le->setText(fixed4BReg(CPU["D0"].toString()));
    ui->d1le->setText(fixed4BReg(CPU["D1"].toString()));
    ui->d2le->setText(fixed4BReg(CPU["D2"].toString()));
    ui->d3le->setText(fixed4BReg(CPU["D3"].toString()));
    ui->d4le->setText(fixed4BReg(CPU["D4"].toString()));
    ui->d5le->setText(fixed4BReg(CPU["D5"].toString()));
    ui->d6le->setText(fixed4BReg(CPU["D6"].toString()));
    ui->d7le->setText(fixed4BReg(CPU["D7"].toString()));

    ui->usple->setText(fixed4BReg(CPU["US"].toString()));
    ui->ssple->setText(fixed4BReg(CPU["SS"].toString()));
    ui->pcle->setText(fixed4BReg(CPU["PC"].toString()));
    ui->srle->setText(fixedBinaryNum(CPU["SR"].toString()));

    QJsonValue RAM = jsonObject.value(QString("RAM"));
    ui->haltle->setText(fixed4BReg(RAM["HALT"].toString()));

    QJsonValue OPC = jsonObject.value(QString("OP"));
    ui->istrle->setText(fixedBinaryNum(OPC["CODE"].toString()));
    ui->mnemle->setText(OPC["MNEMONIC"].toString());


    if (jsonObject.contains("IO"))
    {
        QJsonValue IO = jsonObject.value(QString("IO"));
        if (IO["TYPE"].toString().compare("O") == 0)
        {
            ui->output->insertPlainText(IO["VAL"].toString());
            ui->output->insertPlainText("");
        }
    }
}


void AxolotlApp::to_bottom()
{
    ui->output->verticalScrollBar()->setValue(ui->output->verticalScrollBar()->maximum());
}

void AxolotlApp::run( QString path )
{    
    if(!build(path)) return;

    QByteArray filename = QByteArray(path.toUtf8());
    filename.remove(path.indexOf('.'), path.size());
    filename.append(".B68");

    if ( ui->outputFrame->isHidden() ) on_actionProgram_output_frame_triggered();

    ui->stopBtn->setDisabled( false );

    QTime time;
    QString currTime = time.currentTime().toString();

    ui->output->insertPlainText( "[" + currTime + "]" +" Running -> " + filename + "\n" );

    ConfigManager *conf = ConfigManager::getInstance();
    QJsonObject obj = conf->machineAspect();
    QJsonArray data = obj.value("ratio").toArray();

    if (ui->sbs->isHidden())
    {
        ui->sbs->show();
        ui->splitter_2->setStretchFactor( data[0].toInt(), data[1].toInt() );
        conf->updateMachineAspect(1, data[0].toInt(), data[1].toInt());
    }

    begin_emulator(filename.data());

    updateMachine();

    ui->pushButton_4->setDisabled(false);
    ui->pushButton->setDisabled(false);
    ui->actionMemory->setDisabled(false);

    Editor *e = (Editor *) ui->tabWidget->currentWidget();
    QTextCursor c = QTextCursor(e->document());
    QTextCharFormat fmt1;
    fmt1.setBackground(Qt::transparent);

    for (int i = 0; i < e->document()->blockCount(); i++)
    {
        QTextBlock block = e->document()->findBlockByLineNumber(i);
        int blockPos = block.position();

        c.setPosition(blockPos);
        c.select(QTextCursor::LineUnderCursor);
        c.setCharFormat(fmt1);
    }

    pc = pc_disc();
    block_num = org_disc(e);

    e->setReadOnly(true);

}



void AxolotlApp::disableRunProject( bool value )
{
    ui->actionRun_project->setDisabled( value );
    ui->actionReload_project->setDisabled( value );
}


void AxolotlApp::disableEditorActions( int value )
{
    if ( value == -1 ) //  -1 = no tab opened; 0 or greather = 1 or more tab opened
    {
        ui->actionSave->setDisabled          ( true );
        ui->actionSave_as->setDisabled       ( true );
        ui->actionClose_all_tabs->setDisabled( true );
        ui->actionCurrent_editor_zoom_in->setDisabled ( true );
        ui->actionCurrent_editor_zoom_out->setDisabled( true );
        ui->actionRun->setDisabled( true );
    }
    else
    {
        ui->actionSave->setDisabled          ( false );
        ui->actionSave_as->setDisabled       ( false );
        ui->actionClose_all_tabs->setDisabled( false );
        ui->actionCurrent_editor_zoom_in->setDisabled ( false );
        ui->actionCurrent_editor_zoom_out->setDisabled( false );
        ui->actionRun->setDisabled( false );
    }
}



void AxolotlApp::loadNewSettings()
{
    setTheme();

    QFont newEditorFont( settingsManager->getEditorFont() );
    newEditorFont.setPointSize( settingsManager->getEditorFontSize() );

    for (int index = ui->tabWidget->count() - 1; index >= 0 ; index--)
    {
        Editor *editor = (Editor*)ui->tabWidget->widget(index);
        EditorHighlighter *highLighter = editor->getHighlighter();
        highLighter->setHighLighting();
        highLighter->setDocument( editor->document() );
        editor->setSyntaxHighLighter( highLighter );
        editor->setFont( newEditorFont );
    }

    QFont newConsoleFont( settingsManager->getConsoleFont() );
    newConsoleFont.setPointSize( settingsManager->getConsoleFontSize() );
    ui->output->setFont(  newConsoleFont );

    ui->statusbar->showMessage( "Changes applied successfully", 5000 );
}


void AxolotlApp::updateDataAfterRenaming(QString oldName, QString newName)
{
    QString path = QString();
    if ( openedFileMap.contains( oldName ) )
    {
        path = openedFileMap.value( oldName );

        if ( path.compare( "" )  != 0 )
        {
            int lio = path.lastIndexOf( "/" ) + 1;
            path.remove( lio, path.length() );
            path.append( newName );
        }

        openedFileMap.remove( oldName );
        openedFileMap.insert( newName, path );

        for ( int index = 0; index < ui->tabWidget->count(); index++ )
        {
            QString currText( ui->tabWidget->tabText( index ) );

            if ( currText.compare( oldName ) == 0 )
                ui->tabWidget->setTabText( index, newName );
        }
    }
}



//#################################### END PROGRAMMER DEFINED SLOTS ################################













//#################################### START UI DEFINED SLOTS #####################################






//*********** FILE MENU ************


/**
 * Create new SkEditor called "new" + tabsNums+1; Insert into filePaths the new file.
 */
void AxolotlApp::on_actionNewFile_triggered()
{
    //spawn new editor
    Editor *editor = new Editor( ui->tabWidget );

    ConfigManager *manager = ConfigManager::getInstance();
    QFont font ( manager->editorFont() );
    font.setPointSize( manager->editorFontSize() );

    editor->setFont( font );

    //set default name
    QString tabName("new" + QString::number(ui->tabWidget->count()));

    //append this new tab
    int index = ui->tabWidget->addTab(editor, tabName);

    //after genereting this newTab can give to completer his father! //do not change it
    editor->initializeCompleter();

    QPixmap fileicon(":/icons/img/file.png");
    fileicon = fileicon.scaled( 32, 32, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation );

    ui->tabWidget->setTabIcon(index, fileicon);

    //connect every tab to func {SkAsm_MW::closeTab(index)}
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeEditorTab(int)));
    connect(editor, &Editor::textChanged, this, &AxolotlApp::fileModified);
}


/**
 * Open file and create new QTab; append file's data to filePaths
 */
void AxolotlApp::on_actionOpenFile_triggered()
{
    QString path = QFileDialog::getOpenFileName();

    if ( path.compare( "" ) != 0 )
        openFile( path ); //call programmer defined slot "openFile"
    else
        ui->statusbar->showMessage("Unable to open file", 8000);
}




void AxolotlApp::on_actionNewProject_triggered()
{
    projectWizard = new ProjectWizard;
    connect( projectWizard, &ProjectWizard::created, this, [=] { AxolotlApp::openProject( projectWizard->gets68kPath() ); } );
    projectWizard->run();
}



void AxolotlApp::on_actionOpenProject_triggered()
{
    if ( !projectData.projectOpened )
    {
        QString s68kPath = QFileDialog::getOpenFileName( this, tr( "Open project" ), QDir::currentPath(), tr( "*.s68k" ) );

        openProject( s68kPath );
    }
    else
        ui->statusbar->showMessage( "A project is already open", 8000 );
}


/**
 * Clear data
 *
 * NOTE: bust be compled!
 */

void AxolotlApp::on_actionCloseProject_triggered()
{
    ui->treeWidget->clear();

    projectData.projectOpened = false;
    projectData.s68kPath     = QString();
    projectData.mainPath      = QString();
    projectData.projectPath   = QString();

    emit projectClosed();
}





/**
 * Save file if it's modified; get file's current path from filePaths's map
 */
void AxolotlApp::on_actionSave_triggered()
{    
    int currindex = ui->tabWidget->currentIndex();
    QString currText(ui->tabWidget->tabText(currindex));

    if (currText.at(currText.length() - 1) == "*")
    {
        currText.remove(currText.length() - 1, currText.length() - 1);

        if (!this->openedFileMap.contains(currText))
        {
            on_actionSave_as_triggered();
            return;
        }

        QString currPath = this->openedFileMap.value(currText);

        setRecent( RECENT_FILES_PATH, currPath );

        if (currPath.compare("") != 0)
        {
            Editor *currEditor = (Editor*)ui->tabWidget->currentWidget();
            QString  editorData(currEditor->toPlainText());

            QSaveFile *f = new QSaveFile(currPath);
            f->open(QIODevice::WriteOnly);
            f->write("");
            f->commit();
            f->open(QIODevice::WriteOnly);
            f->write(editorData.toUtf8());
            f->commit();
            f->deleteLater();
            ui->tabWidget->setTabText(currindex, currText);

            ui->statusbar->showMessage( "File saved successfully", 5000 );

            currEditor->setModified( false );
        }
    }
}


void AxolotlApp::on_actionSave_as_triggered()
{

    QFileDialog* fd = new QFileDialog(this, "Save as...", "", tr("SkASM File / .skasm;;Plancton File / .plct"));
    QString fname;

    fd->setFileMode(QFileDialog::AnyFile);
    fd->setAcceptMode(QFileDialog::AcceptSave);

    if (fd->exec()==QDialog::Accepted) {
        QStringList fl = fd->selectedFiles();

        if (!fl.isEmpty()) fname = fl[0];
        else return;

        if(fd->selectedNameFilter() == "SkASM File / .skasm")         fname += ".skasm";
        else if (fd->selectedNameFilter() == "Plancton File / .plct") fname += ".plct";


        Editor *currEditor = (Editor*) ui->tabWidget->currentWidget();
        QString editorData(currEditor->toPlainText());

        int currindex = ui->tabWidget->currentIndex();

        QSaveFile *f = new QSaveFile(fname);
        f->open(QIODevice::WriteOnly);
        f->write("");
        f->commit();
        f->open(QIODevice::WriteOnly);
        f->write(editorData.toUtf8());
        f->commit();
        f->deleteLater();

        QString path(fname);
        int lio = fname.lastIndexOf("/") + 1;
        fname.remove(0, lio);

        ui->tabWidget->setTabText(currindex, fname);

        this->openedFileMap.insert(fname, path);

        setRecent( RECENT_FILES_PATH, path );

        ui->statusbar->showMessage( "File saved successfully", 5000 );

        currEditor->setModified( false );

        QFile savedFile( path );
        savedFile.setPermissions(QFile::ReadGroup  | QFile::ReadOther  | QFile::ReadOwner  | QFile::ReadUser |\
                                 QFile::WriteGroup | QFile::WriteOther | QFile::WriteOwner | QFile::WriteUser|\
                                 QFile::ExeGroup   | QFile::ExeOther   | QFile::ExeOwner   | QFile::ExeUser  );
    }
}


void AxolotlApp::on_actionClose_all_tabs_triggered()
{
    ui->tabWidget->clear();
    this->openedFileMap.clear();
}


void AxolotlApp::on_actionForce_quit_triggered()
{
    qApp->quit();
}




//***************** VIEW MENU *************



void AxolotlApp::on_actionCurrent_editor_zoom_in_triggered()
{
    Editor *currEditor = (Editor*)ui->tabWidget->currentWidget();
    QFont currFont = currEditor->font();
    currFont.setPointSize(currFont.pointSize() + 1);
    currEditor->setFont(currFont);
    QFontMetricsF *metrics = new QFontMetricsF(currFont);
    qreal size = metrics->lineSpacing();
    currEditor->setTabStopDistance(size*2);

    delete metrics;
}


void AxolotlApp::on_actionCurrent_editor_zoom_out_triggered()
{
    Editor *currEditor = (Editor*)ui->tabWidget->currentWidget();
    QFont currFont = currEditor->font();
    currFont.setPointSize(currFont.pointSize() - 1);
    currEditor->setFont(currFont);
    QFontMetricsF *metrics = new QFontMetricsF(currFont);
    qreal size = metrics->lineSpacing();
    currEditor->setTabStopDistance(size*2);

    delete metrics;
}


/**
 * Show pseudo-console frame
 */
void AxolotlApp::on_actionProgram_output_frame_triggered()
{
    ConfigManager *conf = ConfigManager::getInstance();
    QJsonObject obj = conf->consoleAspect();
    QJsonArray data = obj.value("ratio").toArray();

    if (ui->outputFrame->isHidden())
    {

        ui->outputFrame->show();
        ui->outputFrame->setMinimumHeight(1);
        ui->splitter_3->setStretchFactor( data[0].toInt(), data[1].toInt() );
        ui->actionProgram_output_frame->setText("Hide program output frame");
        conf->updateConsoleAspect(1, data[0].toInt(), data[1].toInt());
    }
    else
    {
        ui->outputFrame->hide();
        ui->outputFrame->setMinimumHeight(0);
        ui->actionProgram_output_frame->setText("Show program output frame");
        conf->updateConsoleAspect(0, data[0].toInt(), data[1].toInt());
    }
}


void AxolotlApp::on_actionToggle_project_frame_triggered()
{
    ConfigManager *conf = ConfigManager::getInstance();
    QJsonObject obj = conf->projectAspect();
    QJsonArray data = obj.value("ratio").toArray();

    if (ui->treeWidget->isHidden())
    {
        ui->treeWidget->show();
        ui->treeWidget->setMinimumHeight(1);
        ui->splitter->setStretchFactor( data[0].toInt(), data[1].toInt() );
        conf->updateProjectAspect(1, data[0].toInt(), data[1].toInt());
    }
    else
    {
        ui->treeWidget->hide();
        ui->treeWidget->setMinimumHeight(0);
        conf->updateProjectAspect(0, data[0].toInt(), data[1].toInt());
    }
}




//************* RUN MENU ****************

void AxolotlApp::on_actionRun_triggered()
{
    QString progName = ui->tabWidget->tabText( ui->tabWidget->currentIndex() );

    if ( progName.lastIndexOf( "*" ) != -1 )
        progName.remove( progName.length() - 1, progName.length() );

    if ( openedFileMap.contains(progName) )
    {
        QString progPath = openedFileMap.value( progName );

        run( progPath );
    }
    else
        ui->statusbar->showMessage( "File can't be run", 5000 );

}

void AxolotlApp::on_actionRun_project_triggered()
{
    run( projectData.mainPath );
}



//********* OPTIONS MENU ************


void AxolotlApp::on_actionSettings_triggered()
{
    if ( settingsManager != nullptr ) settingsManager->deleteLater();

    settingsManager = new SettingsManager(this);
    settingsManager->readConfigAndSet();
    connect(settingsManager, &SettingsManager::settingsUpdateRequest, this, &AxolotlApp::loadNewSettings);
}





//************* PSEUDO-CONSOLE FRAME'S BUTTONS *************



void AxolotlApp::on_cleanBtn_clicked()
{
    ui->output->clear();
}


void AxolotlApp::on_stopBtn_clicked()
{
    ui->stopBtn->setDisabled( true );
    ui->pushButton->setDisabled( true );
    ui->pushButton_4->setDisabled( true );
    ui->actionMemory->setDisabled(true);

    updateMachine();
    end_emulator();

    ui->output->insertPlainText( "Program exited" );

    ui->output->insertPlainText( "\n\n" );
    ui->statusbar->showMessage( "Program terminated!", 5000 );
}









void AxolotlApp::on_actionReload_project_triggered()
{
    projectManager->generateSkASMTree(ui->treeWidget, projectData.s68kPath);
}


int AxolotlApp::pc_disc()
{
    QString json = QString(machine_status());
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject jsonObject = doc.object();
    QJsonObject CPU = jsonObject.value(QString("CPU")).toObject();

    int pc = CPU["PC"].toString().toInt(nullptr, 16);

    return pc;
}

int AxolotlApp::org_disc(Editor *e)
{
    int i = 0;

    QTextBlock block = e->document()->findBlockByLineNumber(i);

    while (!block.text().contains(QRegExp("ORG")))
        block = e->document()->findBlockByLineNumber(++i);

    return i;
}


void AxolotlApp::on_pushButton_4_released()
{
    Editor *e = (Editor *) ui->tabWidget->currentWidget();

    if (!emulate())
    {
        ui->pushButton_4->setDisabled(true);
        ui->pushButton->setDisabled(true);
        end_emulator();

        updateMachine();

        QTime time;
        QString currTime = time.currentTime().toString();
        ui->output->insertPlainText( "[" + currTime + "]" + " Terminated\n\n");

        ui->stopBtn->setDisabled(true);
        ui->pushButton->setDisabled(true);
        ui->pushButton_4->setDisabled(true);
        ui->actionMemory->setDisabled(true);
        e->setReadOnly(false);

        QTextCursor c = QTextCursor(e->document());
        QTextCharFormat fmt1;
        fmt1.setBackground(Qt::transparent);

        for (int i = 0; i < e->document()->blockCount(); i++)
        {
            QTextBlock block = e->document()->findBlockByLineNumber(i);
            int blockPos = block.position();

            c.setPosition(blockPos);
            c.select(QTextCursor::LineUnderCursor);
            c.setCharFormat(fmt1);
        }
    }
    else
    {
        updateMachine();

        QTextCharFormat fmt1;
        fmt1.setBackground(Qt::transparent);

        QTextBlock block = e->document()->findBlockByLineNumber(block_num);
        int blockPos = block.position();

        QTextCursor c = QTextCursor(e->document());

        c.setPosition(blockPos);
        c.select(QTextCursor::LineUnderCursor);
        c.setCharFormat(fmt1);

        QTextCharFormat fmt;
        fmt.setBackground(QBrush(QColor(30, 30, 30), Qt::SolidPattern));

        int local_pc = pc_disc();


        if (local_pc < pc)
        {
            block_num -= (pc - local_pc) / 4;
            block = e->document()->findBlockByLineNumber(block_num);
        }
        else
        {
            block = e->document()->findBlockByLineNumber(++block_num);
            while (!block.text().contains(QRegExp("\\S")) || block.text().contains(QRegExp("(^[aA-zZ0-9_]+:){1}")))
                block = e->document()->findBlockByLineNumber(++block_num);
        }

        blockPos = block.position();

        c.setPosition(blockPos);
        c.select(QTextCursor::LineUnderCursor);
        c.setCharFormat(fmt);

        pc = local_pc;
    }

}


void AxolotlApp::on_pushButton_released()
{
    Editor *e = (Editor *) ui->tabWidget->currentWidget();

    while (emulate())
    {
        updateMachine();

        QTextCharFormat fmt1;
        fmt1.setBackground(Qt::transparent);

        QTextBlock block = e->document()->findBlockByLineNumber(block_num);
        int blockPos = block.position();

        QTextCursor c = QTextCursor(e->document());

        c.setPosition(blockPos);
        c.select(QTextCursor::LineUnderCursor);
        c.setCharFormat(fmt1);

        QTextCharFormat fmt;
        fmt.setBackground(QBrush(QColor(30, 30, 30), Qt::SolidPattern));

        int local_pc = pc_disc();


        if (local_pc < pc)
        {
            block_num -= (pc - local_pc) / 4;
            block = e->document()->findBlockByLineNumber(block_num);
        }
        else
        {
            block = e->document()->findBlockByLineNumber(++block_num);
            while (!block.text().contains(QRegExp("\\S")) || block.text().contains(QRegExp("(^[aA-zZ0-9_]+:){1}")))
                block = e->document()->findBlockByLineNumber(++block_num);
        }

        blockPos = block.position();

        c.setPosition(blockPos);
        c.select(QTextCursor::LineUnderCursor);
        c.setCharFormat(fmt);

        pc = local_pc;
    }

    end_emulator();

    updateMachine();

    QTime time;
    QString currTime = time.currentTime().toString();
    ui->output->insertPlainText( "[" + currTime + "]" + " Terminated \n\n");

    ui->stopBtn->setDisabled(true);
    ui->pushButton->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->actionMemory->setDisabled(true);

    e->setReadOnly(false);

    QTextCursor c = QTextCursor(e->document());
    QTextCharFormat fmt1;
    fmt1.setBackground(Qt::transparent);

    for (int i = 0; i < e->document()->blockCount(); i++)
    {
        QTextBlock block = e->document()->findBlockByLineNumber(i);
        int blockPos = block.position();

        c.setPosition(blockPos);
        c.select(QTextCursor::LineUnderCursor);
        c.setCharFormat(fmt1);
    }
}


void AxolotlApp::on_actionMemory_triggered()
{
    if ( memory != nullptr ) memory->deleteLater();

    memory = new uimemory(this);
    memory->insert();
    memory->go();
    memory->show();

}

