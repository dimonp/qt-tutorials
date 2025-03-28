#include <QApplication>

#include "mainwindow.h"
#include "appconfig.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow main_window;
    AppConfig app_config;
    
    app_config.loadSettings(&main_window);
    main_window.show();
    int exitCode = a.exec();
    app_config.saveSettings(&main_window);

    return exitCode;
}
