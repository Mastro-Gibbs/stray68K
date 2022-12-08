#include "editor.h"

#include <QDebug>

class LineNumberArea : public QWidget
{
public:
    LineNumberArea( Editor *editor ) : QWidget( editor ), codeEditor( editor )
    {}

    QSize sizeHint() const override
    {
        return QSize( codeEditor->lineNumberAreaWidth(), 0 );
    }

protected:
    void paintEvent( QPaintEvent *event ) override
    {
        codeEditor->lineNumberAreaPaintEvent( event );
    }

private:
    Editor *codeEditor;
};


Editor::Editor( QWidget *parent ) : QPlainTextEdit( parent )
{
    setLineWrapMode( Editor::LineWrapMode::NoWrap );

    themeSetter = ThemeSetter::getInstance();
    themeSetter->setConfig();
    themeSetter->setEditorBasicStyle();

    setStyleSheet( themeSetter->getBasicFontColor() );

    lineNumberArea = new LineNumberArea( this );

    connect( this, &Editor::blockCountChanged, this, &Editor::updateLineNumberAreaWidth );
    connect( this, &Editor::updateRequest,     this, &Editor::updateLineNumberArea );

    updateLineNumberAreaWidth( 0 );


    syntaxHighLighter = new EditorHighlighter;
    syntaxHighLighter->setHighLighting();
    syntaxHighLighter->setDocument( this->document() );

    spawnCompleter = new QShortcut( QKeySequence( tr( "Ctrl+Space" ) ), this );
    connect( spawnCompleter, &QShortcut::activated, this, &Editor::callCompleter );

}


void Editor::initializeCompleter( QString projectPath )
{
    m_completer = new Completer( this );
    m_completer->setPathProject( projectPath );
    m_completer->generateTLTree();
}

void Editor::callCompleter()
{
    m_completer->checkForUpdate();
    m_completer->insertItems();

    connect( this, &Editor::mouseClicked, m_completer, &Completer::popdownCompleter );
}

bool Editor::getModified() const
{
    return modified;
}

void Editor::setModified(bool value)
{
    modified = value;
}

void Editor::keyPressEvent( QKeyEvent *e )
{
    if ( e->key() == Qt::Key_Return )
    {
        QString line = this->textCursor().block().text();

        QPlainTextEdit::keyPressEvent( e );

        this->insertPlainText(line.split(QRegExp("\\S")).at(0));
    }
    else
    {
        QPlainTextEdit::keyPressEvent( e );
    }
}


int Editor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax( 1, blockCount() );
    while ( max >= 10 )
    {
        max /= 10;
        ++digits;
    }

    int space = 6 + fontMetrics().horizontalAdvance( QLatin1Char( '9' ) ) * digits;

    return space;
}


void Editor::updateLineNumberAreaWidth( int /* newBlockCount */)
{
    setViewportMargins( lineNumberAreaWidth(), 0, 0, 0 );
}


void Editor::updateLineNumberArea( const QRect &rect, int dy )
{
    if ( dy )
        lineNumberArea->scroll( 0, dy );
    else
        lineNumberArea->update( 0, rect.y(), lineNumberArea->width(), rect.height() );

    if ( rect.contains( viewport()->rect()) )
        updateLineNumberAreaWidth( 0 );
}


void Editor::setSyntaxHighLighter(EditorHighlighter *newSyntaxHighLighter)
{
    syntaxHighLighter = newSyntaxHighLighter;
    themeSetter->setEditorBasicStyle();
    setStyleSheet( themeSetter->getBasicFontColor() );
}


EditorHighlighter* Editor::getHighlighter()
{
    return this->syntaxHighLighter;
}


void Editor::resizeEvent( QResizeEvent *e )
{
    QPlainTextEdit::resizeEvent( e );

    QRect cr = contentsRect();
    lineNumberArea->setGeometry( QRect( cr.left(), cr.top(), lineNumberAreaWidth(), cr.height() ) );
}


void Editor::mousePressEvent(QMouseEvent *event)
{
    emit mouseClicked();

    QPlainTextEdit::mousePressEvent( event );
}


void Editor::lineNumberAreaPaintEvent( QPaintEvent *event )
{
    QPainter painter( lineNumberArea );

    themeSetter->setEditorBasicStyle();
    QVector<int> naColor = themeSetter->getLineNumberColor();
    QColor numberAreaColor = QColor( naColor[0], naColor[1], naColor[2] );
    painter.fillRect( event->rect(), numberAreaColor );

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound( blockBoundingGeometry( block ).translated( contentOffset() ).top() );
    int bottom = top + qRound( blockBoundingRect( block ).height() );

    while ( block.isValid() && top <= event->rect().bottom() )
    {
           if ( block.isVisible() && bottom >= event->rect().top() )
           {
               QString number = QString::number( blockNumber + 1 );
               painter.setPen( Qt::white );
               painter.drawText( 0, top, lineNumberArea->width(), fontMetrics().height(),
                                Qt::AlignCenter, number );
           }

           block = block.next();
           top = bottom;
           bottom = top + qRound( blockBoundingRect( block ).height() );
           ++blockNumber;
     }
}