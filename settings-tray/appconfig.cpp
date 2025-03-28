#include <QSettings>
#include <QScreen>

#include "appconfig.h"
#include "mainwindow.h"

void AppConfig::saveSettings(const MainWindow& wnd)
{
    QSettings settings(kConfigFileName, QSettings::IniFormat);

    settings.setValue(kConfigGeometry, wnd.geometry());
    settings.setValue(kConfigIsFullscrn, wnd.isFullScreen());
    settings.setValue(kConfigIsVisible, wnd.isVisible());
    settings.setValue(kConfigIsInTray, wnd.isHideToTray());
    settings.sync();
}

void AppConfig::loadSettings(MainWindow& wnd)
{
    QSettings settings(kConfigFileName, QSettings::IniFormat);

    if (auto geometry = settings.value(kConfigGeometry);  geometry.canConvert<QRect>()) {
        wnd.setGeometry(geometry.toRect());
    } else {
        wnd.move(wnd.screen()->geometry().center() - wnd.frameGeometry().center());
        wnd.resize(800, 300);
    }

    if (auto fullscreen = settings.value(kConfigIsFullscrn);  fullscreen.canConvert<bool>() && fullscreen.toBool()) {
        wnd.showFullScreen();
    }

    if (auto visible = settings.value(kConfigIsVisible);  visible.canConvert<bool>() && !visible.toBool()) {
        wnd.hide();
    }

    if (auto in_tray = settings.value(kConfigIsInTray);  in_tray.canConvert<bool>()) {
        wnd.setHideToTray(in_tray.toBool());
    }
}
