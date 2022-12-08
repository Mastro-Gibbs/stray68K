#ifndef SOURCEADDER_H
#define SOURCEADDER_H


#include <QDialog>
#include <QProcess>

#include "promanager.h"

namespace Ui {
class SourceAdder;
}

class SourceAdder : public QDialog
{
    Q_OBJECT

public:
    explicit SourceAdder(QWidget *parent = nullptr);
    ~SourceAdder();

    void accept() override;

    inline void setProjectPath(const QString &newProjectPath) { projectPath = newProjectPath; }

    inline void setProPath(const QString &newProPath) { proPath = newProPath; }

private:
    Ui::SourceAdder *ui;

    QString projectPath;
    QString proPath;
};

#endif // SOURCEADDER_H
