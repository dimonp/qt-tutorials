#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QSettings>

class MainWindow;

class AppConfig
{
    inline static const char *kConfigFileName = "settings.yaml";

    inline static const char* kConfigGeometry = "mainwindow/geometry";
    inline static const char* kConfigIsFullscrn = "mainwindow/fullScreen";
    inline static const char* kConfigIsVisible = "outputpanel/visible";
    inline static const char* kConfigIsInTray = "outputpanel/in_tray";
    inline static const char* kConfigAppLastRun = "application/last_run";
    inline static const char* kConfigAppData = "application/data";
    inline static const char* kConfigAppDataMap = "application/data_map";

public:
    static void saveSettings(const MainWindow&);
    static void loadSettings(MainWindow&);
};

#endif // APPCONFIG_H
