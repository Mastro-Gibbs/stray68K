#include "projectwizard.h"
#include "ui_projectwizard.h"

ProjectWizard::ProjectWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::ProjectWizard)
{
    ui->setupUi(this);

    show();
}


ProjectWizard::~ProjectWizard()
{
    delete ui;
}


void ProjectWizard::setUp()
{
    setWindowTitle("Project wizard");

    nextBtn = button(WizardButton::NextButton);

    nextBtn->setDisabled(true);

    ConfigManager *config = ConfigManager::getInstance();
    QJsonObject item = config->projectData();

    int state = item["state"].toInt();

    if(state)
    {
        ui->checkBox->setChecked(true);
        QString savedPath = item["path"].toString();
        ui->newProjPath->insert(savedPath);
    }
    else
        ui->checkBox->setChecked(false);

    ui->newProjPath->setReadOnly(true);

    QFont font = ui->errLabelMain->font();
    font.setBold(true);
    ui->errLabelMain->setFont(font);
}



void ProjectWizard::run()
{
    connect(ui->newProjName, &QLineEdit::textChanged, this, &ProjectWizard::enableNextBtn);
    connect(ui->newProjPath, &QLineEdit::textChanged, this, &ProjectWizard::enableNextBtn);

    connect(ui->lineEdit   , &QLineEdit::textChanged, this, &ProjectWizard::enableNextBtn);

    setUp();
}

void ProjectWizard::accept()
{
    ui->errLabelMain->clear();

    if ( ui->lineEdit->text().compare( QString() ) == 0 )
    {
        ui->errLabelMain->setText( "* Main file name required" );
        return;
    }

    ConfigManager *config = ConfigManager::getInstance();
    config->updateProjectData( ui->checkBox->isChecked(), ui->newProjPath->text() );

    QString newProjectFullpath(ui->newProjPath->text());
    newProjectFullpath.append(ui->newProjName->text());

    QDir mkdir;
    mkdir.mkdir(newProjectFullpath);

    newProjectFullpath.append("/");

    mainFilePath = newProjectFullpath;
    QString mainName;

    mainFilePath.append(ui->lineEdit->text());
    mainFilePath.append(".X68");
    mainName = ui->lineEdit->text();
    mainName.append(".X68");

    QFile mkfile(mainFilePath);
    mkfile.open(QIODevice::WriteOnly);
    mkfile.close();
    mkfile.setPermissions(QFile::ReadGroup  | QFile::ReadOther  | QFile::ReadOwner  | QFile::ReadUser |\
                          QFile::WriteGroup | QFile::WriteOther | QFile::WriteOwner | QFile::WriteUser|\
                          QFile::ExeGroup   | QFile::ExeOther   | QFile::ExeOwner   | QFile::ExeUser  );

    writeTemplate();

    QVector<QString> data;
    data.append(ui->newProjName->text());

    data.append(mainName);

    QString proFile(newProjectFullpath);
    proFile.append(ui->newProjName->text());
    proFile.append(".s68");

    s68kPath = proFile;

    ProManager *proManager = ProManager::getInstance();
    proManager->setProFile(proFile);
    proManager->makeIt(data);

    QWizard::accept();

    emit created();
}


void ProjectWizard::enableNextBtn()
{
    QString projName( ui->newProjName->text() );
    QString projpath( ui->newProjPath->text() );

    if (projName.compare("") != 0 && projpath.compare("") != 0)
        nextBtn->setDisabled(false);
    else if(projName.compare("") == 0 || projpath.compare("") == 0)
        nextBtn->setDisabled(true);
}

void ProjectWizard::on_browseBtn_clicked()
{
    ui->newProjPath->clear();
    ui->newProjPath->insert(QFileDialog::getExistingDirectory() + "/");
}

const QString &ProjectWizard::gets68kPath() const
{
    return s68kPath;
}


void ProjectWizard::writeTemplate()
{
    QByteArray mainTemplate;

    if (ui->hwCheckBtn->isChecked())
        mainTemplate = MAIN_TEMPLATE_HELLOWORLD;
    else return;

    QFile main(mainFilePath);
    main.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream iStream( &main );
    iStream.setCodec( "utf-8" );
    iStream << mainTemplate;
    main.close();

}
