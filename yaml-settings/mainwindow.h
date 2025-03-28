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
    explicit MainWindow( QWidget *parent = nullptr );
    ~MainWindow();

    void showMessage(const QString &message);
    QStringList getData() const;
    void setData(const QStringList &data);

private slots:
    void on_actionOpen_triggered();
    void on_pushButtonAdd_clicked();
    void on_pushButtonDelete_clicked();

private:
    std::unique_ptr<Ui::MainWindow> ui;
};
#endif // MAINWINDOW_H
