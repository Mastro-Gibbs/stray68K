/**
 * Singleton class
 *
 */


#ifndef FILEOPTIONS_H
#define FILEOPTIONS_H

#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QFile>

#include "promanager.h"

namespace Ui {
class FileOptions;
}

class FileOptions : public QDialog
{
    Q_OBJECT

public:
    explicit FileOptions(QWidget *parent = nullptr);
    ~FileOptions();

    void deleteMode( QString proPath, QString path, QString fileName );

    void renameMode( QString proPath, QString path, QString oldName );

    void accept() override;

signals:
    void newName(QString, QString);

private:
     enum OptionMode
    {
        Rename = 0,
        Delete = 1
    };

    Ui::FileOptions *ui;

    QCheckBox *permDeletingCheckBox = nullptr;

    QLineEdit *newFileName = nullptr;

    OptionMode opt;

    struct FileData
    {
        QString pathParam;
        QString proPath;
        QString fileName;
    };

    FileData fileData;


};

#endif // FILEOPTIONS_H
