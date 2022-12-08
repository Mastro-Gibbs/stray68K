#ifndef PROJECTWIZARD_H
#define PROJECTWIZARD_H

#include <QWizard>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QProcess>

#include "configmanager.h"
#include "promanager.h"

#define MAIN_TEMPLATE_HELLOWORLD "; template\n; it print 'Hello World'\n\n\tORG   $1000\n\n\tLEA   string,A0\n\tTRAP  #15\n\nstring:   DC.B \"Hello World\\n\",0\n"

namespace Ui {
class ProjectWizard;
}

class ProjectWizard : public QWizard
{
    Q_OBJECT

public:
    explicit ProjectWizard(QWidget *parent = nullptr);
    ~ProjectWizard();

    void accept() override;

    void run();

    const QString &gets68kPath() const;

signals:
    void created();

public slots:
    void enableNextBtn();

private slots:
    void on_browseBtn_clicked();

private:
    Ui::ProjectWizard *ui;
    QAbstractButton *nextBtn;
    QString lang;
    QString mainFilePath;

    QString s68kPath;

    void setUp();
    void writeTemplate();
};

#endif // PROJECTWIZARD_H
