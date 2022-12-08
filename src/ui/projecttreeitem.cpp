#include "projecttreeitem.h"

#include <QDebug>

ProjectTreeItem::ProjectTreeItem( QWidget *parent, QString path ) :
    QPushButton( parent )
{
    this->path = path;
}

void ProjectTreeItem::mousePressEvent( QMouseEvent *e )
{
    if( e->button() == Qt::RightButton )
        emit rightClicked();
    else
        emit leftClicked();
}
