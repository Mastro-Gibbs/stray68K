#include "editorhighlighter.h"

#include <QDebug>

EditorHighlighter::EditorHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{}

void EditorHighlighter::setHighLighting()
{
    themeSetter = ThemeSetter::getInstance();
    themeSetter->setConfig();
    themeSetter->setEditorFontStyle();

    HighlightingRule rule;

    QVector<int> directiveColor = themeSetter->getDirectiveFormatColor();
    directiveFormat.setForeground(QColor(directiveColor[0], directiveColor[1], directiveColor[2]));


    for (const QString &pattern : themeSetter->getDirectiveColor()) {
        QString data = QStringLiteral("\\b") + pattern + QStringLiteral("\\b");
        rule.pattern = QRegularExpression(data);
        rule.format = directiveFormat;
        highlightingRules.append(rule);
    }

    QVector<int> siColor = themeSetter->getStdIstuctionFormatColor();
    stdIstuctionFormat.setForeground(QColor(siColor[0], siColor[1], siColor[2]));

    for (const QString &pattern : themeSetter->getIstructionColor()) {
        QString data = QStringLiteral("\\b") + pattern + QStringLiteral("\\b");
        rule.pattern = QRegularExpression(data);
        rule.format = stdIstuctionFormat;
        highlightingRules.append(rule);
    }

    QVector<int> sizeColor = themeSetter->getSizeFormatColor();
    sizeFormat.setForeground(QColor(sizeColor[0], sizeColor[1], sizeColor[2]));
    rule.pattern = QRegularExpression(QStringLiteral("\\.(b|B|w|W|l|L)"));
    rule.format = sizeFormat;
    highlightingRules.append(rule);

    QVector<int> regsColor = themeSetter->getRegsFormatColor();
    regsFormat.setForeground(QColor(regsColor[0], regsColor[1], regsColor[2]));
    rule.pattern = QRegularExpression(QStringLiteral("\\w*((A|D|a|d))[0-7]"));
    rule.format = regsFormat;
    highlightingRules.append(rule);

    QVector<int> nfColor = themeSetter->getNumberFormatColor();
    numberFormat.setForeground(QColor(nfColor[0], nfColor[1], nfColor[2]));
    rule.pattern = QRegularExpression(QStringLiteral("\\w*(?<![a-zA-Z])[0-9]"));
    rule.format = numberFormat;
    highlightingRules.append(rule);

    QVector<int> fColor = themeSetter->getFunctionFormatColor();
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(QColor(fColor[0], fColor[1], fColor[2]));
    rule.pattern = QRegularExpression(QStringLiteral("(^[aA-zZ0-9_]+:){1}"));
    rule.format = functionFormat;
    highlightingRules.append(rule);

    QVector<int> qColor = themeSetter->getQuotationFormatColor();
    quotationFormat.setForeground(QColor(qColor[0], qColor[1], qColor[2]));
    rule.pattern = QRegularExpression(QStringLiteral("(\").*?\\1")); //(?:\")[^@]*(?:\")
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    QVector<int> osColor = themeSetter->getOtherSymbolsFormatColor();
    otherSymbolsFormat.setFontWeight(100);
    otherSymbolsFormat.setForeground(QColor(osColor[0], osColor[1], osColor[2]));
    rule.pattern = QRegularExpression(QStringLiteral("\\(|\\)|\\+|-|,"));
    rule.format = otherSymbolsFormat;
    highlightingRules.append(rule);

    QVector<int> slcColor = themeSetter->getSingleLineCommentFormatColor();
    singleLineCommentFormat.setForeground(QColor(slcColor[0], slcColor[1], slcColor[2]));
    rule.pattern = QRegularExpression(QStringLiteral(";.*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

}


void EditorHighlighter::highlightBlock(const QString &text)
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
