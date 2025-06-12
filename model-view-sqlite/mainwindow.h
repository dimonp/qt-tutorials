#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sqlitetreemodel.h"

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

private slots:
    void on_actionOpen_triggered();
    
    void showItemDetails(const QModelIndex &index);

private:
    SqliteTreeModel sqliteModel;
    std::unique_ptr<Ui::MainWindow> ui;
};
#endif // MAINWINDOW_H
