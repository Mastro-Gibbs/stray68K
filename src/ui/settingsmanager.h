#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QDialog>
#include <QDebug>
#include <QFileDialog>

#include "configmanager.h"

#define DARKTHEME_QRC  ":/theme/theme/DarkTheme.json"
#define LIGHTTHEME_QRC ":/theme/theme/LightTheme.json"

namespace Ui {
class SettingsManager;
}

class SettingsManager : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsManager(QWidget *parent = nullptr);
    ~SettingsManager();

    void readConfigAndSet();

    void accept() override;

    const QString &getTheme() const;
    const QString &getEditorFont() const;
    const QString &getConsoleFont() const;
    int getEditorFontSize() const;
    int getConsoleFontSize() const;

    const QString &getDefaultPath() const;
    bool getUseDefaultPath() const;

signals:
    void settingsUpdateRequest();

private slots:
    void changeWorkdir();

private:
    void storeNewValues();

    void writeNewValues();

    Ui::SettingsManager *ui;

    ConfigManager *configManager;

    struct Appearance
    {
        QString theme;
        QString editorFont;
        QString consoleFont;
        int     editorFontSize;
        int     consoleFontSize;
    };

    struct ProjectWiz
    {
        QString defaultPath;
        bool    useDefaultPath;
    };

    struct Options
    {
        Appearance appearance;
        ProjectWiz projectWiz;
    };

    Options options;
};

#endif // SETTINGSMANAGER_H
