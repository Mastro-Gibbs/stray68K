/**
 *  Singleton class
 *
 */

#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class ConfigManager
{
public:
    static ConfigManager *getInstance();

    void updateTheme( QString );

    void updateProjectData( int, QString );

    void updateEditorFont( QString );

    void updateConsoleFont( QString );

    void updateEditorFontSize( int );

    void updateConsoleFontSize( int );

    void updateProjectAspect( int, int, int );

    void updateMachineAspect( int, int, int );

    void updateConsoleAspect( int, int, int );

    QString theme();

    QJsonObject projectData();

    QString editorFont();

    QString consoleFont();

    int editorFontSize();

    int consoleFontSize();

    QJsonObject projectAspect();

    QJsonObject machineAspect();

    QJsonObject consoleAspect();

private:
    explicit ConfigManager();

    QFile configFile;

    void write( QByteArray );
    QJsonObject read();
};

#endif // CONFIGMANAGER_H
