#include "completer.h"
#include "ui_completer.h"

#include "../editor.h"

#include "completeritem.h"

Completer::Completer( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::Completer )
{
    parsingTree.root.node = ( QPlainTextEdit* ) parent;

    ui->setupUi( this );

    parentPos = parsingTree.root.node->mapToGlobal( QPoint( 0, 0 ) );

    cursor = parsingTree.root.node->textCursor();

    setWindowFlags( Qt::WindowType::Tool | Qt::WindowType::FramelessWindowHint );

    QShortcut *closeCompleter = new QShortcut( Qt::Key_Escape, this );
    connect( closeCompleter, &QShortcut::activated, this, &Completer::popdownCompleter );

    connect( ui->suggestionsList, &QListWidget::itemActivated, this, &Completer::insertWord );

    readFromModels();
}

Completer::~Completer()
{
    delete ui;
}


void Completer::readFromModels()
{
     QFile keywords( ":/keywords/keywords/keywords" );
    if ( keywords.open( QIODevice::ReadOnly ) )
    {
        QTextStream in( &keywords );
        while ( !in.atEnd() )
        {
            knownWords.stdWords.insert( in.readLine(), SuggestionType::Keyword );
        }
        keywords.close();
    }

    QFile reg( ":/keywords/keywords/regs" );
    if ( reg.open( QIODevice::ReadOnly ) )
    {
        QTextStream in( &reg );
        while ( !in.atEnd() )
        {
            knownWords.stdWords.insert( in.readLine(), SuggestionType::Reg );
        }
        reg.close();
    }

    QFile dir( ":/keywords/keywords/directives" );
    if ( dir.open( QIODevice::ReadOnly ) )
    {
        QTextStream in( &dir );
        while ( !in.atEnd() )
        {
            knownWords.stdWords.insert( in.readLine(), SuggestionType::Directive );
        }
        dir.close();
    }
}


QPoint Completer::updatePos()
{
    QPoint newPos( parentPos );

    cursor = parsingTree.root.node->textCursor();

    QFontInfo currFont = parsingTree.root.node->fontInfo();
    float delta = currFont.pointSize();

    delta = ( delta / 100 ) * 70;

    newPos.setX( parentPos.x() + ( cursor.columnNumber() * (int) delta ) );
    newPos.setY( parentPos.y() + ( cursor.blockNumber()  * (int) ( delta * 2 ) ) );

    return newPos;
}


void Completer::resizeCompleter( int sizeH )
{
    ui->suggestionsList->setCurrentRow( 0 );

    if ( sizeH < 10 )
    {
        this->setMaximumHeight( 17 * sizeH  );
        ui->suggestionsList->setMaximumHeight( 17 * sizeH );
        this->setMinimumHeight( 17 * sizeH  );
        ui->suggestionsList->setMinimumHeight( 17 * sizeH );
    }
    else
    {
        this->setMaximumHeight( 240 );
        ui->suggestionsList->setMaximumHeight( 240 );
        this->setMinimumHeight( 240 );
        ui->suggestionsList->setMinimumHeight( 240 );
    }

}


void Completer::insertWord()
{
    cursor.select( QTextCursor::WordUnderCursor );

    const CompleterItem *item = (CompleterItem *) ui->suggestionsList->selectedItems().at(0);

    QString suggestion = item->text();

    int fio = suggestion.indexOf( " " );
    if ( fio != -1 )
        suggestion.remove( fio, suggestion.size() - 1 );

    cursor.insertText( suggestion );

    popdownCompleter();
}

void Completer::setPathProject(const QString &newPathProject)
{
    parsingTree.projectPath = newPathProject;
}


void Completer::popupCompleter()
{
    move( updatePos() );

    this->show();
}


void Completer::popdownCompleter()
{
    this->hide();
}



void Completer::insertItems()
{
    ui->suggestionsList->clear();

    cursor = parsingTree.root.node->textCursor();
    cursor.select( QTextCursor::WordUnderCursor );
    QString filter = cursor.selectedText();

    QPixmap methodIcon( ":/icons/img/method.png" );
    QPixmap keywIcon( ":/icons/img/nativeKeyword.png" );
    QPixmap shebangIcon( ":/icons/img/shebang.png" );
    QPixmap paramIcon( ":/icons/img/param.png" );

    methodIcon = methodIcon.scaled( 24, 15, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation );
    keywIcon = keywIcon.scaled( 24, 15, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation );
    shebangIcon = shebangIcon.scaled( 24, 15, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation );
    paramIcon = paramIcon.scaled( 24, 15, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation );

    auto keys = knownWords.stdWords.keys();

    QRegExp exp("^" + filter.toUpper());
    QRegExp exp2("^" + filter.toLower());

    int i = 0;
    foreach ( const QString &keyw, keys )
    {
        if ( keyw.contains( exp ) || keyw.contains( exp2 ) )
        {
            CompleterItem *newItem = new CompleterItem;
            newItem->setText( keyw );
            ui->suggestionsList->insertItem( i++, newItem );

            int type = knownWords.stdWords.value( keyw );
            switch ( type ) {
                case SuggestionType::Directive:
                    newItem->setIcon( methodIcon );
                    break;
                case SuggestionType::Keyword:
                    newItem->setIcon( keywIcon );
                    break;
                case SuggestionType::Reg:
                    newItem->setIcon( shebangIcon );
                    break;
                case SuggestionType::Label:
                    newItem->setIcon( paramIcon );
                    break;
            }

            newItem->setSType( SuggestionType(type) );
        }
    }

    keys = knownWords.dynamicWords.keys();

    foreach ( const QString &keyw, keys )
    {
        if ( keyw.contains( exp ) || keyw.contains( exp2 )  )
        {
            CompleterItem *newItem = new CompleterItem;
            newItem->setText( keyw );
            ui->suggestionsList->insertItem( i++, newItem );

            int type = knownWords.dynamicWords.value( keyw );
            switch ( type ) {
                case SuggestionType::Directive:
                    newItem->setIcon( methodIcon );
                    break;
                case SuggestionType::Keyword:
                    newItem->setIcon( keywIcon );
                    break;
                case SuggestionType::Reg:
                    newItem->setIcon( shebangIcon );
                    break;
                case SuggestionType::Label:
                    newItem->setIcon( paramIcon );
                    break;
            }

            newItem->setSType( SuggestionType(type) );
        }
    }

    int suggestedElemsCount = ui->suggestionsList->count();

    if ( suggestedElemsCount )
    {
        resizeCompleter( suggestedElemsCount );
        popupCompleter();
    }
}



void Completer::checkForUpdate()
{
    discoverIncludedWords();
}



void Completer::discoverIncludedWords()
{
    CompleterParser parser;

    QMap<QString, SuggestionType> words = parser.findNewKeyw( parsingTree.root.rootText() );
    knownWords.dynamicWords.clear();
    knownWords.dynamicWords.insert(words);
}











































/*
void Completer::discoverIncludedWords()
{
    knownWords.cleanDynamicWords();

    CompleterParser parser;

    foreach ( TLTChildNode curr, parsingTree.childs )
    {
        if ( curr.testAndSet() )
        {
            if ( curr.nodeName.compare( QString() ) != 0 && \
                 parsingTree.projectPath.compare( QString() ) != 0 )
            {
                QFile file( parsingTree.projectPath + curr.nodeName );
                if ( file.open( QIODevice::ReadOnly | QIODevice::Text ) )
                {
                    QTextStream in ( &file );
                    QMap<QString, SuggestionType> words = parser.findNewKeyw( in.readAll() );
                    knownWords.dynamicWords.insert( words );
                    file.close();
                }
            }
        }
    }
}

void Completer::generateTLTree()
{
    knownWords.cleanDynamicWords();

    CompleterParser parser;
    QVector<QString> childs = parser.findIncludedFiles( parsingTree.root.rootText() );

    for ( int i = 0; i < childs.size(); i++ )
    {
        TLTChildNode node( childs[ i ] );
        if ( !parsingTree.childs.contains( node ) )
            parsingTree.childs.append( node );
    }

    for ( int i = 0; i < anchestor->count(); i++ )
    {
        Editor *editor = ( Editor* ) anchestor->widget( i );

        QString nodeName = anchestor->tabText( i );
        nodeName.remove( QRegularExpression( "\\*" ) );
        TLTChildNode node( nodeName, editor );

        if ( editor->getModified() && editor != parsingTree.root.node )
        {
            if ( parsingTree.childs.removeOne( node ) )
            {
                parsingTree.childs.append( node );
            }
        }
    }

    for ( int i = 0; i < anchestor->count(); i++ )
    {
        Editor *editor = ( Editor* ) anchestor->widget( i );

        QString nodeName = anchestor->tabText( i );
        nodeName.remove( QRegularExpression( "\\*" ) );
        TLTChildNode node( nodeName, editor );
        for ( int j = 0; j < parsingTree.childs.size(); j++ )
        {
            TLTChildNode curr = parsingTree.childs.at( j );
            if ( !curr.compareEditor( node ) )
            {
                curr.node = nullptr;
                parsingTree.childs.removeOne( curr );
                parsingTree.childs.append( curr );
            }
            if ( curr == QString() )
            {
                parsingTree.childs.removeOne( curr );
            }
        }
    }

    discoverIncludedWords();
}



void Completer::discoverIncludedWords()
{
    for ( int j = 0; j < parsingTree.childs.size(); j++ )
    {
        TLTChildNode curr = parsingTree.childs.at( j );
        CompleterParser parser;

        if ( curr.node != nullptr )
        {
            QMap<QString, SuggestionType> words = parser.findNewKeyw( curr.node->toPlainText() );
            knownWords.dynamicWords.insert( words );
        }
        else
        {

            QString includeName( curr.nodeName );
            if ( includeName.compare( QString() ) != 0 && pathProject.compare( QString() ) != 0 )
            {
                QFile file( pathProject + includeName );
                QString data;
                if ( file.open( QIODevice::ReadOnly | QIODevice::Text ) )
                {
                    QTextStream in ( &file );
                    data = in.readAll();
                    file.close();
                }

                QMap<QString, SuggestionType> words = parser.findNewKeyw( data );
                knownWords.dynamicWords.insert( words );
            }
        }
    }
}



















































































void Completer::eraseSuggestionlist()
{
    ui->suggestionsList->clear();
}






void Completer::updateDynamicModel()
{
    //CompleterParser completerParser;

    //QMap<QString, CompleterParser::SuggestionType> newKeyw = completerParser.findNewKeyw( editor->toPlainText() );

    //knownWords.dynamicWords.insert( newKeyw );
}


void Completer::readFromModels()
{

}







*/
