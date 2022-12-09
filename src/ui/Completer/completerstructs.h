#ifndef COMPLETERSTRUCTS_H
#define COMPLETERSTRUCTS_H

#include <QString>
#include <QMap>
#include <QPlainTextEdit>
#include <QDebug>
#include <QFileInfo>
#include <QDateTime>

#include <cstring>

#include "completerparser.h"
#include "completerenums.h"



struct Words
{
    QMap<QString, SuggestionType> stdWords;
    QMap<QString, SuggestionType> dynamicWords;

    void cleanStdWords()
    {
        stdWords.clear();
    }

    void cleanDynamicWords()
    {
        dynamicWords.clear();
    }
};



struct TLTRootNode
{
    QPlainTextEdit* node = nullptr;

    QString rootText()
    {
        return node->toPlainText();
    }
};



struct TLTChildNode
{
    bool status      = false;
    QString nodeName = QString();
    QDateTime timeStamp = QDateTime();

    TLTChildNode() {}

    TLTChildNode( QString includeName )
    {
        nodeName = includeName;
    }

    TLTChildNode( QString includeName, bool state)
    {
        nodeName = includeName;
        status   = state;
    }

    bool testAndSet()
    {
        bool ret = status;
        if ( status ) status = false;
        return ret;
    }

    bool testDate( QDateTime newTime )
    {
        if ( timeStamp != newTime )
        {
            timeStamp = newTime;
            status = true;
        }
        return status;
    }

    void setDate( QDateTime newTime )
    {
        timeStamp = newTime;
    }
};


struct TLVector
{
#define ZERO 0

    TLTChildNode **childs = new TLTChildNode*[ ZERO ];

    ~TLVector()
    {
        delete [] childs;
    }

    void insert( TLTChildNode *node )
    {
        if ( !contains( node ) )
        {
            if ( lastElemInsertIndex == SIZE ) realloc();

            childs[ lastElemInsertIndex ] = node;
            lastElemInsertIndex++;
        }
    }

    bool contains( TLTChildNode *node )
    {
        bool b = false;

        if ( indexOf( node ) != -1 )
        {
            b = true;
        }
        return b;
    }

    TLVector intersection( TLVector &findedChilds )
    {
        TLVector ret;

        for ( int index = ZERO; index < len(); ++index )
        {
            TLTChildNode *curr = childs[ index ];
            if ( findedChilds.indexOf( curr ) == -1 )
            {
                ret.insert( curr );
            }
        }
        return ret;
    }

    int indexOf( TLTChildNode *node )
    {
        int indexOf = -1;
        for( int index = ZERO; index < SIZE; index++ )
        {
            TLTChildNode *cmp = childs[ index ];
            if ( cmp == node || cmp->nodeName.compare( node->nodeName ) == ZERO )
            {
                indexOf = index;
                break;
            }
        }
        return indexOf;
    }

    int remove( TLTChildNode *node )
    {
        int indexOfElem = indexOf( node );
        if ( indexOfElem != -1 )
        {
            delete childs[ indexOfElem ];
            childs[ indexOfElem ] = nullptr;

            std::memcpy ( &childs[ indexOfElem ], &childs[ --SIZE ], sizeof( TLTChildNode ) );

            lastElemInsertIndex--;
        }
        return indexOfElem;
    }


    int len()
    {
        return SIZE;
    }

    void DEBUG()
    {
        for( int index = ZERO; index < SIZE; index++ )
        {
            TLTChildNode *cmp = childs[ index ];
            qDebug() << "Name: " << cmp->nodeName \
                     << ", Status: " << cmp->status \
                     << ", Time: " << cmp->timeStamp \
                     << ", Addr: " << cmp;
        }

    }

private:
    void realloc()
    {
        int oldSize = SIZE;
        TLTChildNode **newArray = new TLTChildNode*[ ++SIZE ];
        std::copy(childs, childs + std::min(oldSize, SIZE), newArray);
        delete [] childs;
        childs = newArray;
    }

    int lastElemInsertIndex = ZERO;
    int SIZE = ZERO;
};


struct TLTree
{
    QString projectPath = QString();

    TLTRootNode root;
    TLVector    nodes;


};


#endif // COMPLETERSTRUCTS_H
