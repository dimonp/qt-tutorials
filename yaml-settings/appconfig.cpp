#include <QScreen>
#include <QDateTime>

#include "appconfig.h"
#include "mainwindow.h"
#include "yamlsettings.h"

/**
 * @brief Saves the current application settings to the configuration file.
 *
 * This function stores the main window's current state, 
 *
 * @param[in] wnd constant reference to the main window whose settings are to be saved.
 */
void AppConfig::saveSettings(const MainWindow &wnd)
{
    QSettings settings(kConfigFileName, YamlSettings::format);

    settings.setValue(kConfigGeometry, wnd.geometry());
    settings.setValue(kConfigIsFullscrn, wnd.isFullScreen());
    settings.setValue(kConfigIsVisible, wnd.isVisible());
    settings.setValue(kConfigAppLastRun, QDateTime::currentDateTime());
    settings.setValue(kConfigAppData, wnd.getData());
    settings.sync();
}

/**
 * @brief Loads the application settings from the configuration file.
 *
 * This function retrieves and applies previously saved application settings,
 * If no saved settings are found, it sets default window properties.
 *
 * @param[in,out] wnd reference to the main window object to be configured.
 */
void AppConfig::loadSettings(MainWindow &wnd)
{
    QSettings settings(kConfigFileName, YamlSettings::format);

    if (auto geometry = settings.value(kConfigGeometry); geometry.canConvert<QRect>()) {
        wnd.setGeometry(geometry.toRect());
    } else {
        wnd.move(wnd.screen()->geometry().center() - wnd.frameGeometry().center());
        wnd.resize(800, 300);
    }

    if (auto fullscreen = settings.value(kConfigIsFullscrn);  
            fullscreen.canConvert<bool>() && fullscreen.toBool()) {
            
        wnd.showFullScreen();
    }

    if (auto visible = settings.value(kConfigIsVisible); visible.canConvert<bool>()) {            
        wnd.setVisible(visible.toBool());
    }

    if (auto lastRun = settings.value(kConfigAppLastRun); lastRun.canConvert<QDateTime>()) {
        QString time = lastRun.toDateTime().toString(Qt::RFC2822Date);
        if (time.isEmpty()) {
            wnd.showMessage("No previous run");
        } else {
            wnd.showMessage(QString("Last run: %1").arg(time));
        }
    }

    if (auto data = settings.value(kConfigAppData); data.canConvert<QStringList>()) {            
        wnd.setData(data.toStringList());
    }
}