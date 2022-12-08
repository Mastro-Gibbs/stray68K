#include "promanager.h"

ProManager::ProManager()
{}



ProManager *ProManager::getInstance()
{
    static ProManager instance;
    return &instance;
}



void ProManager::makeIt(QVector<QString> data)
{
    QJsonObject obj;
    obj.insert("name", data[0]);
    obj.insert("main", data[1]);

    QJsonDocument document;
    document.setObject( obj );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );

    write( bytes );
}


void ProManager::addSourceFile( QString fileName )
{
    QJsonObject obj;
    obj.insert( "name", proData( Name ) );
    obj.insert( "main", proData( Main ) );

    QJsonArray arraySources;
    arraySources = sources();
    arraySources << fileName;
    obj.insert( "sources", arraySources );

    QJsonDocument document;
    document.setObject( obj );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );

    write( bytes );
}


void ProManager::removeSourceFile( QString path )
{
    QJsonObject obj;
    obj.insert( "name", proData( Name ) );
    obj.insert( "main", proData( Main ) );

    QVector<QString> sourcesList;
    sourcesList = sourcesToQStringVector();
    sourcesList.removeOne( path );

    QJsonArray arraySources;
    foreach ( QString srcPath, sourcesList )
    {
        arraySources << srcPath;
    }

    obj.insert( "sources", arraySources );

    QJsonDocument document;
    document.setObject( obj );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );

    write( bytes );
}


QString ProManager::proData(ProDataType type)
{
    proFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = proFile.readAll();
    proFile.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(val.toUtf8());

    QJsonObject jsonObject = jsonDocument.object();

    QString typeString;

    switch ( type )
    {
        case Name:
            typeString = "name";
            break;

        case Main:
            typeString = "main";
            break;
    }
    return jsonObject.value( typeString ).toString();
}


QJsonArray ProManager::sources()
{
    proFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = proFile.readAll();
    proFile.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(val.toUtf8());

    QJsonObject jsonObject = jsonDocument.object();

    QJsonValue sources = jsonObject.value( "sources" );

    return sources.toArray();
}


QVector<QString> ProManager::sourcesToQStringVector()
{
    QJsonArray jsonArraySources = sources();
    QVariantList sourcesVariant = jsonArraySources.toVariantList();

    QVector<QString> sourcesList;

    foreach( QVariant elem, sourcesVariant )
    {
        sourcesList.append( elem.toString() );
    }

    return sourcesList;
}


void ProManager::setProFile(QString newProFile)
{
    proFile.setFileName(newProFile);
}


void ProManager::write(QByteArray bytes)
{
    if( proFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
    {
        QTextStream iStream( &proFile );
        iStream.setCodec( "utf-8" );
        iStream << bytes;
        proFile.close();
    }
}
