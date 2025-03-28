#ifndef APPCONFIG_H
#define APPCONFIG_H

class MainWindow;

class AppConfig
{
    inline static const char *kConfigFileName = "settings.ini";

    inline static const char* kConfigGeometry = "mainwindow/geometry";
    inline static const char* kConfigIsFullscrn = "mainwindow/fullScreen";
    inline static const char* kConfigIsVisible = "outputpanel/visible";
    inline static const char* kConfigIsInTray = "outputpanel/in_tray";

public:
    void saveSettings(const MainWindow&);
    void loadSettings(MainWindow&);
};

#endif // APPCONFIG_H
