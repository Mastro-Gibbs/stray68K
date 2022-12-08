/**
 * Singleton class
 *
 */

#ifndef EDITORHIGHLIGHTER_H
#define EDITORHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include "themesetter.h"

class EditorHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit EditorHighlighter(QTextDocument *parent = 0);

    void setHighLighting();

protected:
    void highlightBlock(const QString &text) override;

private:

    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat regsFormat;



    QTextCharFormat stdIstuctionFormat;
    QTextCharFormat directiveFormat;
    QTextCharFormat stdPrimitiveFormat;
    QTextCharFormat sizeFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat otherSymbolsFormat;

    ThemeSetter *themeSetter;
};


#endif // EDITORHIGHLIGHTER_H
