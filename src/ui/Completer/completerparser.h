#ifndef COMPLETERPARSER_H
#define COMPLETERPARSER_H

#include <QObject>
#include <QMap>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "completerenums.h"
#include "completerstructs.h"

class CompleterParser : public QObject
{
    Q_OBJECT

public:
    explicit CompleterParser(QObject *parent = nullptr);

    QMap<QString, SuggestionType> findNewKeyw( QString sourceText );

private:
    QRegularExpression labelRX;
};

#endif // COMPLETERPARSER_H
