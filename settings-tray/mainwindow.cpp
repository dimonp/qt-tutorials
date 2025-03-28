#include <QSettings>
#include <QCloseEvent>
#include <QStyle>

#include "./ui_mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow())
    , trayIcon_(std::make_unique<QSystemTrayIcon>(this))
{
    ui->setupUi(this);

    connect(ui->showMsgButton, &QPushButton::clicked, this, &MainWindow::showMessageInTray);

    trayIcon_->setIcon(style()->standardIcon(QStyle::SP_ComputerIcon));
    trayIcon_->setToolTip("Tray Program"
                          "\n"
                          "Example");

    QMenu *menu = new QMenu(this);
    QAction *viewWindow = new QAction("Show", this);
    QAction *quitAction = new QAction("Exit", this);

    connect(viewWindow, &QAction::triggered, this, &MainWindow::show);
    connect(quitAction, &QAction::triggered, this, &MainWindow::closeApp);

    menu->addAction(viewWindow);
    menu->addAction(quitAction);

    trayIcon_->setContextMenu(menu);
    trayIcon_->show();

    connect(trayIcon_.get(), &QSystemTrayIcon::activated, this, &MainWindow::trayIconActivated);
}

MainWindow::~MainWindow() = default;

void MainWindow::showMessageInTray()
{
    trayIcon_->showMessage("Message title", "Message text", QSystemTrayIcon::Information);
}

void MainWindow::closeApp()
{
    QCoreApplication::quit();
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        setVisible(!isVisible());
        break;
    default:
        break;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (isHideToTray()) {
        event->ignore();
        hide();
    } else {
        closeApp();
    }
}

bool MainWindow::isHideToTray() const
{
    return ui->toTrayCheckBox->isChecked();
}

void MainWindow::setHideToTray(bool flag)
{
    ui->toTrayCheckBox->setChecked(flag);
}
