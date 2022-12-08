#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QObject>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMenu>
#include <QAction>


#include "projecttreeitem.h"
#include "promanager.h"
#include "sourceadder.h"
#include "fileoptions.h"

class ProjectManager : public QObject
{
    Q_OBJECT

public:
    static ProjectManager *getInstance();

    virtual ~ProjectManager();

    void generateSkASMTree( QTreeWidget *parent, QString s68kPath );

    enum ProjectItemType
    {
        Folder = 0,
        Source = 1,
        Binary = 2
    };

    inline const QString &getMainPath() const
        { return mainPath; }

signals:
    void openRequest( QString path );
    void popupMenuRequest( ProjectTreeItem *parent, QString filePath = QString(), ProjectManager::ProjectItemType type = Folder );

    void generatingFinished();
    void fileNameChanged( QString oldName, QString newName);

public slots:
    void addSrc( QTreeWidget *parent, QString proPath );
    void renameSrc ( QTreeWidget *parent, QVector<QString> params );
    void deleteSrc ( QTreeWidget *parent, QVector<QString> params );

    inline void renamed( QString oldName, QString newName )
        { emit fileNameChanged(oldName, newName); }

private slots:
    inline void open( QString path )
        { emit openRequest( path ); }

    inline void generatePopupMenu( ProjectTreeItem *parent,
                                   QString filePath = QString(),
                                   ProjectManager::ProjectItemType type = Folder )
        { emit popupMenuRequest( parent, filePath, type ); }

private:
    explicit ProjectManager();

    QString elaboratePath( QString s68kPath );

    QString mainPath;

    SourceAdder *adder = nullptr;

    FileOptions *fileOptions = nullptr;
};

#endif // PROJECTMANAGER_H
