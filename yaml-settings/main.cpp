#include <QApplication>

#include "mainwindow.h"
#include "appconfig.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    
    AppConfig app_config;   
    app_config.loadSettings(mainWindow);

    mainWindow.show();
    int exitCode = app.exec();

    app_config.saveSettings(mainWindow);

    return exitCode;
}
