#ifndef THEMESETTER_H
#define THEMESETTER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>

#include "configmanager.h"

class ThemeSetter
{
public:
    static ThemeSetter *getInstance();

    void setConfig();

    void setStyle();
    void setEditorBasicStyle();
    void setEditorKeywordStyle();
    void setEditorFontStyle();
    void setOutputFrameStyle();

    inline QString currentTheme() { return themeFile; }

    inline const QString getMainbg() const     { return mainbg.toString(); }
    inline const QString getTreeWidget() const { return treeWidget.toString(); }
    inline const QString getEditor() const     { return editor.toString(); }

    inline const QVector<QJsonValue> &getOutputFrame() const { return outputframe; }

    inline const QVector<QString> &getIstructionColor() const           { return istructionColor; }
    inline const QVector<QString> &getDirectiveColor() const            { return directiveColor; }
    inline const QVector<int> &getRegsFormatColor() const               { return regsFormatColor; }
    inline const QVector<int> &getNumberFormatColor() const             { return numberFormatColor; }
    inline const QVector<int> &getDirectiveFormatColor() const          { return directiveFormatColor; }
    inline const QVector<int> &getStdIstuctionFormatColor() const       { return stdIstuctionFormatColor; }
    inline const QVector<int> &getSizeFormatColor() const               { return sizeFormatColor; }
    inline const QVector<int> &getFunctionFormatColor() const           { return functionFormatColor; }
    inline const QVector<int> &getQuotationFormatColor() const          { return quotationFormatColor; }
    inline const QVector<int> &getOtherSymbolsFormatColor() const       { return otherSymbolsFormatColor; }
    inline const QVector<int> &getSingleLineCommentFormatColor() const  { return singleLineCommentFormatColor; }

    inline const QString getBasicFontColor() const        { return basicFontColor.toString(); }
    inline const QVector<int> &getLineNumberColor() const { return lineNumberColor; }


private:
    explicit ThemeSetter();

    QString themeFile;

    QJsonValue mainbg;
    QJsonValue treeWidget;
    QJsonValue editor;

    QVector<QJsonValue> outputframe;

    QVector<QString> directiveColor;
    QVector<QString> istructionColor;

    QVector<int> regsFormatColor;

    QVector<int> numberFormatColor;
    QVector<int> directiveFormatColor;
    QVector<int> stdIstuctionFormatColor;
    QVector<int> sizeFormatColor;
    QVector<int> functionFormatColor;
    QVector<int> quotationFormatColor;
    QVector<int> otherSymbolsFormatColor;
    QVector<int> singleLineCommentFormatColor;

    QJsonValue basicFontColor;
    QVector<int> lineNumberColor;

};

#endif // THEMESETTER_H
