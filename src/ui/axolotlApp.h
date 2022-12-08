#ifndef AXOLOTLAPP_H
#define AXOLOTLAPP_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QSaveFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QProcess>
#include <QScrollBar>

#include "editor.h"
#include "themesetter.h"
#include "projectwizard.h"
#include "outputhighlighter.h"
#include "promanager.h"
#include "projectmanager.h"
#include "settingsmanager.h"

#define RECENT_FILES_PATH    "recent_files"
#define RECENT_PROJECTS_PATH "recent_projects"

QT_BEGIN_NAMESPACE
namespace Ui { class AxolotlApp; }
QT_END_NAMESPACE

class AxolotlApp : public QMainWindow
{
    Q_OBJECT

public:
    AxolotlApp(QWidget *parent = nullptr);
    ~AxolotlApp();

    /*
     * DYnamic disabling or enabling of items ( implemented via connections )
     */
    void dynamicBinding();

    /*
     * Initialize objs and set some value
     */
    void init();

    void setIcons();

    void setTheme();

private slots:
    void initTheme();

    void openFile( QString );
    void openProject( QString );

    void fileModified();

    void closeEditorTab( int );

    void generatePopupMenu( ProjectTreeItem *parent, QString filePath, ProjectManager::ProjectItemType type );

    void run( QString path );
    void printStdoutStderr();

    void disableRunProject( bool value );
    void disableEditorActions( int value );

    void loadNewSettings();

    void updateDataAfterRenaming(QString oldName, QString newName);

private slots:
    void on_actionNewFile_triggered();
    void on_actionOpenFile_triggered();

    void on_actionNewProject_triggered();
    void on_actionOpenProject_triggered();
    void on_actionCloseProject_triggered();


    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void on_actionClose_all_tabs_triggered();
    void on_actionForce_quit_triggered();


    void on_actionCurrent_editor_zoom_in_triggered();
    void on_actionCurrent_editor_zoom_out_triggered();
    void on_actionProgram_output_frame_triggered();


    void on_actionRun_triggered();
    void on_actionRun_project_triggered();


    void on_actionSettings_triggered();


    void on_cleanBtn_clicked();
    void on_stopBtn_clicked();

    void on_actionReload_project_triggered();

    void on_actionToggle_machine_area_triggered();

    void on_actionToggle_project_frame_triggered();

signals:
    void projectOpened();
    void projectClosed();


private:
    void findInexistentRecentPath( const QString &path_to_file);
    void setRecent  ( const QString &, QString );
    void recent     ( const QString & );
    void clearRecent( const QString & );

    QMap<QString, QString> openedFileMap;  //<K = filename, V = file_path>

    OutputHighlighter *syntaxHighlighter;

    struct ProjectData
    {
        bool    projectOpened;
        QString s68kPath;
        QString mainPath;
        QString projectPath;
    };

    struct AxolotlProcesses
    {
        QProcess *runnerProcess = nullptr ;
        QProcess *finder        = nullptr;
    };

    AxolotlProcesses axolotlProcesses;
    ProjectData      projectData;

    ProjectWizard  *projectWizard    = nullptr;
    ProjectManager *projectManager   = nullptr;
    SettingsManager *settingsManager = nullptr;

    Ui::AxolotlApp *ui;
};
#endif // AXOLOTLAPP_H
