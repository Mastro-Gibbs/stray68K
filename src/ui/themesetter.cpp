#include "themesetter.h"

ThemeSetter::ThemeSetter()
{}


ThemeSetter *ThemeSetter::getInstance()
{
    static ThemeSetter instance;
    return &instance;
}


void ThemeSetter::setConfig()
{
    ConfigManager *config = ConfigManager::getInstance();
    themeFile = config->theme();
}


void ThemeSetter::setStyle()
{
    QFile file;
    file.setFileName(themeFile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(val.toUtf8());

    QJsonObject jsonObject = jsonDocument.object();

    mainbg      = jsonObject.value(QString("skeditorapp"));
    treeWidget  = jsonObject.value(QString("projectarea"));
    editor      = jsonObject.value(QString("editor"));
}


void ThemeSetter::setEditorBasicStyle()
{
    QFile file;
    file.setFileName(themeFile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(val.toUtf8());

    QJsonObject jsonObject = jsonDocument.object();

    QJsonValue value = jsonObject.value(QString("basiceditor"));
    QJsonObject item = value.toObject();

    QJsonValue lineNumber = item["linecolor"];

    basicFontColor = item["defaultfc"];

    lineNumberColor << lineNumber.toArray()[0].toInt()
                    << lineNumber.toArray()[1].toInt()
                    << lineNumber.toArray()[2].toInt();

}


void ThemeSetter::setEditorKeywordStyle()
{
    QFile file;
    file.setFileName(themeFile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(val.toUtf8());

    QJsonObject jsonObject = jsonDocument.object();

    QJsonValue value = jsonObject.value(QString("keywords"));
    QJsonObject item = value.toObject();

    QJsonValue directive = item["directive"];
    QJsonValue istruction = item["istruction"];


    QJsonArray dir = directive.toArray();
    for (auto i = dir.begin(); i != dir.end(); i++)
        directiveColor.append(i->toString());

    QJsonArray ist = istruction.toArray();
    for (auto i = ist.begin(); i != ist.end(); i++)
        istructionColor.append(i->toString());

}


void ThemeSetter::setEditorFontStyle()
{
    QFile file;
    file.setFileName(themeFile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(val.toUtf8());

    QJsonObject jsonObject = jsonDocument.object();

    QJsonValue value = jsonObject.value(QString("fontcolors"));
    QJsonObject item = value.toObject();

    QJsonValue regFormat               = item["regFormat"];
    QJsonValue numberFormat            = item["numberFormat"];
    QJsonValue directiveFormat         = item["directiveFormat"];
    QJsonValue stdIstuctionFormat      = item["stdIstuctionFormat"];
    QJsonValue sizeFormat              = item["sizeFormat"];
    QJsonValue functionFormat          = item["functionFormat"];
    QJsonValue quotationFormat         = item["quotationFormat"];
    QJsonValue otherSymbolsFormat      = item["otherSymbolsFormat"];
    QJsonValue singleLineCommentFormat = item["singleLineCommentFormat"];

    regsFormatColor << regFormat.toArray()[0].toInt()
                    << regFormat.toArray()[1].toInt()
                    << regFormat.toArray()[2].toInt();

    numberFormatColor << numberFormat.toArray()[0].toInt()
                      << numberFormat.toArray()[1].toInt()
                      << numberFormat.toArray()[2].toInt();

    directiveFormatColor << directiveFormat.toArray()[0].toInt()
                         << directiveFormat.toArray()[1].toInt()
                         << directiveFormat.toArray()[2].toInt();

    stdIstuctionFormatColor << stdIstuctionFormat.toArray()[0].toInt()
                            << stdIstuctionFormat.toArray()[1].toInt()
                            << stdIstuctionFormat.toArray()[2].toInt();

    sizeFormatColor << sizeFormat.toArray()[0].toInt()
                    << sizeFormat.toArray()[1].toInt()
                    << sizeFormat.toArray()[2].toInt();

    functionFormatColor << functionFormat.toArray()[0].toInt()
                        << functionFormat.toArray()[1].toInt()
                        << functionFormat.toArray()[2].toInt();

    quotationFormatColor << quotationFormat.toArray()[0].toInt()
                         << quotationFormat.toArray()[1].toInt()
                         << quotationFormat.toArray()[2].toInt();

    otherSymbolsFormatColor << otherSymbolsFormat.toArray()[0].toInt()
                            << otherSymbolsFormat.toArray()[1].toInt()
                            << otherSymbolsFormat.toArray()[2].toInt();

    singleLineCommentFormatColor << singleLineCommentFormat.toArray()[0].toInt()
                                 << singleLineCommentFormat.toArray()[1].toInt()
                                 << singleLineCommentFormat.toArray()[2].toInt();

    setEditorKeywordStyle();
}


void ThemeSetter::setOutputFrameStyle()
{
    QFile file;
    file.setFileName(themeFile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(val.toUtf8());

    QJsonObject jsonObject = jsonDocument.object();

    QJsonValue value = jsonObject.value(QString("outputframe"));
    QJsonObject item = value.toObject();

    outputframe << item["hidebtn"] << item["outarea"];
}
