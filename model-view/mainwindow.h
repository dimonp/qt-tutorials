#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "treemodel.h"
#include "tablemodel.h"

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

private:
    TreeModel treeModel;
    TableModel tableModel;
    std::unique_ptr<Ui::MainWindow> ui;
};
#endif // MAINWINDOW_H
