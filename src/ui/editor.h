#ifndef EDITOR_H
#define EDITOR_H

#include <QPlainTextEdit>
#include <QPainter>
#include <QTextBlock>
#include <QTextCursor>
#include <QDebug>
#include <QAbstractItemView>
#include <QShortcut>

#include "editorhighlighter.h"
#include "themesetter.h"
#include "Completer/completer.h"


class Editor : public QPlainTextEdit
{
    Q_OBJECT

public:
    Editor( QWidget *parent = nullptr );

    void lineNumberAreaPaintEvent( QPaintEvent *event );

    int lineNumberAreaWidth();

    void setSyntaxHighLighter( EditorHighlighter *newSyntaxHighLighter );

    EditorHighlighter *getHighlighter();

    void initializeCompleter( QString projectPath = QString() );

    bool getModified() const;
    void setModified(bool value);

protected:
    void keyPressEvent( QKeyEvent *e ) override;

    void resizeEvent( QResizeEvent *event ) override;

    void mousePressEvent ( QMouseEvent * event ) override;

signals:
    void completerCalled();
    void mouseClicked();

private slots:
    void updateLineNumberAreaWidth( int newBlockCount );
    void updateLineNumberArea( const QRect &rect, int dy );

    void callCompleter();

private:
    QWidget *lineNumberArea;
    EditorHighlighter *syntaxHighLighter;
    ThemeSetter *themeSetter;
    Completer *m_completer = nullptr;
    QShortcut *spawnCompleter = nullptr;
    bool modified;
};

#endif // EDITOR_H
