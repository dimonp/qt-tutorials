#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent(QCloseEvent *event) override;

    bool isHideToTray() const;
    void setHideToTray(bool flag);

private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMessageInTray();
    void closeApp();

private:
    std::unique_ptr<QSystemTrayIcon> trayIcon_;
    std::unique_ptr<Ui::MainWindow> ui;
};
#endif // MAINWINDOW_H
