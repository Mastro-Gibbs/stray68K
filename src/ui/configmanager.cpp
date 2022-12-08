#include "configmanager.h"

ConfigManager::ConfigManager()
{
    configFile.setFileName( "config.json" );
}


ConfigManager *ConfigManager::getInstance()
{
    static ConfigManager configManager;
    return &configManager;
}


void ConfigManager::write( QByteArray bytes )
{
    if( configFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
    {
        QTextStream iStream( &configFile );
        iStream.setCodec( "utf-8" );
        iStream << bytes;
        configFile.close();
    }
}

QJsonObject ConfigManager::read()
{
    configFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = configFile.readAll();
    configFile.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(val.toUtf8());

    return jsonDocument.object();

}


void ConfigManager::updateProjectData
                    ( int state, QString path )
{
    QJsonObject projectData;
    projectData.insert( "state", state );
    projectData.insert( "path", path );

    QJsonObject content = read();
    content.remove("projectData");
    content.insert("projectData", projectData);

    QJsonDocument document;
    document.setObject( content );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );

    write( bytes );
}


void ConfigManager::updateTheme
                    ( QString value )
{
    QJsonObject content = read();
    content.remove("theme");
    content.insert( "theme", value );

    QJsonDocument document;
    document.setObject( content );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );

    write( bytes );
}


void ConfigManager::updateEditorFont
                    ( QString value )
{
    QJsonObject content = read();
    content.remove("editorFont");
    content.insert( "editorFont", value );

    QJsonDocument document;
    document.setObject( content );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );

    write( bytes );
}


void ConfigManager::updateEditorFontSize
                    ( int value )
{
    QJsonObject content = read();
    content.remove("editorFontSize");
    content.insert( "editorFontSize", value );

    QJsonDocument document;
    document.setObject( content );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );

    write( bytes );
}

void ConfigManager::updateConsoleFont
                    ( QString value )
{
    QJsonObject content = read();
    content.remove("consoleFont");
    content.insert( "consoleFont", value );

    QJsonDocument document;
    document.setObject( content );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );

    write( bytes );
}


void ConfigManager::updateConsoleFontSize
                    ( int value )
{
    QJsonObject content = read();
    content.remove("consoleFontSize");
    content.insert( "consoleFontSize", value );

    QJsonDocument document;
    document.setObject( content );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );

    write( bytes );
}


void ConfigManager::updateProjectAspect( int s, int x, int y )
{
    QJsonObject content = read();
    QJsonObject aspect  = content.value(QString("aspect")).toObject();

    aspect.remove("project");
    content.remove("aspect");

    QJsonObject projectData;
    projectData.insert( "status", s );

    QJsonArray ratio;
    ratio.append(x);
    ratio.append(y);
    projectData.insert( "ratio", ratio );

    aspect.insert("project", projectData);
    content.insert("aspect", aspect);

    QJsonDocument document;
    document.setObject( content );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );

    write( bytes );
}

void ConfigManager::updateMachineAspect( int s, int x, int y )
{
    QJsonObject content = read();
    QJsonObject aspect  = content.value(QString("aspect")).toObject();

    aspect.remove("machine");
    content.remove("aspect");

    QJsonObject machineData;
    machineData.insert( "status", s );

    QJsonArray ratio;
    ratio.append(x);
    ratio.append(y);
    machineData.insert( "ratio", ratio );

    aspect.insert("machine", machineData);
    content.insert("aspect", aspect);

    QJsonDocument document;
    document.setObject( content );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );

    write( bytes );
}

void ConfigManager::updateConsoleAspect( int s, int x, int y )
{
    QJsonObject content = read();
    QJsonObject aspect  = content.value(QString("aspect")).toObject();

    aspect.remove("console");
    content.remove("aspect");

    QJsonObject consoleData;
    consoleData.insert( "status", s );

    QJsonArray ratio;
    ratio.append(x);
    ratio.append(y);
    consoleData.insert( "ratio", ratio );

    aspect.insert("console", consoleData);
    content.insert("aspect", aspect);

    QJsonDocument document;
    document.setObject( content );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );

    write( bytes );
}



QString ConfigManager::theme()
{
    configFile.open( QIODevice::ReadOnly | QIODevice::Text );
    QString val = configFile.readAll();
    configFile.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson( val.toUtf8() );

    QJsonObject jsonObject = jsonDocument.object();

    return jsonObject.value( QString( "theme" ) ).toString();
}



QJsonObject ConfigManager::projectData()
{
    configFile.open( QIODevice::ReadOnly | QIODevice::Text );
    QString val = configFile.readAll();
    configFile.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson( val.toUtf8() );

    QJsonObject jsonObject = jsonDocument.object();

    QJsonValue value = jsonObject.value( QString( "projectData") );
    return value.toObject();
}


QString ConfigManager::editorFont()
{
    configFile.open( QIODevice::ReadOnly | QIODevice::Text );
    QString val = configFile.readAll();
    configFile.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson( val.toUtf8() );

    QJsonObject jsonObject = jsonDocument.object();

    return jsonObject.value( QString( "editorFont" ) ).toString();
}


QString ConfigManager::consoleFont()
{
    configFile.open( QIODevice::ReadOnly | QIODevice::Text );
    QString val = configFile.readAll();
    configFile.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson( val.toUtf8() );

    QJsonObject jsonObject = jsonDocument.object();

    return jsonObject.value( QString( "consoleFont" ) ).toString();
}

int ConfigManager::editorFontSize()
{
    configFile.open( QIODevice::ReadOnly | QIODevice::Text );
    QString val = configFile.readAll();
    configFile.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson( val.toUtf8() );

    QJsonObject jsonObject = jsonDocument.object();

    return jsonObject.value( QString( "editorFontSize" ) ).toInt();
}

int ConfigManager::consoleFontSize()
{
    configFile.open( QIODevice::ReadOnly | QIODevice::Text );
    QString val = configFile.readAll();
    configFile.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson( val.toUtf8() );

    QJsonObject jsonObject = jsonDocument.object();

    return jsonObject.value( QString( "consoleFontSize" ) ).toInt();
}


QJsonObject ConfigManager::projectAspect()
{
    configFile.open( QIODevice::ReadOnly | QIODevice::Text );
    QString val = configFile.readAll();
    configFile.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson( val.toUtf8() );

    QJsonObject jsonObject = jsonDocument.object();

    return jsonObject.value( QString( "aspect" ) ).toObject().value("project").toObject();
}

QJsonObject ConfigManager::machineAspect()
{
    configFile.open( QIODevice::ReadOnly | QIODevice::Text );
    QString val = configFile.readAll();
    configFile.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson( val.toUtf8() );

    QJsonObject jsonObject = jsonDocument.object();

    return jsonObject.value( QString( "aspect" ) ).toObject().value("machine").toObject();
}

QJsonObject ConfigManager::consoleAspect()
{
    configFile.open( QIODevice::ReadOnly | QIODevice::Text );
    QString val = configFile.readAll();
    configFile.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson( val.toUtf8() );

    QJsonObject jsonObject = jsonDocument.object();

    return jsonObject.value( QString( "aspect" ) ).toObject().value("console").toObject();
}


