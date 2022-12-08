#include "settingsmanager.h"
#include "ui_settingsmanager.h"

SettingsManager::SettingsManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsManager)
{
    ui->setupUi(this);

    setWindowTitle( "Axolotl Options" );

    show();

    configManager = ConfigManager::getInstance();

    connect(ui->browseButton, &QPushButton::pressed, this, &SettingsManager::changeWorkdir);
}

SettingsManager::~SettingsManager()
{
    delete ui;
}


void SettingsManager::changeWorkdir()
{
    ui->defaultPath->insert(QFileDialog::getExistingDirectory() + "/");
}

void SettingsManager::readConfigAndSet()
{
    QString theme       = configManager->theme();
    QString editorFont  = configManager->editorFont();
    QString consoleFont = configManager->consoleFont();
    int editorFontSize  = configManager->editorFontSize();
    int consoleFontSize = configManager->consoleFontSize();
    QJsonObject projDefault = configManager->projectData();

    options.appearance.theme           = theme;
    options.appearance.editorFont      = editorFont;
    options.appearance.editorFontSize  = editorFontSize;
    options.appearance.consoleFont     = consoleFont;
    options.appearance.consoleFontSize = consoleFontSize;
    options.projectWiz.defaultPath     = projDefault[ "path" ].toString();
    options.projectWiz.useDefaultPath  = projDefault[ "state" ].toInt();

    if ( theme.compare( ":/theme/theme/DarkTheme.json" ) == 0 )
        ui->themebox->setCurrentIndex( 0 );
    else if ( theme.compare( ":/theme/theme/LightTheme.json" ) == 0 )
        ui->themebox->setCurrentIndex( 1 );

    ui->editorFontBox->setCurrentFont( QFont( options.appearance.editorFont ) );

    ui->editorFontSizeBox->setValue( options.appearance.editorFontSize );

    ui->consoleFontBox->setCurrentFont( QFont( options.appearance.consoleFont ) );

    ui->consoleFontSizeBox->setValue( options.appearance.consoleFontSize );

    ui->defaultPath->setText( options.projectWiz.defaultPath );

    ui->useDefaultCheckBox->setChecked( options.projectWiz.useDefaultPath );

}


void SettingsManager::storeNewValues()
{
    if ( ui->themebox->currentText().compare( "Dark Theme" ) == 0 )
        options.appearance.theme = QString(DARKTHEME_QRC);
    else if ( ui->themebox->currentText().compare( "Light Theme" ) == 0  )
        options.appearance.theme = QString(LIGHTTHEME_QRC);

    options.appearance.editorFont      = ui->editorFontBox->currentFont().family();
    options.appearance.editorFontSize  = ui->editorFontSizeBox->value();
    options.appearance.consoleFont     = ui->consoleFontBox->currentFont().family();
    options.appearance.consoleFontSize = ui->consoleFontSizeBox->value();
    options.projectWiz.defaultPath     = ui->defaultPath->text();
    options.projectWiz.useDefaultPath  = ui->useDefaultCheckBox->isChecked();
}


void SettingsManager::writeNewValues()
{
    configManager->updateTheme( options.appearance.theme );
    configManager->updateProjectData( options.projectWiz.useDefaultPath, options.projectWiz.defaultPath );
    configManager->updateEditorFont( options.appearance.editorFont );
    configManager->updateConsoleFont( options.appearance.consoleFont );
    configManager->updateEditorFontSize( options.appearance.editorFontSize );
    configManager->updateConsoleFontSize( options.appearance.consoleFontSize );
}


void SettingsManager::accept()
{
    storeNewValues();
    writeNewValues();
    QDialog::accept();
    emit settingsUpdateRequest();
}


const QString &SettingsManager::getTheme() const
{
    return options.appearance.theme;
}

const QString &SettingsManager::getEditorFont() const
{
    return options.appearance.editorFont;
}

const QString &SettingsManager::getConsoleFont() const
{
    return options.appearance.consoleFont;
}

int SettingsManager::getEditorFontSize() const
{
    return options.appearance.editorFontSize;
}

int SettingsManager::getConsoleFontSize() const
{
    return options.appearance.consoleFontSize;
}

const QString &SettingsManager::getDefaultPath() const
{
    return options.projectWiz.defaultPath;
}

bool SettingsManager::getUseDefaultPath() const
{
    return options.projectWiz.useDefaultPath;
}
