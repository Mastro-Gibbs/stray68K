#ifndef COMPLETER_H
#define COMPLETER_H

#include <QWidget>
#include <QTextCursor>
#include <QPlainTextEdit>
#include <QShortcut>
#include <QListWidget>
#include <QDebug>

#include "completerparser.h"
#include "completerstructs.h"


namespace Ui {
class Completer;
}

class Completer : public QWidget
{
    Q_OBJECT

public:
    explicit Completer( QWidget *parent );
    ~Completer();

    void updateWords();

    void popupCompleter();
    void popdownCompleter();

    void insertItems();

    void generateTLTree();

    void checkForUpdate();

    void discoverIncludedWords();

    /*
    void readFromModels();

    void eraseSuggestionlist();

    void updateDynamicModel();
    */

    void setPathProject(const QString &newPathProject);

public slots:
    void insertWord();

private:
    Words  knownWords;
    TLTree parsingTree;

    Ui::Completer *ui;

    QPoint parentPos;

    QTextCursor cursor;

private:
    void readFromModels();

    QPoint updatePos();

    void resizeCompleter( int sizeH );

};
#endif // COMPLETER_H
