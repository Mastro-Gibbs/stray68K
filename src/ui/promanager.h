#ifndef PROMANAGER_H
#define PROMANAGER_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class ProManager
{
public:
    static ProManager *getInstance();

    void makeIt(QVector<QString>);

    void addBinFile(QString);

    void removeBinFile(QString);

    void addSourceFile(QString);

    void removeSourceFile(QString);

    enum ProDataType
    {
        Name = 1,
        Main = 3
    };

    QString proData(ProDataType);

    QJsonArray sources();

    QVector<QString> sourcesToQStringVector();

    QJsonArray binary();

    QVector<QString> binaryToQStringVector();

    void setProFile(QString newProFile);

private:
    explicit ProManager();

    QFile proFile;

    void write(QByteArray);
    QJsonObject read();
};

#endif // PROMANAGER_H
