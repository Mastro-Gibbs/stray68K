#include "completerparser.h"
#include <QDebug>


CompleterParser::CompleterParser(QObject *parent)
                : QObject(parent)
{
    labelRX = QRegularExpression( "(^[aA-zZ0-9_]+:){1}" );
}


QMap<QString, SuggestionType> CompleterParser::findNewKeyw( QString sourceText )
{
    QRegularExpressionMatchIterator it  = labelRX.globalMatch( sourceText );

    QMap<QString, SuggestionType> keywFinded;

    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        QString keyw( match.captured() );

        keywFinded.insert( keyw, SuggestionType::Label );
    }

    return keywFinded;
}

TLVector CompleterParser::findIncludedFiles(QString sourceText)
{
    QRegularExpressionMatchIterator it = labelRX.globalMatch( sourceText );

    TLVector includedFiles;

    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        QString keyw( match.captured() );
        keyw.remove( QRegularExpression( "@[a-zA-Z:]*( *)*" ) );
        if ( keyw.compare( QString() ) != 0 )
        {
            TLTChildNode *newNode = new TLTChildNode( keyw, true );
            includedFiles.insert( newNode );
        }
    }
    return includedFiles;
}
