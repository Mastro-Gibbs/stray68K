#include "outputhighlighter.h"

OutputHighlighter::OutputHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{}


void OutputHighlighter::setHiglightFormat()
{
    symbolsFormat.setFontWeight(100);
    symbolsFormat.setForeground(QColor(255, 135, 0));
    rule.pattern = QRegularExpression(QStringLiteral("^[\[][A-Za-z]*[\\]]\\s*->|(->)"));
    rule.format = symbolsFormat;
    highlightingRules.append(rule);

    symbolsFormat.setFontWeight(100);
    symbolsFormat.setForeground(QColor(255, 135, 0));
    rule.pattern = QRegularExpression(QStringLiteral("^[\[]([0-9:])*\\]"));
    rule.format = symbolsFormat;
    highlightingRules.append(rule);

    namesFormat.setFontWeight(100);
    namesFormat.setForeground(QColor(255, 210, 0));
    const QString namesPatterns[] = {
        QStringLiteral("\\bTerminated\\b"),
        QStringLiteral("\\bRunning\\b"),
        QStringLiteral("\\bLocated in\\b"),
        QStringLiteral("\\bProgram exited\\b")
    };

    for (const QString &pattern : namesPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = namesFormat;
        highlightingRules.append(rule);
    }

    successFormat.setFontWeight(100);
    successFormat.setForeground(QColor(42, 200, 61));
    rule.pattern = QRegularExpression(QStringLiteral("\\bSuccess\\b"));
    rule.format = successFormat;
    highlightingRules.append(rule);

    buildFormat.setFontWeight(100);
    buildFormat.setForeground(QColor(212, 138, 250));
    rule.pattern = QRegularExpression(QStringLiteral("\\bBUILD\\b"));
    rule.format = buildFormat;
    highlightingRules.append(rule);

    asFormat.setFontWeight(100);
    asFormat.setForeground(QColor(230, 70, 70));
    rule.pattern = QRegularExpression(QStringLiteral("\\bASSEMBLER ERROR\\b"));
    rule.format = asFormat;
    highlightingRules.append(rule);

    aeFormat.setFontWeight(100);
    aeFormat.setForeground(QColor(245, 100, 100));
    rule.pattern = QRegularExpression(QStringLiteral("\\bASM ERROR\\b"));
    rule.format = aeFormat;
    highlightingRules.append(rule);
}


void OutputHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    setCurrentBlockState(0);
}
