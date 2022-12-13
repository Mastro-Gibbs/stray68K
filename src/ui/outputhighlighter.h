#ifndef OUTPUTHIGHLIGHTER_H
#define OUTPUTHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>

class OutputHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit OutputHighlighter(QTextDocument *parent = 0);

    void setHiglightFormat();

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    HighlightingRule rule;

    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat symbolsFormat;
    QTextCharFormat namesFormat;
    QTextCharFormat successFormat;
    QTextCharFormat buildFormat;
    QTextCharFormat asFormat;
    QTextCharFormat aeFormat;
    QTextCharFormat timeFormat;
    QTextCharFormat disabledFormat;
    QTextCharFormat enabledFormat;
};

#endif // OUTPUTHIGHLIGHTER_H
