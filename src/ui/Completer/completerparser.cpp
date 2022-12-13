#include "completerparser.h"
#include <QDebug>


CompleterParser::CompleterParser(QObject *parent)
                : QObject(parent)
{
    labelRX = QRegularExpression(QStringLiteral("(\\n\\t\\n[aA-zZ0-9_]+:){1}"));
}


QMap<QString, SuggestionType> CompleterParser::findNewKeyw( QString sourceText )
{
    QRegularExpressionMatchIterator it  = labelRX.globalMatch( sourceText );

    QMap<QString, SuggestionType> keywFinded;

    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        QString keyw( match.captured() );
        keyw.remove(QChar(':'));
        keyw.remove(QChar('\t'));
        keyw.remove(QChar('\n'));

        keywFinded.insert( keyw, SuggestionType::Label );
    }

    return keywFinded;
}
